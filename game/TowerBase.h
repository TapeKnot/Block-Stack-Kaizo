#include "dragonfly/Object.h"

class TowerBase : public df::Object {
private:

public:
    TowerBase();
    int eventHandler(const df::Event* p_e) override;
};