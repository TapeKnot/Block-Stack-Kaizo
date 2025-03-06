#pragma once

#include "Object.h"

enum ShakeDirection {
    HORIZONTAL,
    VERTICAL
};

class ShakeController : public df::Object {
    private:
        ShakeDirection m_direction;
        float m_intensity;
        float m_decay;
        int m_steps;
    public:
        ShakeController();
        int eventHandler(const df::Event *p_e) override;
        void shake(ShakeDirection direction, float intensity, float decay);
};