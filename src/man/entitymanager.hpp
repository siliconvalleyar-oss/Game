#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>
#include "../util/typealiases.hpp"
#include "../util/gamecontext.hpp"

namespace ECS{
	struct GameContext_t;

	struct  EntityManager_t : public GameContext_t
	{
		static constexpr std::size_t kNUMINITIALENTITIES { 1000 } ;	
		explicit EntityManager_t();
		void createEntity(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t) ;
		const VecEntities_t& getEntities() const override
		{
			return m_Entity;
		};

		VecEntities_t& getEntities()  override
		{
			return m_Entity;
		};

	private:
		VecEntities_t m_Entity{};
	};

}

