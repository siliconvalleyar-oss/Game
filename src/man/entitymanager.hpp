#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <random>
#include "componentstorage.hpp"
#include "../util/typealiases.hpp"
#include "../util/gamecontext.hpp"
#include "../cmp/entity.hpp"

namespace ECS {

struct EntityManager_t : public GameContext_t {
    Vect_t<Entity_t> m_Entity{};
    Entity_t* m_player { nullptr };
    ComponentStorage_t m_components;
    std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<int> distX{ 50, 550 };
    std::uniform_int_distribution<int> distY{ 50, 300 };
    
    explicit EntityManager_t() {
        m_Entity.reserve(1000);
        createPlayer();
        createEnemies(8); // 8 enemigos
    }
    
    void createPlayer() {
        auto& player = m_Entity.emplace_back(16, 16, 0xFF00FF00, EntityType::PLAYER);
        player.x = 320;
        player.y = 180;
        player.vx = 0;
        player.vy = 0;
        player.active = true;
        m_player = &player;
    }
    
    void createEnemies(int count) {
        std::uniform_int_distribution<int> distColor(0, 3);
        
        for (int i = 0; i < count; i++) {
            EntityType type;
            uint32_t color;
            int colorType = distColor(rng);
            
            switch(colorType) {
                case 0: type = EntityType::ENEMY_RED; color = 0xFFFF0000; break;
                case 1: type = EntityType::ENEMY_BLUE; color = 0xFF0000FF; break;
                case 2: type = EntityType::ENEMY_GREEN; color = 0xFF00FF00; break;
                default: type = EntityType::ENEMY_YELLOW; color = 0xFFFFFF00; break;
            }
            
            auto& enemy = m_Entity.emplace_back(16, 16, color, type);
            enemy.x = distX(rng);
            enemy.y = distY(rng);
            enemy.vx = (rand() % 3) + 1;
            enemy.vy = (rand() % 3) + 1;
            if (rand() % 2) enemy.vx = -enemy.vx;
            if (rand() % 2) enemy.vy = -enemy.vy;
            enemy.active = true;
        }
    }
    
    void createEnemyAt(int x, int y, EntityType type, uint32_t color) {
        auto& enemy = m_Entity.emplace_back(16, 16, color, type);
        enemy.x = x;
        enemy.y = y;
        enemy.vx = (rand() % 5) + 1;
        enemy.vy = (rand() % 5) + 1;
        if (rand() % 2) enemy.vx = -enemy.vx;
        if (rand() % 2) enemy.vy = -enemy.vy;
        enemy.active = true;
    }
    
    const Vect_t<Entity_t>& getEntities() const override { return m_Entity; }
    Vect_t<Entity_t>& getEntities() override { return m_Entity; }
    
    Entity_t* getPlayer() override { return m_player; }
    void setPlayer(Entity_t* player) override { m_player = player; }
    
    void removeInactive() {
        m_Entity.erase(
            std::remove_if(m_Entity.begin(), m_Entity.end(),
                [](const Entity_t& e) { return !e.active; }),
            m_Entity.end()
        );
    }
};

}
