#pragma once 
#include <cstdint>
#include <vector>
#include <string>
#include "physics.hpp"
#include "../util/typealiases.hpp"

namespace ECS {

enum class EntityType {
    PLAYER,
    ENEMY_RED,
    ENEMY_BLUE,
    ENEMY_GREEN,
    ENEMY_YELLOW
};

struct Entity_t {
    EntityType type { EntityType::ENEMY_RED };
    uint32_t w { 16 }, h { 16 };
    uint32_t x { 0 }, y { 0 };
    int32_t vx { 0 }, vy { 0 };
    uint32_t color { 0xFFFFFFFF };
    std::vector<uint32_t> sprite{};
    bool active { true };
    EntityID_t entityID { 0 };
    
    Entity_t() = default;
    
    Entity_t(uint32_t _w, uint32_t _h, uint32_t _color, EntityType _type)
        : w(_w), h(_h), color(_color), type(_type) {
        generateSprite();
    }
    
    void generateSprite() {
        sprite.resize(w * h, color);
        // Dibujar borde más oscuro
        for (uint32_t x = 0; x < w; x++) {
            sprite[x] = color & 0x00FFFFFF; // más oscuro
            sprite[(h-1) * w + x] = color & 0x00FFFFFF;
        }
        for (uint32_t y = 0; y < h; y++) {
            sprite[y * w] = color & 0x00FFFFFF;
            sprite[y * w + (w-1)] = color & 0x00FFFFFF;
        }
    }
};

}
