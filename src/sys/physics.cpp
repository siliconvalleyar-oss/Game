#include "physics.hpp"
#include "../util/gamecontext.hpp"

namespace ECS {

bool PhysicsSystem_t::update(GameContext_t& g) const {
    auto& entities = g.getEntities();
    const uint32_t SCREEN_W = 640;
    const uint32_t SCREEN_H = 360;
    
    for (auto& entity : entities) {
        if (!entity.active) continue;
        
        entity.x += entity.vx;
        entity.y += entity.vy;
        
        if (entity.x + entity.w >= SCREEN_W) {
            entity.x = SCREEN_W - entity.w;
            if (entity.type != EntityType::PLAYER) entity.vx = -entity.vx;
            else entity.vx = 0;
        }
        if (entity.y + entity.h >= SCREEN_H) {
            entity.y = SCREEN_H - entity.h;
            if (entity.type != EntityType::PLAYER) entity.vy = -entity.vy;
            else entity.vy = 0;
        }
        if (entity.x <= 0) {
            entity.x = 0;
            if (entity.type != EntityType::PLAYER) entity.vx = -entity.vx;
            else entity.vx = 0;
        }
        if (entity.y <= 0) {
            entity.y = 0;
            if (entity.type != EntityType::PLAYER) entity.vy = -entity.vy;
            else entity.vy = 0;
        }
    }
    return true;
}

}
