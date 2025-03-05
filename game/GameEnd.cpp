#include "GameEnd.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "WorldManager.h"
#include "ResourceManager.h"

#include "PrizeScreen.h"
#include "GameController.h"

GameEnd::GameEnd(int points) {
	m_p_sound = RM.getSound("crate-explode");
	if (m_p_sound) m_p_sound->play();

	// Setup sprite
	setSprite("game-over");

	// Set object type.
	setType("GameEnd");

	setAltitude(df::MAX_ALTITUDE);

	setLocation(df::CENTER_CENTER);

	GC.setScrollSpeed(0.0f);

	m_points = points;
}

GameEnd::~GameEnd() {
	df::ObjectList objects = WM.getAllObjects();

	for (int i = 0; i < objects.getCount(); i++) {
		Object* p_o = objects[i];

		if (p_o->getType() == "Crate" || p_o->getType() == "TowerBase" || p_o->getType() == "HighestPoint" || p_o->getType() == "Points") {
			WM.markForDelete(p_o);
		}
	}
}

int GameEnd::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event = dynamic_cast<const df::EventKeyboard*>(p_e);

		if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			if (p_keyboard_event->getKey() == df::Keyboard::SPACE) {
				reset();
				return 1;
			}
		}
    }

    return 0;
}

void GameEnd::reset() {
	if (m_p_sound) m_p_sound->stop();

	new PrizeScreen(m_points);
	WM.markForDelete(this);
}

int GameEnd::draw() {
	return df::Object::draw();
}
