#pragma once
#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__
#define GC GameController::getInstance()
#include "Object.h"
#include "Crate.h"
#include "HighestPoint.h"
#include "Points.h"
#include "Music.h"

const float INITIAL_STACK_HEIGHT = 2.0;

class GameController : public df::Object {
private:
    GameController();							// No constructing.
    GameController(GameController const&);		// No copying.
    void operator=(GameController const&);		// No assigning.

    float m_stack_height;
    float m_stack_position;
    float m_scroll_speed;
    bool m_fast_scroll_mode;
    df::Object *m_p_tower_base;
    df::Object* m_p_highest_obj;
    HighestPoint* m_p_highest_point;
    Points* m_p_points;
    df::Music* m_p_music;

public:
    // Get the singleton instance of the GameManager.
    static GameController& getInstance();

    void reset();
    float getStackPosition() const;
    float getStackHeight() const;
    void increaseStackHeight(float delta);
    float getScrollSpeed() const;
    void setScrollSpeed(float new_speed);
    df::Object* getHighestObject() const;
    void setHighestObject(df::Object* new_obj);
    void successfulDrop(float new_stack_position);
    void endGame();
    int eventHandler(const df::Event *p_e) override;
    int draw() override;
};

#endif