#include "Crate.h"
#include "dragonfly/Event.h"
#include "dragonfly/EventCollision.h"
#include "GameController.h"
#include "dragonfly/DisplayManager.h"
#include "dragonfly/EventStep.h"
#include "dragonfly/EventKeyboard.h"
#include "dragonfly/EventOut.h"
#include "dragonfly/WorldManager.h"
#include "gameEnd.h"

#include <cmath>

Crate::Crate() {
    // Initialize member variables
    m_status = MOVING;
    m_target_height = DM.getVertical() + 5;
    
    // Initialize object properties
    setSprite("crate");
    setType("Crate");
    setSolidness(df::SOFT);

    m_crate_size = df::Vector(
        getAnimation().getSprite()->getWidth() + 1,
        getAnimation().getSprite()->getHeight() + 1
    );

    float max_pos = DM.getHorizontal() - (m_crate_size.getX() / 2);
    float min_pos = 0 + (m_crate_size.getX() / 2);

    float start_pos = rand() % (int)floor(max_pos) + min_pos;

    setPosition(df::Vector(start_pos, DM.getVertical() - 20));

    float start_vel;

    if (rand() % 2 == 1) {
        start_vel = 1;
    }
    else {
        start_vel = -1;
    }

    setVelocity(df::Vector(start_vel, 0));

    
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
        if (getPosition().getX() >= DM.getHorizontal() - (m_crate_size.getX() / 2)) {
            setVelocity(df::Vector(-1, getVelocity().getY()));
        }
        else if (getPosition().getX() <= 0 + (m_crate_size.getX() / 2)) {
            setVelocity(df::Vector(1, getVelocity().getY()));
        }
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
    float target_height = DM.getVertical() - GC.getStackHeight() - m_crate_size.getY() / 2;

    setVelocity(df::Vector(0, 0));
    setPosition(df::Vector(getPosition().getX(), target_height));
    m_status = STACKED;
    GC.successfulDrop(getPosition().getX());

    GC.setTopCrate(this);
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
            if ((p_collision_event->getObject1() == GC.getTopCrate()) ||
                (p_collision_event->getObject2() == GC.getTopCrate())) {
                stack();
                return 1;
            }
            else if ((p_collision_event->getObject1()->getType() == "TowerBase") &&
                (p_collision_event->getObject2() == this)) {
                stack();
                return 1;
            }
            else if ((p_collision_event->getObject1() == this) &&
                (p_collision_event->getObject2()->getType() == "TowerBase")) {
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
                m_status = FALLING;
                return 1;
            }
        }
    }

    // Handle out-of-bounds events
    else if (p_e->getType() == df::OUT_EVENT) {
        if (m_status == FALLING || GC.getTopCrate() == this) {
            new GameEnd();
        }

        WM.markForDelete(this);

        return 1;
    }

    return 0;
}