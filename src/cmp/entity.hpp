#pragma once 
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "physics.hpp"
#include "../util/typealiases.hpp"
#include "../../lib/picoPNG/src/picopng.hpp"

namespace ECS {

enum class EntityType {
    PLAYER,
    ENEMY,
    ITEM,
    OBSTACLE
};

struct Entity_t {
    EntityType type { EntityType::ENEMY };
    uint32_t w { 16 }, h { 16 };
    float x { 0 }, y { 0 };
    float vx { 0 }, vy { 0 };
    uint32_t color { 0xFFFFFFFF };
    std::vector<uint32_t> sprite{};
    bool active { true };
    EntityID_t entityID { 0 };
    std::string name { "" };
    
    Entity_t() = default;
    
    Entity_t(uint32_t _w, uint32_t _h, uint32_t _color, EntityType _type)
        : type(_type), w(_w), h(_h), color(_color) {
        generateSolidSprite();
    }
    
    Entity_t(const std::string& filename, EntityType _type) : type(_type) {
        loadSpriteFromPNG(filename);
    }
    
    void generateSolidSprite() {
        sprite.resize(w * h, color);
        for (uint32_t i = 0; i < w; i++) {
            sprite[i] = color & 0x00FFFFFF;
            sprite[(h-1) * w + i] = color & 0x00FFFFFF;
        }
        for (uint32_t i = 0; i < h; i++) {
            sprite[i * w] = color & 0x00FFFFFF;
            sprite[i * w + (w-1)] = color & 0x00FFFFFF;
        }
    }
    
    void loadSpriteFromPNG(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: No se pudo cargar " << filename << std::endl;
            w = 16; h = 16;
            generateSolidSprite();
            return;
        }
        
        std::vector<unsigned char> pngData(
            std::istreambuf_iterator<char>{file},
            std::istreambuf_iterator<char>{}
        );
        file.close();
        
        std::vector<unsigned char> pixels;
        unsigned long imgW = 0, imgH = 0;
        
        int error = decodePNG(pixels, imgW, imgH, pngData.data(), pngData.size(), true);
        
        if (error != 0) {
            std::cerr << "Error decodificando PNG: " << filename << std::endl;
            w = 16; h = 16;
            generateSolidSprite();
            return;
        }
        
        w = imgW;
        h = imgH;
        sprite.resize(w * h);
        
        for (size_t i = 0; i < w * h; i++) {
            uint32_t r = pixels[i * 4 + 0];
            uint32_t g = pixels[i * 4 + 1];
            uint32_t b = pixels[i * 4 + 2];
            uint32_t a = pixels[i * 4 + 3];
            sprite[i] = (a << 24) | (r << 16) | (g << 8) | b;
        }
        
        std::cout << "✅ Cargado: " << filename << " (" << w << "x" << h << ")" << std::endl;
    }
};

}
