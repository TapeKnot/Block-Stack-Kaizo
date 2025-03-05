#include "EventStep.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "GameController.h"

#include "HighestPoint.h"

HighestPoint::HighestPoint() {
	// Set sprite to make object visible.
	setSprite("highest-point");

	// Set object type.
	setType("HighestPoint");

	setAltitude(3);

	m_sprite_size = df::Vector(
		getAnimation().getSprite()->getWidth(),
		getAnimation().getSprite()->getHeight()
	);
}

int HighestPoint::eventHandler(const df::Event* p_e) {
	// Handle step events
	if (p_e->getType() == df::STEP_EVENT) {
		setVelocity(df::Vector(0, GC.getScrollSpeed()));

		return 1;
	}

	return 0;
}

void HighestPoint::updatePosition(df::Object* highest_obj) {

	df::Vector obj_pos = highest_obj->getPosition();

	printf("Object Pos: X = %f, Y = %f\n", obj_pos.getX(), obj_pos.getY());

	df::Vector obj_size = df::Vector(
		highest_obj->getAnimation().getSprite()->getWidth(),
		highest_obj->getAnimation().getSprite()->getHeight()
	);

	df::Vector new_pos;

	if (obj_pos.getX() <= (DM.getHorizontal() / 2)) {
		new_pos.setX(obj_pos.getX() + (obj_size.getX() / 2) /* + (m_sprite_size.getX() / 2)*/);
		//getAnimation().setIndex(2);
	}
	else {
		new_pos.setX(obj_pos.getX() - (obj_size.getX() / 2) /* - (m_sprite_size.getX() / 2)*/);
		//getAnimation().setIndex(1);
	}

	new_pos.setY(obj_pos.getY() /* - (obj_size.getY() / 2)*/);

	printf("New Position: X = %f, Y = %f\n", new_pos.getX(), new_pos.getY());

	setPosition(new_pos);
}

int HighestPoint::draw() {
	return df::Object::draw();
}
