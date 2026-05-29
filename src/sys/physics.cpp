#include "physics.hpp"
#include "../util/gamecontext.hpp"

namespace ECS {

bool PhysicsSystem_t::update(GameContext_t& g) const {
    auto& physicsComponents = g.getPhysicsComponent();
    for (auto& phy : physicsComponents) {
        phy.x += phy.vx;
        phy.y += phy.vy;
        
        // Colisiones con bordes
        if (phy.x >= 640 - 16) {
            phy.x = 640 - 16;
            phy.vx = -phy.vx;
        }
        if (phy.y >= 360 - 16) {
            phy.y = 360 - 16;
            phy.vy = -phy.vy;
        }
        if (phy.x <= 0) {
            phy.x = 0;
            phy.vx = -phy.vx;
        }
        if (phy.y <= 0) {
            phy.y = 0;
            phy.vy = -phy.vy;
        }
    }
    return true;
}

}
