#include "SceneController.h"
#include "Vector.h"
#include "GameManager.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventKeyboard.h"
#include "GameController.h"

SceneController::SceneController() {
    // Initialize scene to start.
    m_current_scene = SCENE_START;

    // Make sure objects pointers are null
    m_p_game_start = nullptr;
    m_p_insert_coin = nullptr;
    m_p_game_over = nullptr;

    // Create game controller.
    m_p_game_controller = new GameController(this);

    start();
}

SceneController::~SceneController() {
    // Clean up resources if necessary
}

Scene SceneController::getScene() const {
    return m_current_scene;
}

void SceneController::start() {
    m_current_scene = SCENE_START;

    // Remove game over logo if present.
    if (m_p_game_over != nullptr) {
        WM.markForDelete(m_p_game_over);
        m_p_game_over = nullptr;
    }

    // Create game start logo.
    m_p_game_start = new df::Object();
    m_p_game_start->setSprite("game-start");
    m_p_game_start->setPosition(df::Vector(DM.getHorizontal()/2, DM.getVertical()/2 - 3));
    m_p_game_start->setAltitude(2);

    // Create insert coin logo.
    m_p_insert_coin = new df::Object();
    m_p_insert_coin->setSprite("insert-coin");
    m_p_insert_coin->setPosition(df::Vector(DM.getHorizontal()/2, DM.getVertical()/2 + 7));
    m_p_game_start->setAltitude(2);

    // Reset game state.
    m_p_game_controller->reset();
}

void SceneController::play() {
    m_current_scene = SCENE_PLAY;

    // Remove game start and insert coin logos.
    WM.markForDelete(m_p_game_start);
    WM.markForDelete(m_p_insert_coin);

    // end();
}

void SceneController::end() {
    m_current_scene = SCENE_END;

    // Create game over logo.
    m_p_game_over = new df::Object();
    m_p_game_over->setSprite("game-over");
    m_p_game_over->setPosition(df::Vector(DM.getHorizontal()/2, DM.getVertical()/2));
    m_p_game_start->setAltitude(2);
}

int SceneController::eventHandler(const df::Event *p_e) {
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard *p_keyboard_event = dynamic_cast<const df::EventKeyboard *>(p_e);
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            switch (p_keyboard_event->getKey()) {
                case df::Keyboard::ESCAPE:
                    GM.setGameOver();
                    return 1; // Exit game
                case df::Keyboard::SPACE:
                    if (m_current_scene == SCENE_START) {
                        m_current_scene = SCENE_PLAY;
                        play();
                    } else if (m_current_scene == SCENE_END) {
                        m_current_scene = SCENE_START;
                        start();
                    }
                    return 1; // Continue game
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}

int SceneController::draw() {
    return 0;
}