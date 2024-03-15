
#include "cube.hpp"


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
	uint32_t* outwardFace;
	
	switch (line) {
		case (Row::Top) : {
			outwardFace = &top;
			maskType =  static_cast<uint32_t>(Mask::Row::Top);
			break;
		}

		case (Row::Middle): {
			maskType =  static_cast<uint32_t>(Mask::Row::Middle);
			break;
		}

		case (Row::Bottom): {
			outwardFace = &bottom;
			maskType =  static_cast<uint32_t>(Mask::Row::Bottom);
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

	uint32_t tmp = front&maskType;

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

			//no need for tmp
			tmp = right&maskType;

			right &= ~maskType;
			right |= (left&maskType);

			left &= ~maskType;
			left |= tmp;
			break;
		}
	}

	return cube
}



Cube Cube::rotateVert(Column line, Direction dir) {

	uint32_t maskType;
	uint32_t* outwardFace;

	
	switch (line) {
		case (Column::Left) : {
			outwardFace = &left;
			//didn't know you couldn't use scoped enums as
			//integers when I originally wrote this lol
			maskType = static_cast<uint32_t>(Mask::Column::Left);
			break;
		}

		case (Column::Middle): {
			maskType =  static_cast<uint32_t>(Mask::Column::Middle);
			break;
		}

		case (Column::Right): {
			outwardFace = &right;
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

	uint32_t tmp = front&maskType;

	switch (dir) {
		case (Direction::Up) : {
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

		case (Direction::Down) : {
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


uint32_t Cube::rotFaceLeft(uint32_t face) {
	uint32_t newFace = 0x0000;
	//(0b111 << original tile index) (<< or >>) difference of new index

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

/*
//Written by ChatGPT cause I don't feel like writing this part
std::ostream& operator<<(std::ostream& os, const Cube& cube) {
    std::array<char, 6> const colors {{
        'W', // White  0b000
        'G', // Green  0b001
        'B', // Blue   0b010
        'O', // Orange 0b011
        'R', // Red    0b100
        'Y'  // Yellow 0b101
    }};

    // A lambda function to extract and print a single row of a face
    auto printRow = [&](uint32_t face, Line row) {
        int shift = (row == Line::Top ? 6 : row == Line::Middle ? 3 : 0) * 3;
        for (int col = 0; col < 3; ++col) {
            int colorIndex = (face >> (shift + col * 3)) & 0x07;
            os << colors[colorIndex];
        }
    };

    // Print the top face
    for (int row = 0; row < 3; ++row) {
        os << "      "; // Spacing to align the top face
        printRow(cube.top, static_cast<Line>(row));
        os << '\n';
    }

    // Print the middle four faces (left, front, right, back)
    for (int row = 0; row < 3; ++row) {
        printRow(cube.left, static_cast<Line>(row));
        os << " ";
        printRow(cube.front, static_cast<Line>(row));
        os << " ";
        printRow(cube.right, static_cast<Line>(row));
        os << " ";
        printRow(cube.back, static_cast<Line>(row));
        os << '\n';
    }

    // Print the bottom face
    for (int row = 0; row < 3; ++row) {
        os << "      "; // Spacing to align the bottom face
        printRow(cube.bottom, static_cast<Line>(row));
        os << '\n';
    }

    return os;
}*/
