#include "Modifier.h"
#include "EventStep.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "GameController.h"

Modifier::Modifier(ModifierType type, int lifespan) {
    setModifierType(type);
    m_lifespan = lifespan;    // Initialize lifespan to 0
    setType("modifier");
    setSolidness(df::SPECTRAL);
    setAltitude(4);  // Draw above most game objects
    setValue(lifespan / 30);
    setDrawValue();

    switch (m_modifier_type) {
        case SPEEDY:
            setViewString("SPEEDY:");
            break;
        case SWING:
            setViewString("SWING:");
            break;
        case WINDOW:
            setViewString("WINDOW:");
            break;
    }

    if (m_modifier_type == WINDOW) {
        m_p_window = new Window();
    } else {
        m_p_window = nullptr;
    }

    setPosition(df::Vector(DM.getHorizontal() / 2, 1));
}

int Modifier::eventHandler(const df::Event* p_e) {
    // Check if this is a step event
    if (p_e->getType() == df::STEP_EVENT) {
        // Decrement lifespan if it's positive
        if (m_lifespan > 0) {
            m_lifespan--;
            setValue(m_lifespan / 30);
        } else {
            if (m_p_window != nullptr)
                WM.markForDelete(m_p_window);
            GC.setModifier(nullptr);
            WM.markForDelete(this);
            return 1;
        }
        return 1;
    }
    
    // If not a step event, let parent handle it
    return df::ViewObject::eventHandler(p_e);
}

ModifierType Modifier::getModifierType() const {
    return m_modifier_type;
}

void Modifier::setModifierType(ModifierType newType) {
    m_modifier_type = newType;
}