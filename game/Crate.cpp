#include "Crate.h"
#include "Event.h"
#include "EventStack.h"
#include "EventCollision.h"
#include "GameController.h"
#include "DisplayManager.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "EventOut.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameEnd.h"
#include "Modifier.h"

#include <cmath>

Crate::Crate() {
    // Initialize member variables
    m_status = MOVING;
    m_target_height = DM.getVertical() + 5;

    // Initialize block position to a random number
    m_progress = rand() % 100 / 100.0;

    // Initialize progress speed based on scroll speed
    float adjusted_scroll_speed = GC.getScrollSpeed() / (GC.getFastScrollMode() ? 4.0 : 1.0);
    if (adjusted_scroll_speed == 0) m_progress_speed = 0.010;
    else m_progress_speed = adjusted_scroll_speed / 1.5 - 0.015;
    // printf("Progress Speed: %f\n", m_progress_speed);
    
    // Initialize object properties
    setSprite("crate");
    setType("Crate");
    setSolidness(df::SOFT);

    m_crate_size = df::Vector(
        getAnimation().getSprite()->getWidth() + 1,
        getAnimation().getSprite()->getHeight() + 1
    );

    setPosition(df::Vector(-10, -10));
}

df::Vector Crate::getCrateSize() const {
    return m_crate_size;
}

void Crate::drop() {
    m_status = FALLING;
}

void Crate::step() {
    switch (m_status) {
    case MOVING: {
        // Convert m_progress to a value that moves back and forth
        float x_progress;

        Modifier *mod = GC.getModifier();
        if (mod != nullptr && mod->getModifierType() == SWING)
            x_progress = (1 + std::sin(m_progress * 2 * M_PI - M_PI / 2)) / 2; // Sinusoidal movement
        else
            x_progress = 1 - abs(std::fmod(m_progress * 2, 2) - 1);     // Linear movement

        // Calculate new x position
        float x_pos = m_crate_size.getX() / 2 + (DM.getHorizontal() - m_crate_size.getX()) * x_progress;

        // Set new position and increment progress
        setPosition(df::Vector(x_pos, DM.getVertical() / 4));

        // Increment progress
        if (mod != nullptr && mod->getModifierType() == SPEEDY)
            m_progress += m_progress_speed * 1.25;
        else
            m_progress += m_progress_speed;

        break;
    }
    case FALLING: {
        setVelocity(df::Vector(0, getVelocity().getY() + 0.1));
        break;
    }
    case STACKED:
        // Crate is stacked, scroll
        setVelocity(df::Vector(0, GC.getScrollSpeed()));
        break;
    }
}

void Crate::stack() {
    df::Sound* p_sound = RM.getSound("crate-stack");
    if (p_sound) p_sound->play();

    float target_height = DM.getVertical() - GC.getStackHeight() - m_crate_size.getY() / 2;

    setVelocity(df::Vector(0, 11));

    df::Vector highest_obj_pos = GC.getHighestObject()->getPosition();

    //setPosition(df::Vector(highest_obj_pos.getX() + getCrateSize().getX(), highest_obj_pos.getY() + getCrateSize().getY()));
    setPosition(df::Vector());
    m_status = STACKED;

    // Send Stack Event.
    EventStack* e = new EventStack(this);
    WM.onEvent(e);
}

int Crate::eventHandler(const df::Event *p_e) {
    // Handle step events
    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }

    else if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision* p_collision_event = dynamic_cast<const df::EventCollision*>(p_e);
        
        if (m_status == FALLING) {
            if ((p_collision_event->getObject1() == GC.getHighestObject()) ||
                (p_collision_event->getObject2() == GC.getHighestObject())) {
                stack();
                return 1;
            }
        }

        return 0;
    }

    // Handle keyboard events
    else if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard *p_keyboard_event = dynamic_cast<const df::EventKeyboard *>(p_e);
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            if (p_keyboard_event->getKey() == df::Keyboard::SPACE && m_status == MOVING) {
                df::Sound* p_sound = RM.getSound("crate-drop");
                if (p_sound) p_sound->play();

                m_status = FALLING;
                return 1;
            }
        }
    }

    // Handle out-of-bounds events
    else if (p_e->getType() == df::OUT_EVENT) {
        if (m_status == FALLING || GC.getHighestObject() == this) {
            GC.endGame();
        }

        WM.markForDelete(this);

        return 1;
    }

    return 0;
}