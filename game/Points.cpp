#include "Points.h"
#include "EventStep.h"
#include "EventStack.h"

// Constructor.
Points::Points() {
	setLocation(df::BOTTOM_RIGHT);
	setPosition(df::Vector(getPosition().getX(), getPosition().getY() - 1));
	setViewString(POINTS_STRING);
	setColor(df::YELLOW);

	// Set object type.
	setType("Points");
}

// Handles events.
int Points::eventHandler(const df::Event* p_e) {
	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}

	if (p_e->getType() == STACK_EVENT) {
		setValue(getValue() + 10);
		return 1;
	}

	return 0;
}