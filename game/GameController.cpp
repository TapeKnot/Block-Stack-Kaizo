#include "GameController.h"
#include "DisplayManager.h"
#include "Crate.h"
#include "EventStep.h"
#include "TowerBase.h"
#include "WorldManager.h"

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

    // Initialize modifier
    m_p_modifier = nullptr;
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
    m_fast_scroll_mode = false;

    // Reset tower base
    m_p_tower_base = new TowerBase;
    m_p_tower_base->setPosition(
        df::Vector(DM.getHorizontal()/2, DM.getVertical() - m_stack_height));

    // Reset modifier
    if (m_p_modifier != nullptr)
        WM.markForDelete(m_p_modifier);
    m_p_modifier = nullptr;

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

bool GameController::getFastScrollMode() const {
    return m_fast_scroll_mode;
}

Modifier* GameController::getModifier() const {
    return m_p_modifier;
}

void GameController::setModifier(Modifier* new_modifier) {
    m_p_modifier = new_modifier;
}

Crate* GameController::getTopCrate() const {
    return m_p_top_crate;
}

void GameController::setTopCrate(Crate* new_crate) {
    m_p_top_crate = new_crate;
}

// Successful drop method
void GameController::successfulDrop(float new_stack_position) {
    m_stack_position = new_stack_position;
    m_stack_height += 4;
    m_scroll_speed += (m_scroll_speed == 0) ? 0.05 : 0.001;

    // 1-in-5 chance to spawn a modifier
    if (m_p_modifier == nullptr && rand() % 5 == 0) {
        // Randomly select a modifier type and lifespan
        ModifierType mod_type = static_cast<ModifierType>(rand() % 3);
        int mod_lifespan = rand() % 300 + 150;
        m_p_modifier = new Modifier(mod_type, mod_lifespan);
    }

    new Crate();
}

// Event handler method
int GameController::eventHandler(const df::Event *p_e) {
    // Handle step events
    if (p_e->getType() == df::STEP_EVENT) {
        m_stack_height -= m_scroll_speed;

        if (m_p_top_crate != nullptr) {
            if (m_p_top_crate->getPosition().getY() <= DM.getVertical() / 2 && m_fast_scroll_mode == false) {
                m_scroll_speed *= 4;
                m_fast_scroll_mode = true;
            }
            else if (m_p_top_crate->getPosition().getY() > DM.getVertical() / 2 && m_fast_scroll_mode == true) {
                m_scroll_speed /= 4;
                m_fast_scroll_mode = false;
            }
        }
        
        return 1;
    }

    return 0; // Return appropriate value
}

// Override draw method
int GameController::draw() { return 0; }