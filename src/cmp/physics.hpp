#pragma once
#include <cstdint>

namespace ECS {

struct PhysicsComponent_t {
    uint32_t x { 0 }, y { 0 };
    uint32_t vx { 1 }, vy { 1 };
    uint32_t width { 16 }, height { 16 };
    
    PhysicsComponent_t() = default;
    PhysicsComponent_t(uint32_t px, uint32_t py) : x(px), y(py) {}
    PhysicsComponent_t(uint32_t px, uint32_t py, uint32_t vx_, uint32_t vy_) 
        : x(px), y(py), vx(vx_), vy(vy_) {}
};

} // namespace ECS
