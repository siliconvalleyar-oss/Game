#pragma once 
#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>
#include <fstream>
#include "../../lib/picoPNG/src/picopng.hpp"
#include <iostream>
#include <cstring>

namespace ECS{
	struct Entity_t
	{
		~Entity_t()=default;
		
		explicit Entity_t(uint32_t _w , uint32_t _h)
		: w(_w) , h(_h)
		{
			sprite.resize(w*h);	
		}

		explicit Entity_t(std::string filename ){
			std::vector <unsigned char>pixels{};
			unsigned long dw{0},dh{0};
			std::ifstream file(filename ,std::ios::binary);
			//filename
			std::vector<unsigned char> filevec(
					std::istreambuf_iterator<char>{file}
				,	std::istreambuf_iterator<char>{}
				
			);


			decodePNG(pixels ,dw,dh,filevec.data() , filevec.size());
				sprite.resize(pixels.size()/4);
				std::memcpy(sprite.data() , pixels.data() , pixels.size());
				w=dw;
				h=dh;

		}

		bool has_physics(){return true;};

		uint32_t x { 0 } , y { 0 };	
		uint32_t w { 0 } , h { 0 };
		uint32_t vx { 1 } , vy { 1 };

		std::vector<uint32_t>sprite{};
	};
}