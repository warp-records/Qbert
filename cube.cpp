
#include "rubix.hpp"


Cube::Cube() {
	top =    WhiteFace;
	bottom = GreenFace;
	front =  BlueFace;
	back =   OrangeFace;
	left =   RedFace;
	right =  YellowFace;
}

uint32_t rotFaceLeft(uint32_t face);
uint32_t rotFaceRight(uint32_t face);
uint32_t rotFace180(uint32_t face);

Cube Cube::rotHoriz(Row line, Direction dir) {

	uint32_t maskType;
	
	switch (line) {
		case (Row::Top) : {
			outwardFace = &top;
			maskType = Mask::Row::Top;
			break;
		}

		case (Row::Middle): {
			maskType = Mask::Row::Middle;
			break;
		}

		case (Row::Bottom): {
			outwardFace = &bottom;
			maskType = Mask::Row::Bottom;
			break;
		}
	}

	if (line != Row::Middle) {
		switch (dir) {
			case (Direction::Left) : {
				*outwardFace = rotFaceLeft(*outwardFace);
				break;
			}

			case (Direction::Right) : {
				*outwardFace = rotFaceRight(*outwardFace);
				break;
			}

			case (Direction::_180) : {
				*outwardFace = rotFace180(*outwardFace);
				break;
			}
		}
	}

	uint16_t tmp = front&maskType;

	switch (dir) {
		case (Direction::Left) : {
			front &= ~maskType;
			front |= (right&maskType);

			right &= ~maskType;
			right |= (back&maskType);

			back &= ~maskType;
			back |= (left&maskType);

			left &= ~maskType;
			left |= tmp;
			break;
		}

		case (Direction::Right) : {
			front &= ~maskType;
			front |= (left&maskType);

			left &= ~maskType;
			left |= (back&maskType);

			back &= ~maskType;
			back |= (right&maskType);

			right &= ~maskType;
			right |= tmp;
			break;
		}

		case (Direction::_180) : {
			front &= ~maskType;
			front |= (back&maskType);

			back &= ~maskType;
			back |= tmp;

			tmp = right&maskType;

			right &= ~maskType;
			right |= (left&maskType);

			left &= ~maskType;
			left |= tmp;
			break;
		}
	}
}

/*
Cube Cube::rotateVert(Column line, Direction dir) {

	uint32_t maskType;
	
	switch (line) {
		case (Row::Left) : {
			outwardFace = &left;
			maskType = Mask::Column::Left;
			break;
		}

		case (Row::Middle): {
			maskType = Mask::Column::Middle;
			break;
		}

		case (Row::Bottom): {
			outwardFace = &bottom;
			maskType = Mask::Column::Right;
			break;
		}
	}

	if (line != Row::Middle) {
		switch (dir) {
			case (Direction::Up) : {
				*outwardFace = rotFaceLeft(*outwardFace);
				break;
			}

			case (Direction::Down) : {
				*outwardFace = rotFaceRight(*outwardFace);
				break;
			}

			case (Direction::_180) : {
				*outwardFace = rotFace180(*outwardFace);
				break;
			}
		}
	}

	uint16_t tmp = top&maskType;

	top &= ~maskType;
	top |= (right&maskType);

	right &= ~maskType;
	right |= (back&maskType);

	back &= ~maskType;
	back |= (left&maskType);

	left &= ~maskType;
	left |= tmp;
}*/


uint32_t Cube::rotFaceLeft(uint32_t face) {
	uint32_t newFace = 0x0000;
	//(0b111 << original position offset) (<< or >>) new offset by shift
	//Group the same shift operations once you are sure this works
	newFace |= (face & (0b111<<0*3)) << 6*3;
	newFace |= (face & (0b111<<1*3)) << 2*3;
	newFace |= (face & (0b111<<2*3)) >> 2*3;
	newFace |= (face & (0b111<<3*3)) << 4*3;
	newFace |= (face & (0b111<<5*3)) >> 4*3;
	newFace |= (face & (0b111<<6*3)) << 2*3;
	newFace |= (face & (0b111<<7*3)) >> 2*3;
	newFace |= (face & (0b111<<8*3)) >> 6*3;

	return newFace;
}

uint32_t Cube::rotFaceRight(uint32_t face) {
	uint32_t newFace = 0x0000;

	newFace |= (face & (0b111<<0*3)) << 2*3;
	newFace |= (face & (0b111<<1*3)) << 4*3;
	newFace |= (face & (0b111<<2*3)) << 6*3;
	newFace |= (face & (0b111<<3*3)) << 2*3;
	newFace |= (face & (0b111<<5*3)) << 2*3;
	newFace |= (face & (0b111<<6*3)) << 6*3;
	newFace |= (face & (0b111<<7*3)) << 4*3;
	newFace |= (face & (0b111<<8*3)) >> 2*3;

	return newFace;
}

uint32_t Cube::rotFace180(uint32_t face) {
	uint32_t newFace = 0x0000;

	newFace |= (face & (0b111<<0*3)) << 2*3;
	newFace |= (face & (0b111<<1*3)) << 4*3;
	newFace |= (face & (0b111<<2*3)) << 6*3;
	newFace |= (face & (0b111<<3*3)) << 2*3;
	newFace |= (face & (0b111<<5*3)) << 2*3;
	newFace |= (face & (0b111<<6*3)) << 6*3;
	newFace |= (face & (0b111<<7*3)) << 4*3;
	newFace |= (face & (0b111<<8*3)) >> 2*3;

	return newFace;
}

uint32_t Cube::rotFace180(uint32_t face) {
	uint32_t newFace = 0x0000;

	newFace |= (face & (0b111<<0*3)) << 8*3;
	newFace |= (face & (0b111<<1*3)) << 6*3;
	newFace |= (face & (0b111<<2*3)) << 4*3;
	newFace |= (face & (0b111<<3*3)) << 2*3;
	newFace |= (face & (0b111<<5*3)) >> 2*3;
	newFace |= (face & (0b111<<6*3)) >> 4*3;
	newFace |= (face & (0b111<<7*3)) << 6*3;
	newFace |= (face & (0b111<<8*3)) >> 8*3;

	return newFace;
}


//bool isSolved() {}