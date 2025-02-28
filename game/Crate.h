#include "Object.h"
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
    // The game controller.
    GameController *m_p_game_controller;
public:
    Crate(GameController *p_game_controller);
    ~Crate();
    void drop();;
    int eventHandler(const df::Event *p_e) override;
};