#pragma once

#include "ViewObject.h"
#include "Music.h"

class CreditsScreen : public df::ViewObject {
private:

public:
    CreditsScreen();
    int eventHandler(const df::Event* p_e) override;
    void reset();
    int draw() override;
    df::Music* m_p_music;
};
