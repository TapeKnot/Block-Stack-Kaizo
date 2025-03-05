#pragma once

#include "ViewObject.h"

class PrizeScreen : public df::ViewObject {
private:

public:
    PrizeScreen(int points);
    int eventHandler(const df::Event* p_e) override;
    void reset();
    int draw() override;
};