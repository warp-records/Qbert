
#include "cube.hpp"
#include "pdb_gen/subset_cube.hpp"
#include <cassert>

Cube::Cube() {
	front =  WhiteFace;
	top =    GreenFace;
	left =   RedFace;

	back =   YellowFace;
	bottom = BlueFace;
	right =  OrangeFace;
}

uint32_t rotFaceLeft(uint32_t face);
uint32_t rotFaceRight(uint32_t face);
uint32_t rotFace180(uint32_t face);


Cube Cube::rotHoriz(Row line, Direction dir) const {


	//Don't feel like properly coding normalization
	if (line == Row::Top) {
		Direction opposite = dir==Direction::Left ? Direction::Right : Direction::Left;
		opposite = dir==Direction::_180 ? Direction::_180 : dir;
		return rotHoriz(Row::Middle, opposite).rotHoriz(Row::Bottom, opposite);
	}

	Cube newCube = *this;

	uint32_t maskType;
	uint32_t* outwardFace;
	
	switch (line) {
		case (Row::Top) : {
			outwardFace = &newCube.top;
			maskType =  Mask::Row::Top;
			break;
		}

		case (Row::Middle): {
			maskType =  Mask::Row::Middle;
			break;
		}

		case (Row::Bottom): {
			outwardFace = &newCube.bottom;
			maskType =  Mask::Row::Bottom;
			break;
		}
	}

	if (line != Row::Middle) {
		switch (dir) {
			case (Direction::Left) : {
				*outwardFace = line==Row::Top ? rotFaceRight(*outwardFace) : rotFaceLeft(*outwardFace);
				break;
			}

			case (Direction::Right) : {
				*outwardFace = line==Row::Top ? rotFaceLeft(*outwardFace) : rotFaceRight(*outwardFace);
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
			newCube.left |= (right&maskType);

			newCube.back &= ~maskType;
			newCube.back |= (front&maskType);
			break;
		}
	}


	return newCube;
}


Cube Cube::rotVert(Column line, Direction dir) const {

	if (line == Column::Left) {
		Direction opposite = dir==Direction::Up ? Direction::Down : Direction::Up;
		opposite = dir==Direction::_180 ? Direction::_180 : dir;
		return rotVert(Column::Middle, opposite).rotVert(Column::Right, opposite);
	}


	Cube newCube = *this;

	uint32_t maskType;

	//((bottom&maskType)<<6) >> backOrMaskOffset


	//backNotMask = Mask::Column::Left);
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
			maskType = Mask::Column::Left;

			break;
		}

		case (Column::Middle): {
			maskType =  Mask::Column::Middle;
			break;
		}

		case (Column::Right): {
			outwardFace = &newCube.right;
			maskType =  Mask::Column::Right;

			break;
		}
	}

	if (line != Column::Middle) {
		switch (dir) {
			case (Direction::Up) : {
				*outwardFace = line==Column::Left ? rotFaceLeft(*outwardFace) : rotFaceRight(*outwardFace);
				break;
			}

			case (Direction::Down) : {
				*outwardFace = line==Column::Left ? rotFaceRight(*outwardFace) : rotFaceLeft(*outwardFace);
				break;
			}

			case (Direction::_180) : {
				*outwardFace = rotFace180(*outwardFace);
				break;
			}
		}
	}

	//Invert columns and rows before and after processing
	newCube.back =   ((newCube.back&Mask::Row::Bottom) << 3*3*2)
					| ((newCube.back&Mask::Row::Middle)       )
					| ((newCube.back&Mask::Row::Top)    >> 3*3*2);

	newCube.back =    ((newCube.back&Mask::Column::Right) << 3*2)
			    	| ((newCube.back&Mask::Column::Middle)      )
					| ((newCube.back&Mask::Column::Left)  >> 3*2);

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

	newCube.back =    ((newCube.back&Mask::Row::Bottom) << 3*3*2)
					| ((newCube.back&Mask::Row::Middle)       )
					| ((newCube.back&Mask::Row::Top)    >> 3*3*2);

	newCube.back =    ((newCube.back&Mask::Column::Right) << 3*2)
			    	| ((newCube.back&Mask::Column::Middle)      )
					| ((newCube.back&Mask::Column::Left)  >> 3*2);

	return newCube;
}

//Only coded to work with normalized cube rotations
Cube Cube::rotXaxis(CrossSection line, Direction dir) const {

	if (line == CrossSection::Front) {
		Direction opposite = dir==Direction::Right ? Direction::Left : Direction::Right;
		opposite = dir==Direction::_180 ? Direction::_180 : opposite;
		return rotXaxis(CrossSection::Middle, opposite).rotXaxis(CrossSection::Back, opposite);
	}


	Cube newCube = *this;

	if (line == CrossSection::Back) {
		switch (dir) {
			case (Direction::Right) : {
				newCube.back = rotFaceLeft(newCube.back);
				break;
			}

			case (Direction::Left) : {
				newCube.back = rotFaceRight(newCube.back);
				break;
			}

			case (Direction::_180) : {
				newCube.back = rotFace180(newCube.back);
				break;
			}
		}
	}

	uint32_t topMask = line==CrossSection::Back ? Mask::Row::Top : Mask::Row::Middle;
	uint32_t leftMask = line==CrossSection::Back ? Mask::Column::Left : Mask::Column::Middle;
	uint32_t bottomMask = line==CrossSection::Back ? Mask::Row::Bottom : Mask::Row::Middle;
	uint32_t rightMask = line==CrossSection::Back ? Mask::Column::Right : Mask::Column::Middle;

	newCube.top &= ~topMask;
	newCube.right &= ~rightMask;
	newCube.bottom &= ~bottomMask;
	newCube.left &= ~leftMask;

	//WRONG DIRECTIOBN
	switch (dir) {
		case (Direction::Right) : {
			newCube.top |= rotFaceRight(left&leftMask);			
			newCube.right |= rotFaceRight(top&topMask);
			newCube.bottom |= rotFaceRight(right&rightMask);
			newCube.left |= rotFaceRight(bottom&bottomMask);
			break;
		}

		case (Direction::Left) : {
			newCube.top |= rotFaceLeft(right&rightMask);			
			newCube.left |= rotFaceLeft(top&topMask);
			newCube.bottom |= rotFaceLeft(left&leftMask);
			newCube.right |= rotFaceLeft(bottom&bottomMask);
			break;
		}

		case (Direction::_180) : {
			newCube.top |= rotFace180(bottom&bottomMask);			
			newCube.bottom |= rotFace180(top&topMask);
			newCube.left |= rotFace180(right&rightMask);
			newCube.right |= rotFace180(left&leftMask);
			break;
		}
	}

	return newCube;
}


uint32_t Cube::reflectFaceXaxis(uint32_t face) {
	return 	(((face&Mask::Column::Right) << 3*2)
	 	    | ((face&Mask::Column::Middle)      )
			| ((face&Mask::Column::Left)  >> 3*2));
}

Cube Cube::changePerspective(Perspective per) const {

	Cube qb = *this;

	qb.back = reflectFaceXaxis(qb.back);

	switch (per) {

	case (Perspective::Left) : {
		qb.front = left;
		qb.right = front;
		qb.left = qb.back;
		qb.back = right;

		qb.top = rotFaceLeft(top);
		qb.bottom = rotFaceRight(bottom);
		break;
	}

	case (Perspective::Right) : {
		qb.front = right;
		qb.left = front;
		qb.right = qb.back;
		qb.back = left;

		qb.top = rotFaceRight(top);
		qb.bottom = rotFaceLeft(bottom);
		break;
	}

	}

	qb.back = reflectFaceXaxis(qb.back);


	return qb;
}


std::array<Cube, 27> Cube::getNeighbors() const {

	std::array<Cube, 9> xAxisRots {{
		rotXaxis(CrossSection::Back, Direction::Right), rotXaxis(CrossSection::Back, Direction::Left), rotXaxis(CrossSection::Back, Direction::_180),
		rotXaxis(CrossSection::Middle, Direction::Right), rotXaxis(CrossSection::Middle, Direction::Left), rotXaxis(CrossSection::Middle, Direction::_180),
		rotXaxis(CrossSection::Front, Direction::Right), rotXaxis(CrossSection::Front, Direction::Left), rotXaxis(CrossSection::Front, Direction::_180)
	}};


	std::array<Cube, 9> yAxisRots {{
		rotVert(Column::Right, Direction::Up), rotVert(Column::Right, Direction::Down), rotVert(Column::Right, Direction::_180), 
		rotVert(Column::Middle, Direction::Up), rotVert(Column::Middle, Direction::Down), rotVert(Column::Middle, Direction::_180),
		rotVert(Column::Left, Direction::Up), rotVert(Column::Left, Direction::Down), rotVert(Column::Left, Direction::_180)
	}};


	std::array<Cube, 9> zAxisRots {{
		rotHoriz(Row::Bottom, Direction::Left), rotHoriz(Row::Bottom, Direction::Right), rotHoriz(Row::Bottom, Direction::_180),
		rotHoriz(Row::Middle, Direction::Right), rotHoriz(Row::Middle, Direction::Left), rotHoriz(Row::Middle, Direction::_180), 
		rotHoriz(Row::Top, Direction::Right), rotHoriz(Row::Top, Direction::Left), rotHoriz(Row::Top, Direction::_180)

	}};

	std::array<Cube, 27> final;
	std::copy(xAxisRots.begin(), xAxisRots.end(), final.begin());
	std::copy(yAxisRots.begin(), yAxisRots.end(), final.begin()+xAxisRots.size());
	std::copy(zAxisRots.begin(), zAxisRots.end(), final.begin()+xAxisRots.size()+yAxisRots.size());

	return final;
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



//Good enough (I think)
bool Cube::strongSolvedCheck() const {

	std::array<uint32_t, 6> const faces {{
		top, bottom, front, back, left, right
	}};

	std::array<uint32_t, 6> const solvedFaces {{
		WhiteFace, GreenFace, BlueFace,
		OrangeFace, RedFace, YellowFace
	}};

	for (auto solvedFace : solvedFaces) {
		bool foundFlag = false;

		for (auto face : faces) {
			foundFlag = solvedFace==face || foundFlag;
		}

		if (!foundFlag)
			return false;
	}

	return true;
}



//DEBUG CODE:
//------------------------------------
//Checks for repeat corners
bool Cube::hasProperCorners() const {
	std::array<bool, 8> foundCubieIDs {{0, 0, 0, 0, 0, 0, 0, 0 }};

	MiniCube mini(*this);

	for (int i = 0; i < 8; i++) {

		int id = mini.getCubieInfo(i&0b100, i&0b10, i&0b001).id;
		if (foundCubieIDs[id]) {
			return false;
		}

		foundCubieIDs[id] = true;
	}

	return true;
}

//Thanks ChatGPT!
bool Cube::isValidColorDistribution() const {
    std::array<int, 6> colorCounts = {0, 0, 0, 0, 0, 0}; // White, Green, Red, Yellow, Blue, Orange

    // Helper lambda to count colors on a single face
    auto countColorsOnFace = [&](uint32_t face) {
        for (int i = 0; i < 9; ++i) { // 9 stickers per face
            uint32_t color = (face >> (i * 3)) & 0b111; // Extract 3 bits per color
            colorCounts[color]++;
        }
    };

    // Count colors on each face
    countColorsOnFace(top);
    countColorsOnFace(bottom);
    countColorsOnFace(front);
    countColorsOnFace(back);
    countColorsOnFace(left);
    countColorsOnFace(right);

    // Check for 9 stickers of each color
    for (int count : colorCounts) {
        if (count != 9) {
            return false;
        }
    }
    return true;
}


//terminal output written by ChatGPT 4
std::ostream& operator<<(std::ostream& os, const Cube& cube) {
    std::array<char, 6> const colors {{
        'W',
        'G',
        'R',
        'Y', 
        'B',
        'O'
    }};

    // Lambda to extract the color character from a face value
    auto getColorChar = [&colors](uint32_t face, int position) -> char {
    	//Cubes are indexed starting from top left
    	//and move right in the output code
        return colors[(face >> (8*3 - position*3)) & 0x7];
    };

    os << "\n";

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

