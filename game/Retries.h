#pragma once
#include "ViewObject.h"
#include "Event.h"

#define RETRIES_STRING "Cash Spent: $"

class Retries : public df::ViewObject {

public:
	Retries();
	int eventHandler(const df::Event* p_e) override;
};