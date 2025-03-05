#include "Warning.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "DisplayManager.h"

#include "GameStart.h"

Warning::Warning() {
	setSprite("warning");

	// Set object type.
	setType("Warning");

	setAltitude(0);

	setPosition(df::Vector(DM.getHorizontal() / 2, DM.getVertical() - 5));
}

int Warning::draw() {
	return df::Object::draw();
}
