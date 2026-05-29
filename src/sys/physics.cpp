#include "physics.hpp"
#include "../util/gamecontext.hpp"

namespace ECS{
    PhysicsSystem_t::PhysicsSystem_t()    {
    }

    PhysicsSystem_t::~PhysicsSystem_t(){
    }

    bool PhysicsSystem_t::update (GameContext_t& g)const{
        for(auto& e :g.getEntities()){
           
             if(e.x + e.w > 640 ){ e.x -=e.vx ; e.vx -=e.vx; }
             if(e.y + e.h > 360 ){ e.y -=e.vy ; e.vy -=e.vy; }
            
             
        }
        return true;
    }
}