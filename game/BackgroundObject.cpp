#include "BackgroundObject.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "GameController.h"
#include "Animation.h"
#include "EventOut.h"

// Constructor
BackgroundObject::BackgroundObject(BackgroundObjectType background_object_type) {
    // Set object type
    setType("BackgroundObject");
    
    // Store the background object type
    m_background_object_type = background_object_type;
    
    // Set common properties for background objects
    setSolidness(df::SPECTRAL);  // Background elements don't collide
    setAltitude(2);              // Draw in the background
    
    // Handle specific initialization based on type
    switch (m_background_object_type) {
        case STAR: {
            // Star-specific initialization
            setSprite("star");
            df::Animation newAnimation = getAnimation();
            newAnimation.setIndex(rand() % 3);
            newAnimation.setSlowdownCount(-1);
            setAnimation(newAnimation);
            // Random speed modifier between 0.3 and 0.5
            m_speed_modifier = 0.3 + static_cast<float>(rand() % 11) / 50;
            break;
        }
        case PLANET: {
            // Star-specific initialization
            setSprite("planet");
            df::Animation newAnimation = getAnimation();
            newAnimation.setIndex(rand() % 3);
            newAnimation.setSlowdownCount(-1);
            setAnimation(newAnimation);
            // Random speed modifier between 0.1 and 0.3
            m_speed_modifier = 0.1 + static_cast<float>(rand() % 11) / 50;
            break;
        }
        default:
            LM.writeLog("Unknown background object type");
            break;
    }

    // Set initial position just off-screen
    setPosition(df::Vector(
        rand() % (int)WM.getBoundary().getHorizontal(),
        -(getAnimation().getBox().getVertical() + 1) / 2
    ));
}

// Event handler
int BackgroundObject::eventHandler(const df::Event *p_e) {
    // Check if this is a step event for animation or movement
    if (p_e->getType() == df::STEP_EVENT) {
        setVelocity(df::Vector(0, GC.getScrollSpeed() * 0.5));
        return 1;  // Event handled
    }

    if (p_e->getType() == df::OUT_EVENT) {
        WM.markForDelete(this);
        return 1;
    }
    
    // If not handled, pass to parent
    return df::Object::eventHandler(p_e);
}