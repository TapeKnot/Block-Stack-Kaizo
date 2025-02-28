#pragma once

#include "ViewObject.h"
class GameController;

enum Scene {
    SCENE_START,
    SCENE_PLAY,
    SCENE_END
};

class SceneController : public df::ViewObject {
private:
    // The current scene.
    Scene m_current_scene;
    // The game start logo.
    df::Object *m_p_game_start;
    // The insert coin logo.
    df::Object *m_p_insert_coin;
    // The game over logo.
    df::Object *m_p_game_over;
    // The game controller.
    GameController *m_p_game_controller;

public:
    SceneController();
    ~SceneController();
    Scene getScene() const;
    void start();
    void play();
    void end();
    int eventHandler(const df::Event *p_e) override;
    int draw() override;
};