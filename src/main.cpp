extern "C" {
///    #include <tinyPTC/src/tinyptc.h>
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

int main(void){
  
  try{
      ECS::EntityManager_t entityMan;
      entityMan.createEntity(20,40,16,16,0x00ffffff);
      const ECS::RenderSystem_t render{ kSCRWIDTH , kSCRHEIGHT};
      ECS::PhysicsSystem_t Physics;
      ECS::CollisionSystem_t Collision;
 
      while(render.update(entityMan))
      {
        Physics.update(entityMan);
        Collision.update(entityMan);
      }
  }
  catch(...){
    std::cout<< "break program"<<std::endl;
  }


  return 0;
}





