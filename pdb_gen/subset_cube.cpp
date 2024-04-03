
#include "subset_cube.hpp"
#include <cstdint>
#include <cassert>
#include <bit>

MiniCube::MiniCube() {
	front =  WhiteFace;
	top =    GreenFace;
	left =   BlueFace;

	back =   OrangeFace;
	bottom = RedFace;
	right =  YellowFace;
}

uint16_t rotFaceLeft(uint16_t face);
uint16_t rotFaceRight(uint16_t face);
uint16_t rotFace180(uint16_t face);


MiniCube MiniCube::rotHoriz(Row line, Direction dir) const {

	//180 degree rotations are broken
	if (dir == Direction::_180)
		return rotHoriz(line, Direction::Left).rotHoriz(line, Direction::Left);

	//Ensure cube is normalized, don't feel like patching code lol
	if (line == Row::Top)
		return rotHoriz(Row::Bottom, dir==Direction::Left ? Direction::Right : Direction::Left);

	MiniCube newCube = *this;

	uint16_t maskType;
	uint16_t* outwardFace;
	
	switch (line) {
		case (Row::Top) : {
			outwardFace = &newCube.top;
			maskType =  MiniMask::Row::Top;
			break;
		}

		case (Row::Bottom): {
			outwardFace = &newCube.bottom;
			maskType =  MiniMask::Row::Bottom;
			break;
		}
	}

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



MiniCube MiniCube::rotVert(Column line, Direction dir) const {

	//180 degree rotations are broken
	if (dir == Direction::_180)
		return rotVert(line, Direction::Up).rotVert(line, Direction::Up);


	if (line == Column::Left)
		return rotVert(Column::Right, dir==Direction::Up ? Direction::Down : Direction::Up);

	MiniCube newCube = *this;

	uint16_t maskType;

	uint16_t* outwardFace;

	
	switch (line) {
		case (Column::Left) : {
			outwardFace = &newCube.left;
			maskType = MiniMask::Column::Left;
			break;
		}

		case (Column::Right): {
			outwardFace = &newCube.right;
			maskType =  MiniMask::Column::Right;
			break;
		}
	}


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

	//Invert columns and rows before and after processing
	newCube.back = rotFace180(newCube.back);

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

	newCube.back = rotFace180(newCube.back);

	return newCube;
}


uint16_t MiniCube::rotFaceLeft(uint16_t face) {
	uint16_t newFace = 0x0000;
	//(0b111 << original tile index) (<< or >>) difference of new index

	newFace |= (face 	  & 0b111) << 2*3;
	newFace |= (face>>1*3 & 0b111);
	newFace |= (face>>2*3 & 0b111) << 3*3;
	newFace |= (face>>3*3 & 0b111) << 1*3;

	return newFace;
}

uint16_t MiniCube::rotFaceRight(uint16_t face) {
	uint16_t newFace = 0x0000;

	newFace |= (face 	  & 0b111) << 1*3;
	newFace |= (face>>1*3 & 0b111) << 3*3;
	newFace |= (face>>2*3 & 0b111);
	newFace |= (face>>3*3 & 0b111) << 2*3;

	return newFace;
}

//Change later
uint16_t MiniCube::rotFace180(uint16_t face) {
	uint16_t newFace = 0x0000;

	newFace |= (face   	  & 0b111) << 3*3;
	newFace |= (face>>1*3 & 0b111) << 2*3;
	newFace |= (face>>2*3 & 0b111) << 1*3;
	newFace |= (face>>3*3 & 0b111);

	return newFace;
}

MiniCube::CubieInfo MiniCube::getCubieInfo(bool x, bool y, bool z) const {
    uint16_t xFace = x==0 ? left : right;
    //checked
    xFace >>= (x^z)==0 ? 0*3 : 1*3;
    xFace >>= y==0 ?     2*3 : 0*3;
    xFace &= 0b111;

    uint16_t yFace = y==0 ? top : bottom;
    //checked
    yFace >>= x==0 ?     1*3 : 0*3;
    yFace >>= (y^z)==0 ? 0*3 : 2*3;
    yFace &= 0b111;

    uint16_t zFace = z==0 ? front : back;
    //check
    //I think we actually ignore z here since the back is inverted!
    zFace >>= (x^z)==0 ?     1*3 : 0*3;
    zFace >>= y==0 ?     2*3 : 0*3;
    zFace &= 0b111;

    //implement ordering here

    uint8_t id = xFace^yFace^zFace;

    //I think this'll work
    uint8_t orientation = 0;
    orientation += xFace > yFace;
    orientation += yFace > zFace;

	return CubieInfo{id, orientation};
}

std::array<MiniCube, 18> MiniCube::getNeighbors() const {

	//Right view must be used for cube to be normalized
	MiniCube sideViewCube = changePerspective(Perspective::Right);
	std::array<MiniCube, 6> xAxisRots {{
		sideViewCube.rotVert(Column::Left, Direction::Up), sideViewCube.rotVert(Column::Left, Direction::Down),
		sideViewCube.rotVert(Column::Right, Direction::Up), sideViewCube.rotVert(Column::Right, Direction::Down),
		sideViewCube.rotVert(Column::Left, Direction::_180), sideViewCube.rotVert(Column::Right, Direction::_180)
	}};
	std::for_each(xAxisRots.begin(), xAxisRots.end(), [](MiniCube& qb) { qb = qb.changePerspective(Perspective::Left); });


	std::array<MiniCube, 6> yAxisRots {{
		rotVert(Column::Left, Direction::Up), rotVert(Column::Left, Direction::Down),
		rotVert(Column::Right, Direction::Up), rotVert(Column::Right, Direction::Down),
		rotVert(Column::Left, Direction::_180), rotVert(Column::Right, Direction::_180)
	}};


	std::array<MiniCube, 6> zAxisRots {{
		rotHoriz(Row::Top, Direction::Left), rotHoriz(Row::Top, Direction::Right),
		rotHoriz(Row::Bottom, Direction::Left), rotHoriz(Row::Bottom, Direction::Right),
		rotHoriz(Row::Top, Direction::_180), rotHoriz(Row::Bottom, Direction::_180), 
	}};

	std::array<MiniCube, 18> final;
	std::copy(xAxisRots.begin(), xAxisRots.begin(), final.begin());
	std::copy(yAxisRots.begin(), yAxisRots.begin(), final.begin()+xAxisRots.size());
	std::copy(zAxisRots.begin(), zAxisRots.begin(), final.begin()+xAxisRots.size()+yAxisRots.size());

	return final;
}


//terminal output written by ChatGPT 4
std::ostream& operator<<(std::ostream& os, const MiniCube& cube) {
    std::array<char, 6> const colors {{
        'W', // White  0b000
        'G', // Green  0b001
        'B', // Blue   0b010
        'O', // Orange 0b011
        'R', // Red    0b100
        'Y'  // Yellow 0b101
    }};

    auto getColorChar = [&colors](uint16_t face, int position) -> char {
        // Adjust bit shifting for a 2x2 cube, indexing from top left and moving right
        return colors[(face >> (3*3 - position*3)) & 0x7];
    };

    // Print the top face
    for (int i = 0; i < 4; i += 2) {
        os << "   "; // Adjust alignment for a 2x2 cube
        os << getColorChar(cube.top, i)
           << getColorChar(cube.top, i+1) << '\n';
    }

    // Print the middle faces (left, front, right, back)
    for (int i = 0; i < 4; i += 2) {
        os << getColorChar(cube.left, i)
           << getColorChar(cube.left, i+1) << ' ';
        os << getColorChar(cube.front, i)
           << getColorChar(cube.front, i+1) << ' ';
        os << getColorChar(cube.right, i)
           << getColorChar(cube.right, i+1) << ' ';
        os << getColorChar(cube.back, i)
           << getColorChar(cube.back, i+1) << '\n';
    }

    // Print the bottom face
    for (int i = 0; i < 4; i += 2) {
        os << "   "; // Adjust alignment for a 2x2 cube
        os << getColorChar(cube.bottom, i)
           << getColorChar(cube.bottom, i+1) << '\n';
    }

    return os;
}





//Naive compare implementation, for debugging
/*
bool operator==(MiniCube const& lhs, MiniCube const& rhs) {
	MiniCube lhsPerm = lhs;

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			bool equalFaces = lhsPerm.top==rhs.top && lhsPerm.bottom==rhs.bottom &&
								lhsPerm.left==rhs.left && lhsPerm.right==rhs.right &&
								lhsPerm.front==rhs.front && lhsPerm.back==rhs.back;
			if (equalFaces)
				return true;

			lhsPerm = lhsPerm.rotHoriz(Row::Top, Direction::Left);
			lhsPerm = lhsPerm.rotHoriz(Row::Bottom, Direction::Left);
		}

		lhsPerm = lhsPerm.rotVert(Column::Left, Direction::Down);
		lhsPerm = lhsPerm.rotVert(Column::Right, Direction::Down);
	}

	return false;
}*/

bool operator==(MiniCube const& lhs, MiniCube const& rhs) {
	return lhs.top==rhs.top && lhs.bottom==rhs.bottom &&
								lhs.left==rhs.left && lhs.right==rhs.right &&
								lhs.front==rhs.front && lhs.back==rhs.back;
};

bool operator!=(MiniCube const& lhs, MiniCube const& rhs) {
	return !(lhs==rhs);
}

