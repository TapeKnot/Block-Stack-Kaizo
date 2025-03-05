#include "EventStack.h"

	// Create stack event with m_crate as null.
	EventStack::EventStack() {
		setType(STACK_EVENT);
		m_p_crate = nullptr;
	}

	// Create stack event with m_crate as p_crate.
	EventStack::EventStack(Crate* p_crate) {
		setType(STACK_EVENT);
		m_p_crate = p_crate;
	}

	// Set crate that was stacked.
	void EventStack::setCrate(Crate* p_new_crate) {
		m_p_crate = p_new_crate;
	}

	// Return crate that was stacked.
	Crate* EventStack::getCrate() const {
		return m_p_crate;
	}