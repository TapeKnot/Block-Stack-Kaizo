#include "CreditsScreen.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "WorldManager.h"
#include "ResourceManager.h"

#include "GameStart.h"

CreditsScreen::CreditsScreen() {
	m_p_music = RM.getMusic("prize-music");
	if (m_p_music) m_p_music->play();
	
	setSprite("credits");

	// Set object type.
	setType("CreditsScreen");

	setAltitude(df::MAX_ALTITUDE);

	setLocation(df::CENTER_CENTER);
}

int CreditsScreen::eventHandler(const df::Event* p_e) {

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

void CreditsScreen::reset() {
	if (m_p_music) m_p_music->stop();

	new GameStart;
	WM.markForDelete(this);
}

int CreditsScreen::draw() {
	return df::Object::draw();
}
