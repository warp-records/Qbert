
#include <cstdint>
#include <variant>


enum class Line {
	Top, Middle, Bottom
};

enum class Column {
	Left, Middle, Right
};

enum class Direction {
	Up, Down, Left, Right, _180
}

namespace Mask {
	enum class Column {
		Left =   0x1C0E07 << 6*3,
		Middle = 0x1C0E07 << 3*3,
		Right =  0x1C0E07
	}

	enum class Row {
		Top = 0xff << 18*3,
		Middle = 0xff << 9*3,
		Bottom = 0xff,
	}
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
}

struct Cube {


uint32_t top, bottom,
		 front, back,
		 left, right;

 	Cube();
	Cube(uint32_t   top, bottom,
					front, back,
					left, right);


	Cube rotateHoriz(Row line, Direction dir);
	Cube rotateVert(Column line, Direction dir);

	bool isSolved();

private:
	//If this becomes a bottleneck, it could possibly
	//be sped up with a permute instruction
	uint32_t rotFaceLeft(uint32_t face);
	uint32_t rotFaceRight(uint32_t face);
	uint32_t rotFace180(uint32_t face);

};
