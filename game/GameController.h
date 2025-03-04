#pragma once
#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__
#define GC GameController::getInstance()
#include "dragonfly/Object.h"
#include "Crate.h"

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
    Crate* m_p_top_crate;

public:
    // Get the singleton instance of the GameManager.
    static GameController& getInstance();

    void reset();
    float getStackPosition() const;
    float getStackHeight() const;
    void increaseStackHeight(float delta);
    float getScrollSpeed() const;
    void setScrollSpeed(float new_speed);
    Crate* getTopCrate() const;
    void setTopCrate(Crate* new_crate);
    void successfulDrop(float new_stack_position);
    int eventHandler(const df::Event *p_e) override;
    int draw() override;
};

#endif