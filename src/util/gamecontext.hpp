#pragma once
#include "../cmp/entity.hpp"
#include "typealiases.hpp"

namespace ECS {

struct GameContext_t {
    virtual ~GameContext_t() = default;
    virtual Vect_t<Entity_t>& getEntities() = 0;
    virtual const Vect_t<Entity_t>& getEntities() const = 0;
    virtual Entity_t* getPlayer() = 0;
    virtual void setPlayer(Entity_t* player) = 0;
};

}
