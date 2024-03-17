
#include "cube.hpp"


Cube::Cube() {
	top =    GreenFace;
	bottom = BlueFace;
	front =  WhiteFace;
	back =   YellowFace;
	left =   OrangeFace;
	right =  RedFace;
}

uint32_t rotFaceLeft(uint32_t face);
uint32_t rotFaceRight(uint32_t face);
uint32_t rotFace180(uint32_t face);


Cube Cube::rotHoriz(Row line, Direction dir) {

	Cube newCube = *this;

	uint32_t maskType;
	uint32_t* outwardFace;
	
	switch (line) {
		case (Row::Top) : {
			outwardFace = &newCube.top;
			maskType =  static_cast<uint32_t>(Mask::Row::Top);
			break;
		}

		case (Row::Middle): {
			maskType =  static_cast<uint32_t>(Mask::Row::Middle);
			break;
		}

		case (Row::Bottom): {
			outwardFace = &newCube.bottom;
			maskType =  static_cast<uint32_t>(Mask::Row::Bottom);
			break;
		}
	}

	if (line != Row::Middle) {
		switch (dir) {
			case (Direction::Left) : {
				*outwardFace = rotFaceRight(*outwardFace);
				break;
			}

			case (Direction::Right) : {
				*outwardFace = rotFaceLeft(*outwardFace);
				break;
			}

			case (Direction::_180) : {
				*outwardFace = rotFace180(*outwardFace);
				break;
			}
		}
	}

	switch (dir) {
		case (Direction::Left) : {
			newCube.front &= ~maskType;
			newCube.front |= (right&maskType);

			newCube.right &= ~maskType;
			newCube.right |= (newCube.back&maskType);

			newCube.left &= ~maskType;
			newCube.left |= (front&maskType);

			newCube.back &= ~maskType;
			newCube.back |= (left&maskType);
			break;
		}

		case (Direction::Right) : {
			newCube.front &= ~maskType;
			newCube.front |= (left&maskType);

			newCube.left &= ~maskType;
			newCube.left |= (newCube.back&maskType);

			newCube.right &= ~maskType;
			newCube.right |= (front&maskType);

			newCube.back &= ~maskType;
			newCube.back |= (right&maskType);
			break;
		}

		case (Direction::_180) : {
			newCube.front &= ~maskType;
			newCube.front |= (newCube.back&maskType);

			newCube.right &= ~maskType;
			newCube.right |= (left&maskType);

			newCube.left &= ~maskType;
			newCube.left |= (front&maskType);

			newCube.back &= ~maskType;
			newCube.back |= (front&maskType);
			break;
		}
	}


	return newCube;
}



Cube Cube::rotVert(Column line, Direction dir) {

	Cube newCube = *this;

	uint32_t maskType;

	//((bottom&maskType)<<6) >> backOrMaskOffset


	//backNotMask = static_cast<uint32_t>(Mask::Column::Left);
	//backOrMask = (front&maskType) >> 6;

	//Back column rotations require special masks
	//Left column of front is right column of back and vice versa
	//uint32_t backNotMask;
	//uint32_t backOrMask;

	uint32_t* outwardFace;

	
	switch (line) {
		case (Column::Left) : {
			//didn't know you couldn't use scoped enums as
			//integers when I originally wrote this lol
			outwardFace = &newCube.left;
			maskType = static_cast<uint32_t>(Mask::Column::Left);

			break;
		}

		case (Column::Middle): {
			maskType =  static_cast<uint32_t>(Mask::Column::Middle);
			break;
		}

		case (Column::Right): {
			outwardFace = &newCube.right;
			maskType =  static_cast<uint32_t>(Mask::Column::Right);

			break;
		}
	}

	if (line != Column::Middle) {
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

	//Invert columns and rows before and after processing
	newCube.back =   ((newCube.back&static_cast<uint32_t>(Mask::Row::Bottom)) << 3*3*2)
					| ((newCube.back&static_cast<uint32_t>(Mask::Row::Middle))       )
					| ((newCube.back&static_cast<uint32_t>(Mask::Row::Top))    >> 3*3*2);

	newCube.back =    ((newCube.back&static_cast<uint32_t>(Mask::Column::Right)) << 3*2)
			    	| ((newCube.back&static_cast<uint32_t>(Mask::Column::Middle))      )
					| ((newCube.back&static_cast<uint32_t>(Mask::Column::Left))  >> 3*2);

	switch (dir) {
		case (Direction::Up) : {
			newCube.front &= ~maskType;
			newCube.front |= (bottom&maskType);

			newCube.top &= ~maskType;
			newCube.top |= (front&maskType);

			newCube.bottom &= ~maskType;
			newCube.bottom |= (newCube.back&maskType);

			newCube.back &= ~maskType;
			newCube.back |= (top&maskType);
			break;
		}

		case (Direction::Down) : {
			newCube.front &= ~maskType;
			newCube.front |= (top&maskType);

			newCube.bottom &= ~maskType;
			newCube.bottom |= (front&maskType);

			newCube.top &= ~maskType;
			newCube.top |= (newCube.back&maskType);

			newCube.back &= ~maskType;
			newCube.back |= (bottom&maskType);
			break;
		}

		case (Direction::_180) : {
			newCube.front &= ~maskType;
			newCube.front |= (newCube.back&maskType);

			newCube.top &= ~maskType;
			newCube.top |= (bottom&maskType);

			newCube.bottom &= ~maskType;
			newCube.bottom |= (top&maskType);

			newCube.back &= ~maskType;
			newCube.back |= (front&maskType);
			break;
		}
	}

	newCube.back =    ((newCube.back&static_cast<uint32_t>(Mask::Row::Bottom)) << 3*3*2)
					| ((newCube.back&static_cast<uint32_t>(Mask::Row::Middle))       )
					| ((newCube.back&static_cast<uint32_t>(Mask::Row::Top))    >> 3*3*2);

	newCube.back =    ((newCube.back&static_cast<uint32_t>(Mask::Column::Right)) << 3*2)
			    	| ((newCube.back&static_cast<uint32_t>(Mask::Column::Middle))      )
					| ((newCube.back&static_cast<uint32_t>(Mask::Column::Left))  >> 3*2);

	return newCube;
}


uint32_t Cube::rotFaceLeft(uint32_t face) {
	uint32_t newFace = 0x0000;
	//(0b111 << original tile index) (<< or >>) difference of new index

	//Group the same shift operations once you are sure this works
	newFace |= (face & (0b111<<0*3)) << 6*3;
	newFace |= (face & (0b111<<1*3)) << 2*3;
	newFace |= (face & (0b111<<2*3)) >> 2*3;
	newFace |= (face & (0b111<<3*3)) << 4*3;

	newFace |= (face & (0b111<<4*3));

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
	newFace |= (face & (0b111<<3*3)) >> 2*3;

	newFace |= (face & (0b111<<4*3));

	newFace |= (face & (0b111<<5*3)) << 2*3;
	newFace |= (face & (0b111<<6*3)) >> 6*3;
	newFace |= (face & (0b111<<7*3)) >> 4*3;
	newFace |= (face & (0b111<<8*3)) >> 2*3;

	return newFace;
}

//Change later
uint32_t Cube::rotFace180(uint32_t face) {
	/*
	uint32_t newFace = 0x0000;

	newFace |= (face & (0b111<<0*3)) << 8*3;
	newFace |= (face & (0b111<<1*3)) << 6*3;
	newFace |= (face & (0b111<<2*3)) << 4*3;
	newFace |= (face & (0b111<<3*3)) << 2*3;

	newFace |= (face & (0b111<<4*3));

	newFace |= (face & (0b111<<5*3)) >> 2*3;
	newFace |= (face & (0b111<<6*3)) >> 4*3;
	newFace |= (face & (0b111<<7*3)) << 6*3;
	newFace |= (face & (0b111<<8*3)) >> 8*3;*/

	return rotFaceRight(rotFaceRight(face));
}


//bool isSolved() {}

//terminal output written by ChatGPT 4
std::ostream& operator<<(std::ostream& os, const Cube& cube) {
    std::array<char, 6> const colors {{
        'W', // White  0b000
        'G', // Green  0b001
        'B', // Blue   0b010
        'O', // Orange 0b011
        'R', // Red    0b100
        'Y'  // Yellow 0b101
    }};

    // Lambda to extract the color character from a face value
    auto getColorChar = [&colors](uint32_t face, int position) -> char {
    	//Cubes are indexed starting from top left
    	//and move right in the output code
        return colors[(face >> (8*3 - position*3)) & 0x7];
    };

    // Print the top face
    for (int i = 0; i < 9; i += 3) {
        os << "    "; // Align with the middle faces
        os << getColorChar(cube.top, i)
           << getColorChar(cube.top, i+1)
           << getColorChar(cube.top, i+2) << '\n';
    }

    // Print the middle four faces (left, front, right, back)
    for (int i = 0; i < 9; i += 3) {
        os << getColorChar(cube.left, i)
           << getColorChar(cube.left, i+1)
           << getColorChar(cube.left, i+2) << ' ';
        os << getColorChar(cube.front, i)
           << getColorChar(cube.front, i+1)
           << getColorChar(cube.front, i+2) << ' ';
        os << getColorChar(cube.right, i)
           << getColorChar(cube.right, i+1)
           << getColorChar(cube.right, i+2) << ' ';
        os << getColorChar(cube.back, i)
           << getColorChar(cube.back, i+1)
           << getColorChar(cube.back, i+2) << '\n';
    }

    // Print the bottom face
    for (int i = 0; i < 9; i += 3) {
        os << "    "; // Align with the middle faces
        os << getColorChar(cube.bottom, i)
           << getColorChar(cube.bottom, i+1)
           << getColorChar(cube.bottom, i+2) << '\n';
    }

    return os;
}

