#include "ShakeController.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "ViewObject.h"
#include "DisplayManager.h"
#include "LogManager.h"

// Constructor
ShakeController::ShakeController() {
    // Set object properties
    setType("ShakeController");
    setSolidness(df::SPECTRAL);

    // Initialize shake properties
    m_direction = HORIZONTAL;
    m_intensity = 0;
    m_decay = 0;
    m_steps = 0;
}

// Event handler
int ShakeController::eventHandler(const df::Event *p_e) {
    // Check if this is a step event
    if (p_e->getType() == df::STEP_EVENT) {
        if (m_intensity > 0.05) {
            // Shake the view
            df::Box new_box = WM.getView();
            if (m_direction == HORIZONTAL)
                new_box.setCorner(df::Vector(sin(m_steps) * m_intensity, 0));
            else
                new_box.setCorner(df::Vector(0, sin(m_steps) * m_intensity));
            WM.setView(new_box);

            // Decrease intensity
            m_intensity *= m_decay;
        } else {
            // Reset view and stop shaking
            df::Box new_box = WM.getView();
            new_box.setCorner(df::Vector(0, 0));
            WM.setView(new_box);
            m_intensity = 0;
        }

        m_steps++;
        return 1;  // Event handled
    }
    
    // If not handled, pass to parent
    return df::Object::eventHandler(p_e);
}

void ShakeController::shake(ShakeDirection direction, float intensity, float decay) {
    m_direction = direction;
    m_intensity = intensity;
    m_decay = decay;
}