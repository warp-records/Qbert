
#include "edge_cubies.hpp"
#include <array>
#include <optional>
#include <algorithm>
#include <type_traits>

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
i
*/

//missing 001 010

//set for using 6 edge cubies
EdgeCubies::EdgeCubies() {
    //0x71C71C7
    front = WhiteFace | 0x71C71C7;
	top =   GreenFace | 0x71C71C7;
	left =  RedFace | 0x71C71C7;

	back =   YellowFace | 0x71C71C7;
	bottom = BlueFace | 0x71C71C7;
	right =  OrangeFace | 0x71C71C7;
}



/*
front:
000 111 000
111 000 111
000 111 000

top:
000 000 000
000 000 111
000 111 000

left:
000 000 000
000 000 111
000 000 000

right:
000 111 000
111 000 000
000 111 000

bottom:
000 111 000
000 000 111
000 000 000

*/

/*enum Color {
	White =  0b000,
	Green =  0b001,
	Red =   0b010,
	Yellow = 0b011,
	Blue = 	 0b100,
	Orange = 0b101
};*/

uint32_t EdgeCubies::getIdx() const {
    //static int callCount = 0;
    //callCount++;

    //only for debugging
    /*
    auto integrityCheck = [&]() -> bool {
        std::array<bool, 12> seenIds = { false };
        for (int idx = 0; idx < 12; ++idx) {
            CubieInfo info = getCubieInfo(idx);
            if (info.id < 0 || info.id >= 12) return false;
            seenIds[info.id] = true;
        }
        for (bool seen : seenIds) {
            if (!seen) return false;
        }

        return true;
    }; */

    //bool usedIds[8] { 0, 0, 0, 0, 0, 0, 0, 0 };
	//7!*3^5 ... 2!*3^1

	//HELPFHDSAFADSHNFSDK

	//Maybe try a simpler implementation
	//When "N"" is number of cubies in set
	//Num of permutations: 12!/(12-N)!
	//In this case, 12!/6!

	//factorialSet[i] = (11-i)!/(6)!
	uint32_t const factorialSet[7] {
		55440, 5040, 504, 56, 7, 1
	};
	//you're a dumbass if you can't figure this one out
	uint32_t const pow2[8] {
		1, 2, 4, 8, 16, 32, 64
	};



	//Index of all cubibes that HAVEN'T been visited
	//First order of business is fixing this shit

	//constexpr int NUM_CUBIES = 6;
	constexpr int PADDING = 12;
	//Only 12 are used, last 4 are for a genius optimization
	//discovered by yours truly
	//must store each number in a nibble due to 64 bit registers
	alignas(uint64_t) uint8_t indices[12] = {
		PADDING+0, PADDING+1, PADDING+2, PADDING+3,
		PADDING+4, PADDING+5, PADDING+6, PADDING+7,
		PADDING+8, PADDING+9, PADDING+10, PADDING+11,
	};
	/*
	alignas(uint64_t) uint8_t indices1[8] = {
    	PADDING+8, PADDING+9, PADDING+10, PADDING+11,
    	PADDING, PADDING, PADDING, PADDING
	};
	 */
	/*
	alignas(uint64_t) uint8_t indices1[8] = {
			PADDING+8, PADDING+9, PADDING+10, PADDING+11,
			PADDING, PADDING, PADDING, PADDING
		}; */

	//cubes edge sets index into the pattern database
	uint32_t pdbIdx = 0;
	//i is index of edge cubie in cube
	for (int i = 0; i < 6; i++) {
	    //returning 0 every time...

		//CAN'T skip an index since the first index is a corner
		//cubie, NOT an edge cubie
		CubieInfo info = getCubieInfo(i);

		//this better fucking work this time around because
		//if it doesn't I truly have no fucking clue what will
		pdbIdx += pow2[6-i]*factorialSet[i] * (indices[info.id]-PADDING);
		pdbIdx += pow2[6-i-1]*factorialSet[i] * (info.orientation);

		//assert(integrityCheck());
		//assert(pdbIdx <= 42577920);

		/*
		//I'm a genius for this
        uint64_t packed = *reinterpret_cast<uint64_t*>(indices0);
        uint64_t subtractConst = (0x0101010101010101ULL << (info.id*8));
        //weird UB fuckery
        subtractConst = i <= 7 ? subtractConst : 0;
        packed -= subtractConst;
        *reinterpret_cast<uint64_t*>(indices0) = packed;

    	packed = *reinterpret_cast<uint64_t*>(indices1);
    	subtractConst = (0x0000000001010101ULL << (std::max((int) info.id-8, 0))*8);
    	packed -= subtractConst;
    	*reinterpret_cast<uint64_t*>(indices1) = packed;
        */
		for (int j = info.id; j < 12; j++) {
		    indices[j]--;
		}
	}

	return pdbIdx;

}

EdgeCubies::CubieInfo EdgeCubies::getCubieInfo(int idx) const {

    //consider changing to uint8_t
    uint16_t face1;
    uint16_t face2;

    auto bottomTile = [](uint32_t face) -> uint32_t { return (face&(0b111<<3*1))>>3*1; };
    auto rightTile =  [](uint32_t face) -> uint32_t { return (face&(0b111<<3*3))>>3*3; };
    auto leftTile =   [](uint32_t face) -> uint32_t { return (face&(0b111<<3*5))>>3*5; };
    auto topTile =    [](uint32_t face) -> uint32_t { return (face&(0b111<<3*7))>>3*7; };
    //to understand this, visualize the code
    //if you're bad at visualizing things, good fucking luck understanding LOL

    /*
   Front face:
   | |2| |
   |1| |3|
   | |0| |

   Right face:
   | |4| |
   | | |5|
   | |6| |

   Left face:
   | |7| |
   |9| | |
   | |8| |

   Back face:
   | |10| |
   | |  | |
   | |11| |
    */




    //MUST implement for all cases!
    switch (idx) {
        case 0: {
            face1 = bottomTile(front);
            face2 = topTile(bottom);
            break;
        }

        case 1: {
            face1 = leftTile(front);
            face2 = rightTile(left);
            break;
        }

        case 2: {
            face1 = topTile(front);
            face2 = bottomTile(top);
            break;
        }

        case 3: {
            face1 = rightTile(front);
            face2 = leftTile(right);
            break;
        }

        case 4: {
            face1 = topTile(right);
            face2 = rightTile(top);
            break;
        }

        case 5: {
            face1 = rightTile(right);
            face2 = leftTile(back);
            break;
        }

        case 6: {
            face1 = bottomTile(right);
            face2 = rightTile(bottom);
            break;
        }

        case 7: {
            face1 = topTile(left);
            face2 = leftTile(top);
            break;
        }

        case 8: {
            face1 = bottomTile(left);
            face2 = leftTile(bottom);
            break;
        }

        case 9: {
            face1 = leftTile(left);
            face2 = rightTile(back);
            break;
        }

        case 10: {
            face1 = topTile(back);
            face2 = topTile(top);
            break;
        }

        case 11: {
            face1 = bottomTile(back);
            face2 = bottomTile(bottom);
            break;
        }

    	default: {
            throw std::exception();
        }
    }

    //Encountered a blanbk cubie
    assert(face1 <= 0b101 && face2 <= 0b101);

	std::array<uint8_t, 64> cubieIDMap;
	//orange white
	cubieIDMap[0b000101] = 0;
	cubieIDMap[0b101000] = 0;

	//green white
	cubieIDMap[0b000001] = 1;
	cubieIDMap[0b001000] = 1;

	//red white
	cubieIDMap[0b000010] = 2;
	cubieIDMap[0b010000] = 2;

	//blue white
	cubieIDMap[0b000100] = 3;
	cubieIDMap[0b100000] = 3;

	//blue orange
	cubieIDMap[0b100101] = 4;
	cubieIDMap[0b101100] = 4;

	//orange green
	cubieIDMap[0b101001] = 5;
	cubieIDMap[0b001101] = 5;

	cubieIDMap[0b010100] = 6;
	cubieIDMap[0b100010] = 6;

	cubieIDMap[0b011101] = 7;
	cubieIDMap[0b101011] = 7;

	cubieIDMap[0b011100] = 8;
	cubieIDMap[0b100011] = 8;

	cubieIDMap[0b011010] = 9;
	cubieIDMap[0b010011] = 9;

	cubieIDMap[0b011001] = 10;
	cubieIDMap[0b001011] = 10;

	cubieIDMap[0b001010] = 11;
	cubieIDMap[0b010001] = 11;

	CubieInfo info;

	info.id = cubieIDMap[face1<<3 | face2];
	assert(0 <= info.id && info.id <= 11);
	info.orientation = face1 > face2 ? 1 : 0;

	return info;
}

// Implement EdgeCubies::getNeighbors
std::array<EdgeCubies, 27> EdgeCubies::getNeighbors() const {
    std::array<Cube, 27> neighborCubes = Cube::getNeighbors();
    std::array<EdgeCubies, 27> edgeCubiesNeighbors;

    for (int i = 0; i < neighborCubes.size(); i++) {
        edgeCubiesNeighbors[i] = EdgeCubies(neighborCubes[i]);
    }

    return edgeCubiesNeighbors;
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
