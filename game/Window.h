#pragma once

#include "Object.h"

const int WINDOW_WIDTH = 50;

class Window : public df::Object {
public:
    Window();
    int draw() override;
};