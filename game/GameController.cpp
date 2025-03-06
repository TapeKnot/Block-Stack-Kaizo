#include "GameController.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Crate.h"
#include "EventStep.h"
#include "EventStack.h"
#include "EventStart.h"
#include "TowerBase.h"
#include "HighestPoint.h"
#include "GameEnd.h"
#include "Animation.h"
#include "BackgroundObject.h"
#include "Warning.h"
#include "FastScrollBar.h"

// Constructor
GameController::GameController() {
    // Initialize member variables
    m_stack_height = 0.0f;
    m_scroll_speed = 0.0f; // Example speed
    m_fast_scroll_mode = false;
    m_game_ended = false;

    // Initialize tower base
    m_p_tower_base = nullptr;
    m_p_highest_obj = nullptr;
    m_p_highest_point = nullptr;
    m_p_points = nullptr;

    // Initialize modifier
    m_p_modifier = nullptr;

    // Initialize shake controller
    m_p_shake_controller = new ShakeController;
}

GameController& GameController::getInstance() {
    static GameController single;
    return single;
}

// Reset game state
void GameController::reset() {

    // Reset stack height and position
    m_stack_height = INITIAL_STACK_HEIGHT;
    m_total_stacked = 0;

    // Reset scroll speed
    m_scroll_speed = 0.0;
    m_fast_scroll_mode = false;
    m_game_ended = false;

    // Reset tower base
    m_p_tower_base = new TowerBase;
    m_p_highest_obj = m_p_tower_base;
    m_p_tower_base->setPosition(
        df::Vector(DM.getHorizontal()/2, DM.getVertical() - m_stack_height));

    m_p_points = new Points();

    m_p_music = RM.getMusic("game-music");
    if (m_p_music) m_p_music->play();

    // Reset modifier
    m_p_modifier = nullptr;

    EventStart* e = new EventStart();
    WM.onEvent(e);

    new Warning();
    new FastScrollBar();

    // Spawn crate
    new Crate();
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

int GameController::getTotalStacked() const {
    return m_total_stacked;
}

void GameController::setTotalStacked(int new_total_stacked) {
    m_total_stacked = new_total_stacked;
}

bool GameController::getGameEnded() const {
    return m_game_ended;
}
void GameController::setGameEnded(bool new_game_ended) {
    m_game_ended = new_game_ended;
}

df::Object* GameController::getHighestObject() const {
    return m_p_highest_obj;
}

void GameController::setHighestObject(df::Object* new_obj) {
    m_p_highest_obj = new_obj;
}

// Successful drop method
void GameController::successfulDrop(float new_stack_position) {
    m_stack_height += 4;
    m_scroll_speed += (m_scroll_speed == 0) ? 0.05 : 0.001;
    m_total_stacked++;

    // 1-in-5 chance to spawn a modifier, or force spawn if 10 stacked
    bool force_modifier = m_total_stacked == 10;
    bool can_spawn_modifier = m_total_stacked >= 10 && m_p_modifier == nullptr;
    if (force_modifier || (can_spawn_modifier && rand() % 5 == 0)) {
        // Randomly select a modifier type and lifespan
        ModifierType mod_type = static_cast<ModifierType>(rand() % 3);
        int mod_lifespan = rand() % 300 + 150;
        m_p_modifier = new Modifier(mod_type, mod_lifespan);
    }

    // Shake screen
    m_p_shake_controller->shake(VERTICAL, 0.3, 0.8);

    // Spawn new crate
    new Crate();
}

void GameController::endGame() {
    // Stop music
    if (m_p_music) m_p_music->stop();

    // Shake screen
    m_p_shake_controller->shake(HORIZONTAL, 1, 0.9);

    // End game
    m_game_ended = true;
    new GameEnd(m_p_points->getValue());
}

// Event handler method
int GameController::eventHandler(const df::Event *p_e) {
    // Handle step events
    if (p_e->getType() == df::STEP_EVENT) {
        if (m_game_ended) {
            return 1;
        }

        m_stack_height -= m_scroll_speed;

        if (m_p_highest_obj->getPosition().getY() <= DM.getVertical() / 2 && m_fast_scroll_mode == false) {
            m_scroll_speed *= 4;
            m_fast_scroll_mode = true;
        }
        else if (m_p_highest_obj->getPosition().getY() > DM.getVertical() / 2 && m_fast_scroll_mode == true) {
            m_scroll_speed /= 4;
            m_fast_scroll_mode = false;
        }

        if (rand() % 50 == 0) {
            if (m_total_stacked < 20) {
                new BackgroundObject(STAR);
            } else {
                int rand_num = rand() % 10;
                if (rand_num == 0) {
                    new BackgroundObject(PLANET);
                } else {
                    new BackgroundObject(STAR);
                }
            }
        }
        
        return 1;
    }

    else if (p_e->getType() == STACK_EVENT) {
        const EventStack* p_stack_event = dynamic_cast<const EventStack*>(p_e);
        Crate* p_stacked_crate = p_stack_event->getCrate();
        float pos = p_stacked_crate->getPosition().getX();

        setHighestObject(p_stacked_crate);
        //m_p_highest_point->updatePosition(m_p_highest_obj);

        successfulDrop(pos);

        return 1;
    }

    return 0; // Return appropriate value
}

// Override draw method
int GameController::draw() { return 0; }