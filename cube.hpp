#include <cstdint>
#include <variant>


enum class Row {
	Top, Middle, Bottom
};

enum class Column {
	Left, Middle, Right
};

enum class Direction {
	Up, Down, Left, Right
};

enum class Color {
	White =  0b000,
	Green =  0b001,
	Blue =   0b010,
	Orange = 0b011,
	Red = 	 0b100,
	Yellow = 0b101,
};

enum WholeSide {
	WhiteSide =  0x0000000,
	GreenSide =  0x1249249,
	BlueSide =   0x2492492,
	OrangeSide = 0x36DB6DB,
	RedSide = 	 0x4924924,
	YellowSide = 0x5B6DB6D,
}


struct Cube {

uint32_t top, bottom,
		 front, back,
		 left, right;

 	Cube();
	Cube(uint32_t   top, bottom,
					front, back,
					left, right);

	Cube rotate(Direction dir, std::variant<Column, Row> line);
	bool is_solved();

};
