#pragma once

#include "ViewObject.h"

class HighestPoint : public df::ViewObject {
private:
    df::Vector m_sprite_size;

public:
    HighestPoint();
    int eventHandler(const df::Event* p_e) override;
    void updatePosition(df::Object* highest_obj);
    int draw() override;
};