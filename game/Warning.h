#pragma once

#include "ViewObject.h"

class Warning : public df::ViewObject {
private:
public:
    Warning();

    int draw() override;
};