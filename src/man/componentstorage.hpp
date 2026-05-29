#pragma once
#include <vector>
#include "../cmp/physics.hpp"

namespace ECS {

struct ComponentStorage_t {
    PhysicsComponent_t& createPhysicsComponent() {
        m_physicsComponents.emplace_back();
        return m_physicsComponents.back();
    }
    
    std::vector<PhysicsComponent_t>& getPhysicsComponent() { 
        return m_physicsComponents; 
    }
    
    const std::vector<PhysicsComponent_t>& getPhysicsComponent() const { 
        return m_physicsComponents; 
    }

private:
    std::vector<PhysicsComponent_t> m_physicsComponents{};
};

}
