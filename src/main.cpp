extern "C" {
    #include "../lib/tinyPTC/src/tinyptc.h"
}
#include <cstdint>
#include <iostream>
#include <memory>
#include "sys/rendersystem.hpp"
#include "man/entitymanager.hpp"
#include "util/gamecontext.hpp"
#include "sys/collision.hpp"
#include "sys/physics.hpp"

constexpr uint32_t kSCRWIDTH { 640 };
constexpr uint32_t kSCRHEIGHT { 360 };

int main(void) {
    try {
        ECS::EntityManager_t entityMan;
        
        // Crear entidad con sprite cuadrado
        entityMan.createEntity(20, 40, 16, 16, 0x00ffffff);
        
        // Crear entidades desde archivos PNG
        entityMan.createEntity(80, 10, "assets/ninja.png");
        entityMan.createEntity(200, 70, "assets/ninja.png");
        
        const ECS::RenderSystem_t render{ kSCRWIDTH, kSCRHEIGHT };
        ECS::PhysicsSystem_t physics;
        ECS::CollisionSystem_t collision;
        
        while (render.update(entityMan)) {
            physics.update(entityMan);
            collision.update(entityMan);
        }
    } catch (...) {
        std::cout << "break program" << std::endl;
    }
    return 0;
}
