#pragma once
#ifndef __EVENTSTART_H__
#define __EVENTSTART_H__
#include "Event.h"

const std::string START_EVENT = "start";

class EventStart : public df::Event {

private:

public:
	// Create start event.
	EventStart();
};

#endif