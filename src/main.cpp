extern "C" {
    #include "../lib/tinyPTC/src/tinyptc.h"
}
#include <cstdint>
#include <iostream>
#include <memory>
#include <unistd.h>
#include "sys/rendersystem.hpp"
#include "man/entitymanager.hpp"
#include "util/gamecontext.hpp"
#include "sys/collision.hpp"
#include "sys/physics.hpp"
#include "sys/player_controller.hpp"

constexpr uint32_t kSCRWIDTH { 640 };
constexpr uint32_t kSCRHEIGHT { 360 };

int main(void) {
    std::cout << "🎮 RetroMan - Juego con Assets" << std::endl;
    std::cout << "📖 Controles: Flechas para mover al jugador" << std::endl;
    std::cout << "💥 Colisiona con enemigos para destruirlos y ganar puntos!" << std::endl;
    std::cout << "================================================" << std::endl;
    
    try {
        ECS::EntityManager_t entityMan;
        ECS::RenderSystem_t render{ kSCRWIDTH, kSCRHEIGHT };
        ECS::PhysicsSystem_t physics;
        ECS::CollisionSystem_t collision;
        ECS::PlayerController_t controller;
        
        int frameCount = 0;
        
        while (render.update(entityMan)) {
            controller.update(entityMan);
            physics.update(entityMan);
            collision.update(entityMan);
            
            frameCount++;
            if (frameCount % 120 == 0) {
                entityMan.removeInactive();
            }
            
            usleep(16000);
        }
    } catch (const std::exception& e) {
        std::cout << "❌ Error: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "❌ Error desconocido" << std::endl;
    }
    
    return 0;
}
