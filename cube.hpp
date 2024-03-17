
#include <cstdint>
#include <variant>
#include <iostream>


enum class Row {
	Top = 0, Middle = 2, Bottom = 1
};

enum class Column {
	Left = 0, Middle = 2, Right = 1
};

enum class Direction {
	Up = 0, Down = 1, _180 = 4, Left = 2, Right = 3
};

namespace Mask {
	enum class Column {
		Left =   0x070381C0,
		Middle = 0x00E07038,
		Right =  0x001C0E07
	};

	enum class Row {
		Top = 	 0b111111111 << 6*3,
		Middle = 0b111111111 << 3*3,
		Bottom = 0b111111111,
	};
}


enum Color {
	White =  0b000,
	Green =  0b001,
	Blue =   0b010,
	Orange = 0b011,
	Red = 	 0b100,
	Yellow = 0b101
};

enum SolvedFace {
	WhiteFace =  0x0000000,
	GreenFace =  0x1249249,
	BlueFace =   0x2492492,
	OrangeFace = 0x36DB6DB,
	RedFace = 	 0x4924924,
	YellowFace = 0x5B6DB6D
};

struct Cube {


uint32_t top, bottom,
		 front, back,
		 left, right;

 	Cube();
	Cube(uint32_t top, uint32_t bottom,
		uint32_t front, uint32_t back,
		uint32_t left, uint32_t right);

	Cube rotHoriz(Row line, Direction dir);
	Cube rotVert(Column line, Direction dir);

	//bool isSolved();

private:
	//If this becomes a bottleneck, it could possibly
	//be sped up with a permute instruction
	static uint32_t rotFaceLeft(uint32_t face);
	static uint32_t rotFaceRight(uint32_t face);
	static uint32_t rotFace180(uint32_t face);

};

std::ostream& operator<<(std::ostream& os, const Cube& cube);
