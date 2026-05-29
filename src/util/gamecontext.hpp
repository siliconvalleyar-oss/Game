#pragma once
#include "../cmp/entity.hpp"
#include "typealiases.hpp"

namespace ECS{
    struct Entity_t;

    struct GameContext_t
    {
        virtual ~GameContext_t()=default;
        virtual const VecEntities_t& getEntities()const = 0;
        virtual VecEntities_t& getEntities()=0;
        
    };

}