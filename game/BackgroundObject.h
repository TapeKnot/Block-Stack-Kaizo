#pragma once

#include "Object.h"

enum BackgroundObjectType {
    STAR,
    PLANET
};

class BackgroundObject : public df::Object {
    private:
        BackgroundObjectType m_background_object_type;
        float m_speed_modifier;
    public:
        BackgroundObject(BackgroundObjectType background_object_type);
        int eventHandler(const df::Event *p_e) override;
};