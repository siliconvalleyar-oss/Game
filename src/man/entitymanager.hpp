#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <random>
#include <iostream>
#include "componentstorage.hpp"
#include "../util/typealiases.hpp"
#include "../util/gamecontext.hpp"
#include "../cmp/entity.hpp"

namespace ECS {

struct EntityManager_t : public GameContext_t {
    Vect_t<Entity_t> m_Entity{};
    Entity_t* m_player { nullptr };
    int m_score { 0 };
    std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<int> distX{ 50, 550 };
    std::uniform_int_distribution<int> distY{ 50, 280 };
    
    explicit EntityManager_t() {
        m_Entity.reserve(500);
        createPlayer();
        loadEnemiesFromAssets();
    }
    
    void createPlayer() {
        auto& player = m_Entity.emplace_back("assets/ninja_idle.png", EntityType::PLAYER);
        player.x = 320 - player.w / 2;
        player.y = 180 - player.h / 2;
        player.vx = 0;
        player.vy = 0;
        player.active = true;
        player.name = "Player";
        m_player = &player;
        std::cout << "✅ Jugador creado" << std::endl;
    }
    
    void loadEnemiesFromAssets() {
        std::vector<std::string> enemyFiles = {
            "assets/enemy.png", "assets/hongo.png", "assets/bom.png",
            "assets/pacman.png", "assets/mario3.png"
        };
        
        for (const auto& file : enemyFiles) {
            if (FILE *f = fopen(file.c_str(), "r")) {
                fclose(f);
                auto& enemy = m_Entity.emplace_back(file, EntityType::ENEMY);
                enemy.x = distX(rng);
                enemy.y = distY(rng);
                enemy.vx = (rand() % 4) + 1;
                enemy.vy = (rand() % 4) + 1;
                if (rand() % 2) enemy.vx = -enemy.vx;
                if (rand() % 2) enemy.vy = -enemy.vy;
                enemy.active = true;
                enemy.name = file;
            }
        }
        std::cout << "✅ Enemigos cargados" << std::endl;
    }
    
    const Vect_t<Entity_t>& getEntities() const override { return m_Entity; }
    Vect_t<Entity_t>& getEntities() override { return m_Entity; }
    
    Entity_t* getPlayer() override { return m_player; }
    void setPlayer(Entity_t* player) override { m_player = player; }
    
    void addScore(int points) override { m_score += points; std::cout << "🏆 Puntuación: " << m_score << std::endl; }
    int getScore() const override { return m_score; }
    
    void removeInactive() {
        m_Entity.erase(
            std::remove_if(m_Entity.begin(), m_Entity.end(),
                [](const Entity_t& e) { return !e.active; }),
            m_Entity.end()
        );
    }
};

}
