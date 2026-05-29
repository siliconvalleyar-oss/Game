#pragma once
#include <cstdint>

namespace ECS {

struct PhysicsComponent_t {
    float x { 0 }, y { 0 };
    float vx { 0 }, vy { 0 };
    uint32_t width { 16 }, height { 16 };
    bool active { true };
    
    PhysicsComponent_t() = default;
    PhysicsComponent_t(float px, float py) : x(px), y(py) {}
    PhysicsComponent_t(float px, float py, float vx_, float vy_) 
        : x(px), y(py), vx(vx_), vy(vy_) {}
};

}
