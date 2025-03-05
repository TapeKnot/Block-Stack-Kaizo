#pragma once

#include "ViewObject.h"

const float STACK_HEIGHT_WARNING = 7.0; // Stack height to show warning text.

class Warning : public df::ViewObject {
private:
    bool show;
public:
    Warning();
    int eventHandler(const df::Event* p_e) override;
    int draw() override;
};