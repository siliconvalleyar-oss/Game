#pragma once
#include "../util/typealiases.hpp"
namespace ECS {
struct Component_t {
    EntityID_t entityID { 0 };
    Component_t(EntityID_t eid) : entityID(eid) {}
};
}
