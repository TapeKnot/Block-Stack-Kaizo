#include "Retries.h"
#include "EventStep.h"
#include "EventStart.h"

// Constructor.
Retries::Retries() {
	setLocation(df::BOTTOM_LEFT);
	setPosition(df::Vector(getPosition().getX(), getPosition().getY() - 1));
	setViewString(RETRIES_STRING);
	setColor(df::GREEN);

	// Set object type.
	setType("Retries");
}

// Handles events.
int Retries::eventHandler(const df::Event* p_e) {
	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}

	if (p_e->getType() == START_EVENT) {
		setValue(getValue() + 1);
		return 1;
	}

	return 0;
}