
#pragma once

#include "../cube.hpp"
#include <cstdint>
#include <iostream>
#include <cassert>

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
		BlueFace =   0x492,
		OrangeFace = 0x6DB,
		RedFace = 	 0x924,
		YellowFace = 0xB6D
	};


uint16_t top, bottom,
		 front, back,
		 left, right;

 	MiniCube();
	MiniCube(uint16_t top, uint16_t bottom,
		uint16_t front, uint16_t back,
		uint16_t left, uint16_t right);

	MiniCube rotHoriz(Row line, Direction dir) const;
	MiniCube rotVert(Column line, Direction dir) const;

	//Unique integer generated from cube used as an index into the PDB
	//yields the same value for different orientations of the same cube
	uint32_t getIdx() const {
		//bool usedIds[8] {
		//	0, 0, 0, 0, 0, 0, 0, 0
		//};
		//Starting from 1!
		uint16_t const facts[7] {
			1, 2, 6, 24, 120, 720, 5040
		};

		uint32_t idx = 0;

		//Last cube is already known given the first 7
		for (int i = 0; i < 7; i++) {
			idx += facts[i]*getCubieID(i & 0b001, i & 0b010, i & 0b100);

			//assert(usedIds[getCubieID(i & 0b001, i & 0b010, i & 0b100)] == false);
			//usedIds[getCubieID(i & 0b001, i & 0b010, i & 0b100)] = true;
		}



		return idx;
	}

private:
	//If this becomes a bottleneck, it could possibly
	//be sped up with a permute instruction
	static uint16_t rotFaceLeft(uint16_t face);
	static uint16_t rotFaceRight(uint16_t face);
	static uint16_t rotFace180(uint16_t face);

	//Get the unique identifier for each cube:
	//the colors of each face from that XOR'd together

	//Or at least, that works with the current arrangement
	uint8_t getCubieID(bool x, bool y, bool z) const;

};

std::ostream& operator<<(std::ostream& os, const MiniCube& cube);

//For debbuging
bool operator==(MiniCube const& lhs, MiniCube const& rhs);
bool operator!=(MiniCube const& lhs, MiniCube const& rhs);

