#pragma once
#include "ViewObject.h"
#include "GameController.h"
#include "Music.h"

class GameStart : public df::ViewObject {

private:
	void start();
	df::Music* m_p_music;

public:
	GameStart();
	int draw() override;
	int eventHandler(const df::Event* p_e) override;
};
