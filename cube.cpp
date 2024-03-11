
#include "rubix.hpp"


Cube::Cube() {
	top =    WhiteSide;
	bottom = GreenSide;
	front =  BlueSide;
	back =   OrangeSide;
	left =   RedSide;
	right =  YellowSide;
}

//Cube rotate(Direction dir, std::variant<Column, Row> line) {}
//bool is_solved() {}