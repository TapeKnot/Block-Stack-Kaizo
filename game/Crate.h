#include "dragonfly/Object.h"
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
public:
    Crate();
    void step();
    void drop();
    void stack();
    int eventHandler(const df::Event *p_e) override;
};