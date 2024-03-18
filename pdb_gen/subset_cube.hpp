
#pragma once

#include "../cube.hpp"
#include <cstdint>
#include <iostream>


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

	MiniCube rotHoriz(Row line, Direction dir);
	MiniCube rotVert(Column line, Direction dir);

private:
	//If this becomes a bottleneck, it could possibly
	//be sped up with a permute instruction
	static uint16_t rotFaceLeft(uint16_t face);
	static uint16_t rotFaceRight(uint16_t face);
	static uint16_t rotFace180(uint16_t face);

};

std::ostream& operator<<(std::ostream& os, const MiniCube& cube);
