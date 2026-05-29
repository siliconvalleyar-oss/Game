#include "physics.hpp"
#include "../util/gamecontext.hpp"

namespace ECS {

bool PhysicsSystem_t::update(GameContext_t& g) const {
    auto& entities = g.getEntities();
    for (auto& entity : entities) {
        entity.x += entity.vx;
        entity.y += entity.vy;
        
        if (entity.x + entity.w >= 640) {
            entity.x = 640 - entity.w;
            entity.vx = -entity.vx;
        }
        if (entity.y + entity.h >= 360) {
            entity.y = 360 - entity.h;
            entity.vy = -entity.vy;
        }
        if (entity.x <= 0) {
            entity.x = 0;
            entity.vx = -entity.vx;
        }
        if (entity.y <= 0) {
            entity.y = 0;
            entity.vy = -entity.vy;
        }
    }
    return true;
}

}
