#include "GameEnd.h"
#include "dragonfly/EventStep.h"
#include "dragonfly/EventKeyboard.h"
#include "dragonfly/WorldManager.h"

#include "GameStart.h"

GameEnd::GameEnd() {
	// TODO: Play game over sound

	// Setup sprite
	setSprite("game-over");

	// Set object type.
	setType("GameEnd");

	setLocation(df::CENTER_CENTER);

	GC.setScrollSpeed(0.0f);
}

GameEnd::~GameEnd() {
	df::ObjectList crates = WM.objectsOfType("Crate");

	for (int i = 0; i < crates.getCount(); i++) {
		WM.markForDelete(crates[i]);
	}

	df::ObjectList tower_bases = WM.objectsOfType("TowerBase");

	for (int i = 0; i < tower_bases.getCount(); i++) {
		WM.markForDelete(tower_bases[i]);
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
	new GameStart;
	WM.markForDelete(this);
}

int GameEnd::draw() {
	return df::Object::draw();
}
