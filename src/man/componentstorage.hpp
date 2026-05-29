#pragma once
#include <vector>
#include "../cmp/physics.hpp"

namespace ECS {

struct ComponentStorage_t {
    explicit ComponentStorage_t() = default;
    explicit ComponentStorage_t(std::size_t initialsize) {
        m_physicsComponents.reserve(initialsize);
    }
    
    ComponentStorage_t(const ComponentStorage_t&) = delete;
    ComponentStorage_t(ComponentStorage_t&&) = delete;
    ComponentStorage_t& operator=(const ComponentStorage_t&) = delete;
    ComponentStorage_t& operator=(ComponentStorage_t&&) = delete;
    
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
