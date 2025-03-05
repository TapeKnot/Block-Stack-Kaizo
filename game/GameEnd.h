#pragma once

#include "ViewObject.h"

class GameEnd : public df::ViewObject {
private:
    int m_points;

public:
    GameEnd(int points);
    ~GameEnd();
    void reset();
    int eventHandler(const df::Event* p_e) override;
    int draw() override;
};