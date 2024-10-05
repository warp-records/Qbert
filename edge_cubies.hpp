#pragma once

#include "cube.hpp"
#include <cstdint>
#include <iostream>
#include <cassert>
#include <unordered_set>
#include <algorithm>
#include <array>

//Set of 6
struct EdgeCubies : public Cube {

    struct CubieInfo {
		uint8_t id;
		uint8_t orientation;
	};

	uint32_t getIdx() const;
    EdgeCubies::CubieInfo getCubieInfo(int idx) const;

    std::array<EdgeCubies, 27> getNeighbors() const;

    EdgeCubies();

    EdgeCubies(bool ss) : secondSet{ss} {};

    EdgeCubies(uint32_t top, uint32_t bottom,
		uint32_t front, uint32_t back,
		uint32_t left, uint32_t right);

    EdgeCubies(const Cube& largeCube) : Cube(largeCube) {};

    bool secondSet = false;

    //used for debugging
    operator Cube() const { return Cube(top, bottom, front, back, left, right); }
};
/*
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
*/
/*
struct EdgeCubies : Cube {

    //that ended up being dead wrong lol
    //Top, bottom are 3 faces, left/right are 6, front/back are 2
    uint16_t top, bottom, front, back;
    uint32_t left, right;

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
	//Not normalized
	uint32_t
	CubieInfo getCubieInfo(bool x, bool y, bool z) const;


	struct CubieInfo {
		uint8_t id;
		uint8_t orientation;
	};

};

std::ostream& operator<<(std::ostream& os, const EdgeCubies& cube);

//For debbuging
bool operator==(EdgeCubies const& lhs, EdgeCubies const& rhs);
bool operator!=(EdgeCubies const& lhs, EdgeCubies const& rhs);
*/
