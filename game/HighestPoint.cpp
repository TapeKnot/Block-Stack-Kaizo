#include "EventStep.h"
#include "WorldManager.h"
#include "GameController.h"
#include "Crate.h"

#include "HighestPoint.h"

HighestPoint::HighestPoint() {

	// Setup sprite
	setSprite("highest-point");

	// Set object type.
	setType("HighestPoint");

	df::Vector sprite_size = df::Vector(
		getAnimation().getSprite()->getWidth(),
		getAnimation().getSprite()->getHeight()
	);

	df::Vector new_pos;
	df::Vector top_crate_pos = GC.getTopCrate()->getPosition();
	df::Vector top_crate_size = GC.getTopCrate()->getCrateSize();

	new_pos.setX(top_crate_pos.getX() - (top_crate_size.getX() / 2) - (sprite_size.getX() / 2));
	new_pos.setX(top_crate_pos.getY() + (top_crate_size.getY() / 2));

	setPosition(new_pos);
}

int HighestPoint::eventHandler(const df::Event* p_e) {
	// Handle step events
	if (p_e->getType() == df::STEP_EVENT) {
		setVelocity(df::Vector(0, GC.getScrollSpeed()));

		return 1;
	}

	return 0;
}

int HighestPoint::draw() {
	return df::Object::draw();
}
