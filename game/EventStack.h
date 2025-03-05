#pragma once
#ifndef __EVENTSTACK_H__
#define __EVENTSTACK_H__
#include "Event.h"
#include "Crate.h"

const std::string STACK_EVENT = "stack";

class EventStack : public df::Event {

private:
	Crate* m_p_crate;		// Crate that was stacked.

public:
	// Create stack event with m_p_crate as null.
	EventStack();

	// Create stack event with m_p_crate as p_crate.
	EventStack(Crate* p_crate);

	// Set crate that was stacked.
	void setCrate(Crate* p_new_crate);

	// Return crate that was stacked.
	Crate* getCrate() const;
};

#endif