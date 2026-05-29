#include <iostream>
#include "collision.hpp"
#include "../util/gamecontext.hpp"

namespace ECS {

bool CollisionSystem_t::update(GameContext_t& g) const {
    auto& entities = g.getEntities();
    Entity_t* player = g.getPlayer();
    
    if (!player || !player->active) return true;
    
    for (auto& entity : entities) {
        if (!entity.active) continue;
        
        if (&entity != player && entity.type == EntityType::ENEMY) {
            if (player->x < entity.x + entity.w &&
                player->x + player->w > entity.x &&
                player->y < entity.y + entity.h &&
                player->y + player->h > entity.y) {
                
                entity.active = false;
                g.addScore(10);
                std::cout << "💥 Enemigo destruido! +10 puntos" << std::endl;
            }
        }
    }
    
    return true;
}

}
