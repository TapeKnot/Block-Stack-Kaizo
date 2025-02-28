#include "GameController.h"
#include "DisplayManager.h"
#include "SceneController.h"
#include "Crate.h"
#include "EventStep.h"

// Constructor
GameController::GameController(SceneController *p_scene_controller) {
    // Initialize member variables
    m_stack_height = 0;
    m_stack_position = 0;
    m_scroll_speed = 0.0; // Example speed
    m_p_scene_controller = p_scene_controller;

    // Initialize tower base
    m_p_tower_base = new df::Object();
    m_p_tower_base->setSprite("tower-base");
    m_p_tower_base->setSolidness(df::SOFT);
}

// Destructor
GameController::~GameController() {}

// Reset game state
void GameController::reset() {
    // Reset stack height and position
    m_stack_height = INITIAL_STACK_HEIGHT;
    m_stack_position = DM.getHorizontal()/2;

    // Reset scroll speed
    m_scroll_speed = 0.0;

    // Reset tower base
    m_p_tower_base->setPosition(
        df::Vector(DM.getHorizontal()/2, DM.getVertical() - m_stack_height));

    // Spawn crate
    new Crate(this);
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

// Successful drop method
void GameController::successfulDrop(float new_stack_position) {
    m_stack_position = new_stack_position;
    m_stack_height += 4;
    m_scroll_speed += (m_scroll_speed == 0) ? 0.02 : 0.005;
    new Crate(this);
}

// Event handler method
int GameController::eventHandler(const df::Event *p_e) {
    // Handle step events
    if (p_e->getType() == df::STEP_EVENT) {
        printf("stack height: %f\n", m_stack_height);
        m_stack_height -= m_scroll_speed;
        m_p_tower_base->setVelocity(df::Vector(0, m_scroll_speed));

        if (m_stack_height < 0 && m_p_scene_controller->getScene() == SCENE_PLAY) {
            m_scroll_speed = 0;
            m_p_scene_controller->end();
        }

        return 1;
    }

    return 0; // Return appropriate value
}

// Override draw method
int GameController::draw() { return 0; }