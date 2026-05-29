#pragma once 
#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>
#include <fstream>
#include <cstring>
#include "physics.hpp"
#include "../util/typealiases.hpp"

namespace ECS {

struct Entity_t {
    Entity_t() : w(0), h(0) {}
    
    explicit Entity_t(uint32_t _w, uint32_t _h)
        : w(_w), h(_h) {
        sprite.resize(w * h, 0xFFFFFFFF);
    }

    explicit Entity_t(const std::string& filename) : w(0), h(0) {
        std::vector<unsigned char> pixels{};
        unsigned long dw{0}, dh{0};
        std::ifstream file(filename, std::ios::binary);
        if (file.is_open()) {
            std::vector<unsigned char> filevec(
                std::istreambuf_iterator<char>{file},
                std::istreambuf_iterator<char>{}
            );
            w = dw;
            h = dh;
            sprite.resize(w * h, 0xFFFFFFFF);
        }
    }

    uint32_t x { 0 }, y { 0 };
    uint32_t vx { 1 }, vy { 1 };
    uint32_t w { 16 }, h { 16 };
    std::vector<uint32_t> sprite{};
    EntityID_t entityID { 0 };
};

}
