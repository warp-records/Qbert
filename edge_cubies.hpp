#pragma once


#include <array>
#include <optional>
#include <algorithm>
#include <type_traits>
#include "cube.hpp"
#include <cstdint>
#include <iostream>
#include <cassert>
#include <unordered_set>
#include <algorithm>
#include <array>

template<int NUM_CUBIES> struct EdgeCubies : public Cube {
    //static constexpr int NUM_CUBIES = 12;
    bool secondSet;
    bool noOrient;

    struct CubieInfo {
		uint8_t id;
		uint8_t orientation;
	};

	uint64_t getIdx() const;
    typename EdgeCubies<NUM_CUBIES>::CubieInfo getCubieInfo(int idx) const;

    std::array<EdgeCubies<NUM_CUBIES>, 27> getNeighbors() const;

    EdgeCubies<NUM_CUBIES>(bool ss = false, bool noOrnt = false);// : secondSet(ss), noOrient(noOrnt) {};

    //constexpr static std::array<uint8_t, 64> createCubieIDMap();

    EdgeCubies<NUM_CUBIES>(uint32_t top, uint32_t bottom,
		uint32_t front, uint32_t back,
		uint32_t left, uint32_t right);

    EdgeCubies(const Cube& largeCube, bool ss = false, bool noOrnt = false) : Cube(largeCube), secondSet(ss), noOrient(noOrnt) {};

    operator Cube() const { return Cube(top, bottom, front, back, left, right); }
};



template<int NUM_CUBIES> EdgeCubies<NUM_CUBIES>::EdgeCubies(bool ss, bool noOrnt) {
    secondSet = ss;
    noOrient = noOrnt;
    
    front = WhiteFace | 0x71C71C7;
    top =   GreenFace | 0x71C71C7;
    left =  RedFace | 0x71C71C7;

    back =   YellowFace | 0x71C71C7;
    bottom = BlueFace | 0x71C71C7;
    right =  OrangeFace | 0x71C71C7;
}

constexpr std::array<uint32_t, 12> genFactorialSet(const int numCubies) {

    std::array<uint32_t, 12> factorial {{
        1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800
    }};

    std::array<uint32_t, 12> factorialSet{{}};
    for (int i = 0; i < numCubies; i++) {
        factorialSet[i] = factorial[11-i]/factorial[12-numCubies];
    }

    return factorialSet;
}

template<int NUM_CUBIES> uint64_t EdgeCubies<NUM_CUBIES>::getIdx() const {

    //factorialSet[i] = (11-i)!/(NUM_CUBIES)!
    constexpr auto factorialSet = genFactorialSet(NUM_CUBIES);

    //you're a dumbass if you can't figure this one out
    std::array<uint32_t, 12> const pow2 {{
        1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048
    }};

    //Index of all cubibes that HAVEN'T been visited
    //First order of business is fixing this shit
    constexpr int PADDING = 12;

    //store array indices in uint64_ts so we can
    //use the bitshift and subtract hack here
    //holds PADDING+0, PADDING+1, ... PADDING+11, PADDING...
    uint64_t indices0 = 0x131211100f0e0d0c;
    uint64_t indices1 = 0x0c0c0c0c17161514;

    //cubes edge sets index into the pattern database
    uint64_t pdbIdx = 0;
    //i is index of edge cubie in cube
    for (int i = 0; i < NUM_CUBIES; i++) {
        int nc = NUM_CUBIES;
        //returning 0 every time...

        //CAN'T skip an index since the first index is a corner
        //cubie, NOT an edge cubie

        CubieInfo info = getCubieInfo(secondSet ? i+(12-NUM_CUBIES) : i);

        //this better fucking work this time around because
        //if it doesn't I truly have no fucking clue what will

        //Must specify the size to be used while shifting
        uint64_t constexpr FULL_BYTE = 0xff;

        uint64_t offset = (info.id <= 7 ? (indices0 & FULL_BYTE<<info.id*8)>>info.id*8 :
                            (indices1 & FULL_BYTE<<(info.id-8)*8)>>(info.id-8)*8) - PADDING;

        uint64_t orientFactor = noOrient ? 1 : pow2[NUM_CUBIES-i];
        pdbIdx += factorialSet[i] * offset * orientFactor;
        pdbIdx += noOrient ? 0 : (pow2[NUM_CUBIES-i-1]*factorialSet[i] * (info.orientation));

        //For some reason when you bitshift 64 or more it uses
        //the original value
        uint64_t subtractConst = (0x0101010101010101ULL << info.id*8);
        subtractConst = info.id <= 7 ? subtractConst : 0;
        indices0 -= subtractConst;

        subtractConst = (0x0101010101010101ULL << std::max((info.id-8), 0)*8);
        subtractConst = info.id-8 <= 7 ? subtractConst : 0;
        indices1 -= subtractConst;

        //for (int j = info.id; j < 12; j++) {
        //    indices[j]--;
        //}
    }

    return pdbIdx;

}

constexpr std::array<uint8_t, 64> createCubieIDMap() {
    std::array<uint8_t, 64> cubieIDMap = {};
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

    return cubieIDMap;
}




template<int NUM_CUBIES> typename EdgeCubies<NUM_CUBIES>::CubieInfo EdgeCubies<NUM_CUBIES>::getCubieInfo(int idx) const {

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

    }

    constexpr auto cubieIDMap = createCubieIDMap();

    CubieInfo info;

    info.id = cubieIDMap[face1<<3 | face2];
    info.orientation = face1 > face2 ? 1 : 0;

    return info;
}

// Implement EdgeCubies::getNeighbors
template<int NUM_CUBIES> std::array<EdgeCubies<NUM_CUBIES>, 27> EdgeCubies<NUM_CUBIES>::getNeighbors() const {
    std::array<Cube, 27> neighborCubes = Cube::getNeighbors();
    std::array<EdgeCubies<NUM_CUBIES>, 27> edgeCubiesNeighbors;

    for (int i = 0; i < neighborCubes.size(); i++) {
        edgeCubiesNeighbors[i] = EdgeCubies(neighborCubes[i], secondSet, noOrient);
    }

    return edgeCubiesNeighbors;
}
