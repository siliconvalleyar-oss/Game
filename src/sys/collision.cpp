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
            
            if (a.phy && b.phy) {
                if (a.phy->x < b.phy->x + b.w &&
                    a.phy->x + a.w > b.phy->x &&
                    a.phy->y < b.phy->y + b.h &&
                    a.phy->y + a.h > b.phy->y) {
                    std::swap(a.vx, b.vx);
                    std::swap(a.vy, b.vy);
                    std::swap(a.phy->vx, b.phy->vx);
                    std::swap(a.phy->vy, b.phy->vy);
                }
            }
        }
    }
    return true;
}

}
