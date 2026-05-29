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
    std::cout << "🎮 RetroMan - Juego con Jugador y Enemigos" << std::endl;
    std::cout << "📖 Controles: Flechas para mover al jugador (cuadrado verde)" << std::endl;
    std::cout << "💥 Colisiona con los enemigos para destruirlos!" << std::endl;
    
    try {
        ECS::EntityManager_t entityMan;
        ECS::RenderSystem_t render{ kSCRWIDTH, kSCRHEIGHT };
        ECS::PhysicsSystem_t physics;
        ECS::CollisionSystem_t collision;
        ECS::PlayerController_t controller;
        
        int frameCount = 0;
        
        while (render.update(entityMan)) {
            // Control del jugador
            controller.update(entityMan);
            
            // Actualizar físicas
            physics.update(entityMan);
            
            // Actualizar colisiones
            collision.update(entityMan);
            
            // Limpiar enemigos destruidos cada cierto tiempo
            frameCount++;
            if (frameCount % 60 == 0) {
                entityMan.removeInactive();
            }
            
            usleep(16000); // ~60 FPS
        }
    } catch (const std::exception& e) {
        std::cout << "❌ Error: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "❌ Error desconocido" << std::endl;
    }
    
    return 0;
}
