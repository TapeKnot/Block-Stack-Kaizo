#include "Crate.h"
#include "Event.h"
#include "GameController.h"
#include "DisplayManager.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "EventOut.h"
#include "WorldManager.h"

#include <cmath>

Crate::Crate(GameController *p_game_controller) {
    // Initialize member variables
    m_status = MOVING;
    m_target_height = DM.getVertical() + 5;
    m_p_game_controller = p_game_controller;
    
    // Initialize object properties
    setSprite("crate");
    setSolidness(df::SOFT);
    setPosition(df::Vector(DM.getHorizontal() / 2, -10));

    m_crate_size = df::Vector(
        getAnimation().getSprite()->getWidth() + 1,
        getAnimation().getSprite()->getHeight()
    );
}

Crate::~Crate() {
    // Destructor implementation
}

void Crate::drop() {
    m_status = FALLING;
}

int Crate::eventHandler(const df::Event *p_e) {
    // Handle step events
    if (p_e->getType() == df::STEP_EVENT) {
        const df::EventStep *p_step_event = dynamic_cast<const df::EventStep *>(p_e);
        switch (m_status) {
            case MOVING: {
                // Move crate back and forth
                float progress = p_step_event->getStepCount() / 60.0f;
                df::Vector new_position = getPosition();
                float x_pos = m_crate_size.getX() / 2 + (DM.getHorizontal() - m_crate_size.getX()) * abs(std::fmod(progress, 2) - 1);
                setPosition(df::Vector(x_pos, DM.getVertical() / 2));
                break;
            }
            case FALLING: {
                // Handle falling crate
                float target_height = DM.getVertical() - m_p_game_controller->getStackHeight() - m_crate_size.getY() / 2;
                bool below_height = getPosition().getY() > target_height;
                bool within_stack = abs(getPosition().getX() - m_p_game_controller->getStackPosition()) < m_crate_size.getX() / 2;
                if (below_height && within_stack) {
                    setVelocity(df::Vector(0, 0));
                    setPosition(df::Vector(getPosition().getX(), target_height));
                    m_status = STACKED;
                    m_p_game_controller->successfulDrop(getPosition().getX());
                } else {
                    setVelocity(df::Vector(0, getVelocity().getY() + 0.1));
                }
                break;
            }
            case STACKED:
                // Crate is stacked, scroll
                setVelocity(df::Vector(0, m_p_game_controller->getScrollSpeed()));
                break;
        }

        return 1;
    }

    // Handle keyboard events
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard *p_keyboard_event = dynamic_cast<const df::EventKeyboard *>(p_e);
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            if (p_keyboard_event->getKey() == df::Keyboard::SPACE && m_status == MOVING) {
                m_status = FALLING;
                return 1;
            }
        }
    }

    // Handle out-of-bounds events
    if (p_e->getType() == df::OUT_EVENT) {
        if (m_status == FALLING) {
            new Crate(m_p_game_controller);
        }
        WM.markForDelete(this);
    }

    return 0;
}