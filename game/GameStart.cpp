#include "GameStart.h"
#include "dragonfly/EventKeyboard.h"
#include "dragonfly/WorldManager.h"
#include "dragonfly/GameManager.h"
#include "TowerBase.h"
#include "Crate.h"

// Constructor.
GameStart::GameStart() {
	// Setup sprite.
	setSprite("game-start");

	// Set object type.
	setType("GameStart");

	setAltitude(df::MAX_ALTITUDE);

	setLocation(df::CENTER_CENTER);
}

// Handles Keyboard events.
int GameStart::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*)p_e;

		if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			switch (p_keyboard_event->getKey()) {
			case df::Keyboard::SPACE:	// Play
				start();
				break;
			case df::Keyboard::ESCAPE:	// Quit
				GM.setGameOver();
				break;
			default:	// Key is not handled
				break;
			}
		}
		return 1;
	}

	return 0;
}

// Count down to end of "message"
void GameStart::start() {
	//new GameController;
	GC.reset();

	WM.markForDelete(this);
}

// Override default draw so as to not display "value".
int GameStart::draw() {
	return df::Object::draw();
}

