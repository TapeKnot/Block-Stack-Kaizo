#pragma once

#include "ViewObject.h"
class SceneController;

const float INITIAL_STACK_HEIGHT = 2.0;

class GameController : public df::ViewObject {
private:
    float m_stack_height;
    float m_stack_position;
    float m_scroll_speed;
    df::Object *m_p_tower_base;
    SceneController *m_p_scene_controller;
public:
    GameController(SceneController *p_scene_controller);
    ~GameController();
    void reset();
    float getStackPosition() const;
    float getStackHeight() const;
    void increaseStackHeight(float delta);
    float getScrollSpeed() const;
    void successfulDrop(float new_stack_position);
    int eventHandler(const df::Event *p_e) override;
    int draw() override;
};