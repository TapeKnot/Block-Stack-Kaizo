#include "PrizeScreen.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "WorldManager.h"

#include "GameStart.h"

PrizeScreen::PrizeScreen(int points) {
	if (points < 10) {			// 0 crates stacked.
		setSprite("prize-nothing");
	}
	else if (points < 50) {		// 1-4 crates stacked.
		setSprite("prize-toilet-paper");
	}
	else if (points < 100) {	// 5-9 crates stacked.
		setSprite("prize-eggs");
	}
	else if (points < 150) {	// 10-14 crates stacked.
		setSprite("prize-socks");
	}
	else if (points < 250) {	// 15-24 crates stacked.
		setSprite("prize-otter");
	}
	else if (points < 300) {	// 25-29 crates stacked.
		setSprite("prize-crown");
	}
	else if (points < 350) {	// 30-34 crates stacked.
		setSprite("prize-liberty");
	}
	else {						// 35+ crates stacked.
		setSprite("prize-cool");
	}

	// Set object type.
	setType("PrizeScreen");

	setAltitude(df::MAX_ALTITUDE);

	setLocation(df::CENTER_CENTER);
}

int PrizeScreen::eventHandler(const df::Event* p_e) {

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

void PrizeScreen::reset() {
	new GameStart;
	WM.markForDelete(this);
}

int PrizeScreen::draw() {
	return df::Object::draw();
}
