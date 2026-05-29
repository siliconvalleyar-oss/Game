#include <iostream>
#include <algorithm>
#include "collision.hpp"
#include "../util/gamecontext.hpp"

namespace ECS {

bool CollisionSystem_t::update(GameContext_t& g) const {
    auto& entities = g.getEntities();
    for (size_t i = 0; i < entities.size(); ++i) {
        for (size_t j = i + 1; j < entities.size(); ++j) {
            auto& a = entities[i];
            auto& b = entities[j];
            
            if (a.x < b.x + b.w &&
                a.x + a.w > b.x &&
                a.y < b.y + b.h &&
                a.y + a.h > b.y) {
                std::swap(a.vx, b.vx);
                std::swap(a.vy, b.vy);
            }
        }
    }
    return true;
}

}
