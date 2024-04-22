


#pragma once

#include "cube.hpp"
#include <cstdint>
#include <iostream>
#include <cassert>
#include <unordered_set>
#include <algorithm>
#include <array>

namespace MiniMask {
	namespace Column {
		uint16_t constexpr Left =  0xE38;
		uint16_t constexpr Right = 0x1C7;
	};

	namespace Row {
		uint16_t constexpr Top = 	0xFC0;
		uint16_t constexpr Bottom = 0x03F;
	}; 

};

struct EdgeCubies {

	/*
	enum SolvedFace {
		WhiteFace =  0x000,
		GreenFace =  0x249,
		RedFace =   0x492,
		YellowFace = 0x6DB,
		BlueFace = 	 0x924,
		OrangeFace = 0xB6D
	};
	*/
    
    //Top, bottom are 3 faces, left/right are 6, front/back are 2
    uint16_t top, bottom, left, right;
    uint32_t front, back;

 	EdgeCubies();
	EdgeCubies(uint16_t top, uint16_t bottom, 
			uint32_t left, uint32_t right,
			uint16_t front, uint16_t back);
	    
	//EdgeCubies(Cube const& largeCube);

	//Normalized so top left front cube is never moved
	EdgeCubies rotHoriz(Row line) const;
	EdgeCubies rotXAxis(CrossSection line) const;

	EdgeCubies& operator=(const EdgeCubies& other) = default;

	std::array<EdgeCubies, 5> getNeighbors() const;

	//This is gonna be complicated...
	//uint32_t getIdx() const;

	/*
	struct CubieInfo {
		uint8_t id;
		uint8_t orientation;
	};*/

	//CubieInfo getCubieInfo(bool x, bool y, bool z) const;

};

std::ostream& operator<<(std::ostream& os, const EdgeCubies& cube);

//For debbuging
bool operator==(EdgeCubies const& lhs, EdgeCubies const& rhs);
bool operator!=(EdgeCubies const& lhs, EdgeCubies const& rhs);

