
#include "edge_cubies.hpp"
#include <array>


/*
000 101 = White Orange -
000 001 = White Green -
000 010 = White Red -
000 100 = White Blue -
100 101 = Blue Orange -
101 001 = Orange Green -
001 010 = Green Red -
010 100 = Red Blue -
011 101 = Yellow Orange -
011 100 = Yelow Blue
011 010 = Yellow Red -
011 001 = Yellow Green -

*/

//missing 001 010

 uint32_t EdgeCubies::getIdx() const {

	//bool usedIds[8] { 0, 0, 0, 0, 0, 0, 0, 0 };
	//7!*3^5 ... 2!*3^1

	//HELPFHDSAFADSHNFSDK


	//Maybe try a simpler implementation
	//When "N"" is number of cubies in set
	//Num of permutations: 12!/(12-N)!
	//In this case, 12!/6!

	//factorialSet[i] = (i+6)!/6!
	uint32_t const factorialSet[7] {
		1, 7, 56, 504, 5040, 55440, 665280
	};


	//Index of all cubibes that HAVEN'T been visited
	//First order of business is fixing this shit

	constexpr int PADDING = 6;
	//Only 12 are used
	alignas(uint64_t) uint8_t indices[16] = {
		PADDING, PADDING, PADDING, PADDING, PADDING, PADDING, PADDING, PADDING,
		PADDING, PADDING, PADDING, PADDING, PADDING, PADDING, PADDING, PADDING
	};

	uint32_t idx = 0;

	//PLEASE PLEASE PLEASE FUCKINGGG WORK
	//12!/6!*2^6
	for (int i = 6; i > 0; i--) {
		//For this to work, each Cubie ID must max out to the number left
		auto info = getCubieInfo(i-1);

		idx += factorialSet[i-1]*indices[info.id-PADDING]+factorialSet[i]*info.orientation;

		//I'm a genius for this
		/*
		uint64_t packed = *reinterpret_cast<uint64_t*>(indices);
		uint64_t subtractConst = (0x0101010101010101ULL << (info.id*8));
		packed -= subtractConst;
		*reinterpret_cast<uint64_t*>(indices) = packed;*/

		for (int j = info.id; j < 12; j++) {
			indices[j]--;
		}
	}

	return idx;

}

EdgeCubies::CubieInfo EdgeCubies::getCubieInfo(int idx) const {

    uint16_t face1;
    uint16_t face2;
    //to understand this, visualize the code
    //if you're bad at visualizing things, good fucking luck understanding LOL

    /*
   Front face:
   | |2| |
   |1| |3|
   | |0| |

   Right face:
   | |4| |
   | | | |
   | |5| |
    */

    switch (idx) {
        case 0: {
            face1 = front&(0b111<<3*1)>>3*1;
            face2 = bottom&(0b111<<3*7)>>3*7;
        }

        case 1: {
            face1 = front&(0b111<<3*5)>>3*5;
            face2 = left&(0b111<<3*3)>>3*3;
        }

        case 2: {
            face1 = front&(0b111<<3*7)>>3*7;
            face2 = top&(0b111<<3*1)>>3*1;
        }

        case 3: {
            face1 = front&(0b111<<3*3)>>3*3;
            face2 = right&(0b111<<3*5)>>3*5;
        }

        case 4: {
            face1 = right&(0b111<<3*7)>>3*7;
            face2 = top&(0b111<<3*3)>>3*3;
        }

        case 5: {
            face1 = right&(0b111<<3*1)>>3*1;
            face2 = bottom&(0b111<<3*3)>>3*3;
        }
    }

	std::array<uint8_t, 64> cubieIDMap;
	cubieIDMap[0b000101] = 0;
	cubieIDMap[0b101000] = 0;

	cubieIDMap[0b000001] = 1;
	cubieIDMap[0b001000] = 1;

	cubieIDMap[0b000010] = 2;
	cubieIDMap[0b010000] = 2;

	cubieIDMap[0b000100] = 3;
	cubieIDMap[0b100000] = 3;

	cubieIDMap[0b100101] = 4;
	cubieIDMap[0b101100] = 4;

	cubieIDMap[0b101001] = 5;
	cubieIDMap[0b001101] = 5;

	cubieIDMap[0b010100] = 6;
	cubieIDMap[0b100010] = 6;

	cubieIDMap[0b011101] = 7;
	cubieIDMap[0b101110] = 7;

	cubieIDMap[0b011100] = 8;
	cubieIDMap[0b100011] = 8;

	cubieIDMap[0b011010] = 9;
	cubieIDMap[0b010011] = 9;

	cubieIDMap[0b011001] = 10;
	cubieIDMap[0b001011] = 10;

	cubieIDMap[0b001010] = 11;
	cubieIDMap[0b010001] = 11;

	CubieInfo info;

	info.id = cubieIDMap[face1<<3 || face2];
	info.orientation = face1 > face2 ? 1 : 0;

	return info;
}

/*
0b000111000
//Front four edge cubes
if (idx < 4) {
    face1 = front;
    switch (idx) {
        case 0:
            face2 = bottom;
            break;
        case 1:
            face2 = left;
            break;
        case 2:
            face2 = top;
            break;
        case 3:
            face2 = right;
            break;
    }
//Two top and bottom cubies on right face
} else {
    face1 = right;
    if (idx == 4) {
        face2 = top;
    } else {
        face2 = bottom;
    }
}

switch (idx) {
    case 0:
    case 5: {
        face1 &=
    }
}
*/
