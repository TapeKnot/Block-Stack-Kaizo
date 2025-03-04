#pragma once

#include "dragonfly/ViewObject.h"

class GameEnd : public df::ViewObject {
private:

public:
    GameEnd();
    ~GameEnd();
    void reset();
    int eventHandler(const df::Event* p_e) override;
    int draw() override;
};