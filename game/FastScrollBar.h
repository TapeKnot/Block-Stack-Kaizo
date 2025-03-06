#pragma once

#include "ViewObject.h"

class FastScrollBar : public df::ViewObject {
private:
public:
    FastScrollBar();
    int eventHandler(const df::Event* p_e) override;
    int draw() override;
};