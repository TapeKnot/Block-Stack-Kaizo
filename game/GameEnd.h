#pragma once

#include "ViewObject.h"
#include "Sound.h"

class GameEnd : public df::ViewObject {
private:
    int m_points;
    df::Sound* m_p_sound;

public:
    GameEnd(int points);
    ~GameEnd();
    void reset();
    int eventHandler(const df::Event* p_e) override;
    int draw() override;
};