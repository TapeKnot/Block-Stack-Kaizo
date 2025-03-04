#pragma once

#include "dragonfly/ViewObject.h"

class HighestPoint : public df::ViewObject {
private:

public:
    HighestPoint();
    int eventHandler(const df::Event* p_e) override;
    int draw() override;
};