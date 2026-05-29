#pragma once
//#include "../cmp/entity.hpp"
#include <vector>

namespace ECS{
  
  template<typename T>

    using Vect_t = std::vector<T>;

    using EntityID_t = std::size_t;
}