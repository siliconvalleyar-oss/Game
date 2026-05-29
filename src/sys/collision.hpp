#pragma once

namespace ECS{
struct  GameContext_t;

class CollisionSystem_t
{
private:
     
public:
    explicit CollisionSystem_t()=default;
    bool update (GameContext_t&)const;
};




}