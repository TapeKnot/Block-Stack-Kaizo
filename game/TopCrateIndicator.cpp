//#include "dragonfly/EventStep.h"
//#include "dragonfly/WorldManager.h"
//#include "GameController.h"
//
//#include "TopCrateIndicator.h"
//
//TopCrateIndicator::TopCrateIndicator() {
//
//	// Setup sprite
//	setSprite("top-crate-indicator");
//
//	// Set object type.
//	setType("TopCrateIndicator");
//
//	df::Vector pos;
//	df::Vector high_point_pos = GC.getTopCrate()->getPosition();
//
//	pos.setX(high_point_pos.getX() - 2);
//
//	pos.setY(high_point_pos.getY() + 
//
//	setPosition();
//}
//
//int GameEnd::eventHandler(const df::Event* p_e) {
//
//	if (p_e->getType() == df::KEYBOARD_EVENT) {
//		const df::EventKeyboard* p_keyboard_event = dynamic_cast<const df::EventKeyboard*>(p_e);
//
//		if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
//			if (p_keyboard_event->getKey() == df::Keyboard::SPACE) {
//				reset();
//				return 1;
//			}
//		}
//	}
//
//	return 0;
//}
//
//void GameEnd::reset() {
//	new GameStart;
//	WM.markForDelete(this);
//}
//
//int GameEnd::draw() {
//	return df::Object::draw();
//}
