
#include <iostream>
#include "entitymanager.hpp"
#include "../cmp/entity.hpp"

namespace ECS 
{
	EntityManager_t::EntityManager_t(){
	
		m_Entity.reserve(kNUMINITIALENTITIES);
	}
	
	void EntityManager_t::createEntity( uint32_t x , uint32_t y , uint32_t i  ,uint32_t j , uint32_t color )
	{
		//auto& me {
		m_Entity.emplace_back(i,j);
		//me.begin(i,j);
		//me.emplace_back(i,j);
		Entity_t me(i,j);
		//std::swap(me , m_Entity);
		
		std::fill(me.sprite.begin() , me.sprite.end() , color);
		//  me.x = x ;
		//  me.y = y ;
		//  std::fill(me.sprite.begin() , me.sprite.end(),color);
	}
}

