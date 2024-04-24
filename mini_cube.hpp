
#pragma once

#include "cube.hpp"
#include <cstdint>
#include <iostream>
#include <cassert>
#include <unordered_set>
#include <algorithm>

//Not universal across different cube types
struct CubieInfo {
	uint8_t id;
	uint8_t orientation;
};

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

struct MiniCube {

	enum SolvedFace {
		WhiteFace =  0x000,
		GreenFace =  0x249,
		RedFace =   0x492,
		YellowFace = 0x6DB,
		BlueFace = 	 0x924,
		OrangeFace = 0xB6D
	};
    
    uint16_t top, bottom, left, right, front, back;

 	MiniCube();
	MiniCube(uint16_t top, uint16_t bottom,
		uint16_t front, uint16_t back,
		uint16_t left, uint16_t right);
    
    //union  {}
	//Construct minicube from corner cubies
	MiniCube(Cube const& largeCube);

	//Normalized so top left front cube is never moved
	MiniCube rotHoriz(Row line, Direction dir) const;
	MiniCube rotVert(Column line, Direction dir) const;

	//Left side view for rotations around the x axis
	MiniCube changePerspective(Perspective per) const;

	MiniCube& operator=(const MiniCube& other) = default;

	std::array<MiniCube, 9> getNeighbors() const;

	//Unique integer generated from cube used as an index into the PDB
	//yields the same value for different orientations of the same cube

	//For some reason this works even though some IDs are used
	//multiple times
	uint32_t getIdx() const;

	//Only public for debugging
	CubieInfo getCubieInfo(bool x, bool y, bool z) const;


private:

	//If this becomes a bottleneck, it could possibly
	//be sped up with a permute instruction
	static uint16_t rotFaceLeft(uint16_t face);
	static uint16_t rotFaceRight(uint16_t face);
	static uint16_t rotFace180(uint16_t face);

	//Get the unique identifier for each cube:
	//the colors of each face from that XOR'd together
	//uint8_t getCubieID(bool x, bool y, bool z) const;

};

std::ostream& operator<<(std::ostream& os, const MiniCube& cube);

//For debbuging
bool operator==(MiniCube const& lhs, MiniCube const& rhs);
bool operator!=(MiniCube const& lhs, MiniCube const& rhs);

