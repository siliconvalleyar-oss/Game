#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include "componentstorage.hpp"
#include "../util/typealiases.hpp"
#include "../util/gamecontext.hpp"

namespace ECS {

struct EntityManager_t : public GameContext_t {
    static constexpr std::size_t kNUMINITIALENTITIES { 1000 };
    
    explicit EntityManager_t() { 
        m_Entity.reserve(kNUMINITIALENTITIES); 
    }
    
    void createEntity(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color) {
        auto& e = m_Entity.emplace_back(w, h);
        e.x = x;
        e.y = y;
        e.x = x;
        e.y = y;
        e.entityID = m_Entity.size() - 1;
        (void)color; // unused
    }
    
    void createEntity(uint32_t x, uint32_t y, const std::string& filename) {
        auto& e = m_Entity.emplace_back(filename);
        e.x = x;
        e.y = y;
        e.vx = 1;
        e.vy = 1;
        e.entityID = m_Entity.size() - 1;
    }
    
    const Vect_t<Entity_t>& getEntities() const override { return m_Entity; }
    Vect_t<Entity_t>& getEntities() override { return m_Entity; }
    
    const std::vector<PhysicsComponent_t>& getPhysicsComponent() const override { 
        return m_components.getPhysicsComponent(); 
    }
    
    std::vector<PhysicsComponent_t>& getPhysicsComponent() override { 
        return m_components.getPhysicsComponent(); 
    }

private:
    Vect_t<Entity_t> m_Entity{};
    ComponentStorage_t m_components;
};

}
