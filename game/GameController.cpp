#include "GameController.h"
#include "dragonfly/DisplayManager.h"
#include "Crate.h"
#include "dragonfly/EventStep.h"
#include "TowerBase.h"

// Constructor
GameController::GameController() {
    // Initialize member variables
    m_stack_height = 0.0f;
    m_stack_position = 0.0f;
    m_scroll_speed = 0.0f; // Example speed
    m_fast_scroll_mode = false;

    // Initialize tower base
    m_p_tower_base = nullptr;
    m_p_top_crate = nullptr;
}

GameController& GameController::getInstance() {
    static GameController single;
    return single;
}

// Reset game state
void GameController::reset() {

    // Reset stack height and position
    m_stack_height = INITIAL_STACK_HEIGHT;
    m_stack_position = DM.getHorizontal()/2;

    // Reset scroll speed
    m_scroll_speed = 0.0;

    // Reset tower base
    m_p_tower_base = new TowerBase;
    m_p_top_crate = m_p_tower_base; // Ensures only the first crate can stack on the tower base.
    m_p_tower_base->setPosition(
        df::Vector(DM.getHorizontal()/2, DM.getVertical() - m_stack_height));

    // Spawn crate
    new Crate();
}

// Get stack position method
float GameController::getStackPosition() const {
    return m_stack_position;
}

// Get stack height method
float GameController::getStackHeight() const {
    return m_stack_height;
}

// Increase stack height method
void GameController::increaseStackHeight(float delta) {
    m_stack_height += delta;
}

// Get scroll speed method
float GameController::getScrollSpeed() const {
    return m_scroll_speed;
}

void GameController::setScrollSpeed(float new_speed) {
    m_scroll_speed = new_speed;
}

df::Object* GameController::getTopCrate() const {
    return m_p_top_crate;
}

void GameController::setTopCrate(df::Object* new_crate) {
    m_p_top_crate = new_crate;
}

// Successful drop method
void GameController::successfulDrop(float new_stack_position) {
    m_stack_position = new_stack_position;
    m_stack_height += 4;
    m_scroll_speed += (m_scroll_speed == 0) ? 0.02 : 0.005;
    new Crate();
}

// Event handler method
int GameController::eventHandler(const df::Event *p_e) {
    // Handle step events
    if (p_e->getType() == df::STEP_EVENT) {
        //printf("stack height: %f\n", m_stack_height);
        m_stack_height -= m_scroll_speed;

        //printf("Fast Mode: %d\n", m_fast_scroll_mode);

        if (m_p_top_crate->getPosition().getY() <= DM.getVertical() / 2 && m_fast_scroll_mode == false) {
            m_scroll_speed *= 4;
            m_fast_scroll_mode = true;
        }
        else if (m_p_top_crate->getPosition().getY() > DM.getVertical() / 2 && m_fast_scroll_mode == true) {
            m_scroll_speed /= 4;
            m_fast_scroll_mode = false;
        }

        return 1;
    }

    return 0; // Return appropriate value
}

// Override draw method
int GameController::draw() { return 0; }