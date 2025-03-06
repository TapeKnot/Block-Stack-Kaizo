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
    int stack_position = GC.getHighestObject()->getPosition().getX();

    for (int i = 0; i < DM.getVertical(); i++) {
        // Draw view blocking characters
        for (int j = -DM.getHorizontal(); j < -WINDOW_WIDTH / 2; j++)
            DM.drawCh(df::Vector(j + stack_position, i), ' ', df::BLACK);
        for (int j = WINDOW_WIDTH / 2; j < DM.getHorizontal(); j++)
            DM.drawCh(df::Vector(j + stack_position, i), ' ', df::BLACK);

        // Draw window border
        DM.drawCh(df::Vector(-WINDOW_WIDTH / 2 + stack_position, i), '.', df::WHITE);
        DM.drawCh(df::Vector(WINDOW_WIDTH / 2 + stack_position, i), '.', df::WHITE);

    }
    return 0;
}