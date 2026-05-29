#include <iostream>
#include <algorithm>
#include "collision.hpp"
#include "../util/gamecontext.hpp"
#include "../cmp/entity.hpp"

namespace ECS {

bool CollisionSystem_t::update(GameContext_t& g) const {
    auto& entities = g.getEntities();
    Entity_t* player = g.getPlayer();
    
    if (!player) return true;
    
    for (auto& entity : entities) {
        if (!entity.active) continue;
        
        // Colisión jugador vs enemigo
        if (&entity != player && entity.type != EntityType::PLAYER && player->active) {
            if (player->x < entity.x + entity.w &&
                player->x + player->w > entity.x &&
                player->y < entity.y + entity.h &&
                player->y + player->h > entity.y) {
                
                // Destruir enemigo al colisionar
                entity.active = false;
                std::cout << "💥 Enemigo destruido!" << std::endl;
            }
        }
    }
    
    return true;
}

}
