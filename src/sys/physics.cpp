#include "physics.hpp"
#include "../util/gamecontext.hpp"
#include "../man/entitymanager.hpp"

namespace ECS {

bool PhysicsSystem_t::update(GameContext_t& g) const {
    auto& entities = g.getEntities();
    const uint32_t SCREEN_W = 640;
    const uint32_t SCREEN_H = 360;
    
    for (auto& entity : entities) {
        if (!entity.active) continue;
        
        entity.x += entity.vx;
        entity.y += entity.vy;
        
        // Limitar bordes de pantalla
        if (entity.x + entity.w >= SCREEN_W) {
            entity.x = SCREEN_W - entity.w;
            entity.vx = -entity.vx;
        }
        if (entity.y + entity.h >= SCREEN_H) {
            entity.y = SCREEN_H - entity.h;
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
