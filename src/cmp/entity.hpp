#pragma once 
#include <cstdint>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include "../../lib/picoPNG/src/picopng.hpp"
#include "physics.hpp"
#include "../util/typealiases.hpp"

namespace ECS {

struct Entity_t {
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
            decodePNG(pixels, dw, dh, filevec.data(), filevec.size());
            w = dw;
            h = dh;
            sprite.reserve(pixels.size() / 4);
            for (auto p = pixels.begin(); p != pixels.end(); p += 4) {
                uint32_t pixel = 
                    static_cast<uint32_t>(*(p + 0)) << 16 |
                    static_cast<uint32_t>(*(p + 1)) << 8  |
                    static_cast<uint32_t>(*(p + 2))       |
                    static_cast<uint32_t>(*(p + 3)) << 24;
                sprite.push_back(pixel);
            }
        }
    }

    PhysicsComponent_t* phy { nullptr };
    uint32_t w { 0 }, h { 0 };
    uint32_t x { 0 }, y { 0 };
    uint32_t vx { 1 }, vy { 1 };
    std::vector<uint32_t> sprite{};
    EntityID_t entityID { 0 };
};

} // namespace ECS
