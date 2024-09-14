
#pragma once

#include "edge_cubies.hpp"
#include <cstdint>
#include <variant>
#include <iostream>


enum class Row {
	Top = 0, Middle = 2, Bottom = 1
};

enum class Column {
	Left = 0, Middle = 2, Right = 1
};

enum class CrossSection {
	Front = 0, Middle = 2, Back = 1
};

enum class Direction {
	Up = 0, Down = 1, _180 = 4, Left = 2, Right = 3
};

//Only used for changing orientation; Back and Front are irrelevant for implementation
enum class Perspective {
	Left, Right
};

enum Color {
	White =  0b000,
	Green =  0b001,
	Red =   0b010,
	Yellow = 0b011,
	Blue = 	 0b100,
	Orange = 0b101
};

//These represent rows and columns on a square, not a cube
namespace Mask {
	namespace Column {
		uint32_t constexpr Left =   0x070381C0;
		uint32_t constexpr Middle = 0x00E07038;
		uint32_t constexpr Right =  0x001C0E07;
	};

	namespace Row {
		uint32_t constexpr Top = 	 0b111111111 << 6*3;
		uint32_t constexpr Middle = 0b111111111 << 3*3;
		uint32_t constexpr Bottom = 0b111111111;
	};
};

struct Cube {

	enum SolvedFace {
		WhiteFace =  0x0000000,
		GreenFace =  0x1249249,
		RedFace =   0x2492492,
		YellowFace = 0x36DB6DB,
		BlueFace = 	 0x4924924,
		OrangeFace = 0x5B6DB6D
	};


uint32_t top, bottom,
		 front, back,
		 left, right;

 	Cube();
	Cube(uint32_t top, uint32_t bottom,
		uint32_t front, uint32_t back,
		uint32_t left, uint32_t right);

	std::array<Cube, 27> getNeighbors() const;

	//These are only Y and Z axis rotations; todo: make a function for x axis rotations specifically
	Cube rotHoriz(Row line, Direction dir) const;
	Cube rotVert(Column line, Direction dir) const;
	Cube rotXaxis(CrossSection line, Direction dir) const;

	bool isSolved() const {

		uint16_t constexpr SOLVED_HASH =
							(uint16_t) (WhiteFace ^ GreenFace ^
							BlueFace ^ OrangeFace ^
							RedFace ^ YellowFace);

		//With this hash functon, collisions occur 0.8% of the time
		uint16_t const cubeHash = (uint16_t) ((top^front) 	  ^
								  (bottom^left)>>3 ^
								  (right^back)>>6);

		if (cubeHash == SOLVED_HASH) {
			return strongSolvedCheck();
		} else {
			return false;
		}
	}

	Cube changePerspective(Perspective per) const;


	//DEBUG -----------------------------------
	bool hasProperCorners() const;
	bool isValidColorDistribution() const;

private:


	//DEBUG ---------
	static uint32_t extractColor(uint32_t face, int position) {
	    return (face >> (position * 3)) & 0b111;
	}

	bool strongSolvedCheck() const;
	//If this becomes a bottleneck, it could possibly
	//be sped up with a permute instruction
	static uint32_t rotFaceLeft(uint32_t face);
	static uint32_t rotFaceRight(uint32_t face);
	static uint32_t rotFace180(uint32_t face);
	static uint32_t reflectFaceXaxis(uint32_t face);

};

std::ostream& operator<<(std::ostream& os, const Cube& cube);
