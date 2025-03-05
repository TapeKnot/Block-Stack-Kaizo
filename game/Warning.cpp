#include "Warning.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "DisplayManager.h"
#include "EventStep.h"
#include "Animation.h"

#include "GameStart.h"

Warning::Warning() {
	setSprite("warning");

    df::Animation animation = getAnimation();
    animation.setIndex(1);                      // Set sprite to hidden.
    animation.setSlowdownCount(-1);             // Freeze sprite.
    setAnimation(animation);

	// Set object type.
	setType("Warning");

	setAltitude(1);

	setPosition(df::Vector(DM.getHorizontal() / 2, DM.getVertical() - 5));

    show = false;
}

int Warning::eventHandler(const df::Event* p_e) {
    // Handle step events
    if (p_e->getType() == df::STEP_EVENT) {
        if (GC.getGameEnded() == true) {
            WM.markForDelete(this);
        }


        float highest_stack_pos = DM.getVertical() - GC.getHighestObject()->getPosition().getY();

        if (show == false && GC.getTotalStacked() >= 5 && highest_stack_pos <= STACK_HEIGHT_WARNING) {
            show = true;

            df::Animation animation = getAnimation();
            animation.setSlowdownCount(0);             // Unfreeze sprite.
            setAnimation(animation);
        }
        else if (show == true && highest_stack_pos > STACK_HEIGHT_WARNING) {
            show = false;

            df::Animation animation = getAnimation();
            animation.setIndex(1);                      // Set sprite to hidden.
            animation.setSlowdownCount(-1);             // Freeze sprite.
            setAnimation(animation);
        }

        return 1;
    }

    return 0; // Return appropriate value
}

int Warning::draw() {
	return df::Object::draw();
}
