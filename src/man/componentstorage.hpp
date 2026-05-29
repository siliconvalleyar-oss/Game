#pragma once
#include <vector>
#include "../cmp/physics.hpp"

namespace ECS {

struct ComponentStorage_t {
    std::vector<PhysicsComponent_t> physicsComponents{};
    
    PhysicsComponent_t& createPhysicsComponent() {
        physicsComponents.emplace_back();
        return physicsComponents.back();
    }
};

}
