#include "Window.h"
#include "DisplayManager.h"
#include "EventStep.h"
#include "GameController.h"

Window::Window() {
    setType("Window");
    setSolidness(df::SPECTRAL);
    setAltitude(3);
}

int Window::draw() {

    for (int i = 0; i < DM.getVertical(); i++) {
        // Draw view blocking characters
        for (int j = -DM.getHorizontal(); j < -WINDOW_WIDTH / 2; j++)
            DM.drawCh(df::Vector(j + GC.getStackPosition(), i), ' ', df::BLACK);
        for (int j = WINDOW_WIDTH / 2; j < DM.getHorizontal(); j++)
            DM.drawCh(df::Vector(j + GC.getStackPosition(), i), ' ', df::BLACK);

        // Draw window border
        DM.drawCh(df::Vector(-WINDOW_WIDTH / 2 + GC.getStackPosition(), i), '.', df::WHITE);
        DM.drawCh(df::Vector(WINDOW_WIDTH / 2 + GC.getStackPosition(), i), '.', df::WHITE);

    }
    return 0;
}