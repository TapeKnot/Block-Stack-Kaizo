#include "dragonfly/EventStep.h"
#include "dragonfly/EventOut.h"
#include "dragonfly/WorldManager.h"

#include "TowerBase.h"
#include "GameController.h"


TowerBase::TowerBase() {
	setSprite("tower-base");

	setType("TowerBase");
}

int TowerBase::eventHandler(const df::Event* p_e) {
    // Handle step events
    if (p_e->getType() == df::STEP_EVENT) {
        setVelocity(df::Vector(0, GC.getScrollSpeed()));

        return 1;
    }

    // Handle out-of-bounds events
    else if (p_e->getType() == df::OUT_EVENT) {
        WM.markForDelete(this);

        return 1;
    }

    return 0;
}