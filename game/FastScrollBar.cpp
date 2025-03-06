#include "FastScrollBar.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "DisplayManager.h"
#include "EventStep.h"
#include "Animation.h"
#include "Crate.h"

#include "GameStart.h"

FastScrollBar::FastScrollBar() {
    setSprite("fast-scroll-bar");

    // Set object type.
    setType("FastScrollBar");

    setAltitude(2);

    setPosition(df::Vector(DM.getHorizontal() / 2, (DM.getVertical() / 2) - 3));
}

int FastScrollBar::eventHandler(const df::Event* p_e) {
    // Handle step events
    if (p_e->getType() == df::STEP_EVENT) {
        if (GC.getGameEnded() == true) {
            WM.markForDelete(this);
        }

        return 1;
    }

    return 0; // Return appropriate value
}

int FastScrollBar::draw() {
    return df::Object::draw();
}
