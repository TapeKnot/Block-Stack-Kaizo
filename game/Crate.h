#pragma once
#ifndef __CRATE_H__
#define __CRATE_H__
#include "Object.h"
#include "Sound.h"
class GameController;

enum Status {
    MOVING,
    FALLING,
    STACKED
};

class Crate : public df::Object {
private:
    df::Vector m_crate_size;
    Status m_status;
    float m_target_height;
    float m_progress;
    float m_progress_speed;
public:
    Crate();
    df::Vector getCrateSize() const;
    void step();
    void drop();
    void stack();
    int eventHandler(const df::Event *p_e) override;
};

#endif