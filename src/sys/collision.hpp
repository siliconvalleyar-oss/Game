#pragma once

namespace ECS{
struct  GameContext_t;

class CollisionSystem_t
{
private:
     
public:
    CollisionSystem_t();
    ~CollisionSystem_t();
    bool update (GameContext_t&)const;
};




}