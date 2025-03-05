#pragma once

#include "ViewObject.h"
#include "Window.h"

enum ModifierType {
    SPEEDY,
    SWING,
    WINDOW
};

class Modifier : public df::ViewObject {
    private:
        ModifierType m_modifier_type;
        int m_lifespan;
        Window* m_p_window;
    public:
        Modifier(ModifierType type, int lifespan);
        int eventHandler(const df::Event* p_e) override;
        ModifierType getModifierType() const;
        void setModifierType(ModifierType newType);
};