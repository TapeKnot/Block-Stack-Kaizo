#pragma once
#include "dragonfly/ViewObject.h"
#include "GameController.h"

class GameStart : public df::ViewObject {

private:
	void start();

public:
	GameStart();
	int draw() override;
	int eventHandler(const df::Event* p_e) override;
};
