
#include "edge_cubies.hpp"
#include <array>

//NOT DEBUGGED
EdgeCubies EdgeCubies::rotHoriz(Row line) const {
	EdgeCubies newCube(*this);

	uint32_t xSwapMask = line==Row::Top ? 0b111<<9 : 0b111;
	uint32_t zSwapMask = line==Row::Top ? 0b111<<3 : 0b111;

	//operator << has lowest precedence
	newCube.left &= xSwapMask;
	newCube.left |= (right&xSwapMask)<<6 | (right&xSwapMask)<<3 | (right&xSwapMask<<6)>>6;
	
	newCube.right &= xSwapMask;
	newCube.right |= (left&xSwapMask)<<6 | (left&xSwapMask<<3) | (left&xSwapMask<<6)>>6;

	newCube.front &= ~zSwapMask;
	newCube.front |= back&zSwapMask;

	newCube.back &= ~zSwapMask;
	newCube.back |= front&zSwapMask;

	if (line == Row::Top) {
		newCube.top = (top&0b111)<<6 | (top&0b111<<3) | (top&0b111<<6)>>6;
	} else {
		newCube.bottom = (bottom&0b111)<<6 | (bottom&0b111<<3) | (bottom&0b111<<6)>>6;
	}

	return newCube;
}


EdgeCubies EdgeCubies::rotXAxis(CrossSection line) const {
	EdgeCubies newCube(*this);

	uint32_t ySwapMask = line==CrossSection::Front ? 0x7 : 0x7<<6;
			 ySwapMask = line==CrossSection::Middle ? 0x7<<3 : ySwapMask;

	newCube.top &= ySwapMask;
	newCube.top |= bottom&ySwapMask;

	newCube.bottom &= ySwapMask;
	newCube.bottom |= top&ySwapMask;



	uint32_t xBottomTileMask = line==CrossSection::Front ? 0b111 : 0b111<<6;
			 xBottomTileMask = line==CrossSection::Middle ? 0b111<<3 : xBottomTileMask;

	uint32_t xTopTileMask = xBottomTileMask<<9;

	newCube.left &= ~(xTopTileMask | xBottomTileMask);
	newCube.left |= (right&xBottomTileMask)<<9;
	newCube.left |= (right&xTopTileMask)>>9;

	newCube.right &= ~(xTopTileMask | xBottomTileMask);
	newCube.left |= (left&xBottomTileMask)<<9;
	newCube.left |= (left&xTopTileMask)>>9;


	return newCube;
}

std::array<EdgeCubies, 5> EdgeCubies::getNeighbors() const {
	return std::array<EdgeCubies, 5> {{
		rotHoriz(Row::Top), 
		rotHoriz(Row::Bottom),
		rotXAxis(CrossSection::Front), 
		rotXAxis(CrossSection::Middle),
		rotXAxis(CrossSection::Back),
	}};
}

EdgeCubies::EdgeCubies() {
	front = 0x00;
	top = 0xE07;
	left = 0x12492;

	back = 0x1B;
	bottom = 0x124;
	right = 0x2DB6D;
}

/*
000 101 = White Orange
000 001 = White Green
000 010 = White Red
000 100 = White Blue
100 101 = Blue Orange
101 001 = Orange Green
001 010 = Green Red
010 100 = Red Blue
011 101 = Yellow Orange
011 100 = Yelow Blue
011 010 = Yellow Red

011 001 = Yellow Green

*/

//missing 001 010

uint32_t EdgeCubies::getIdx() const {

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

		//bool usedIds[8] { 0, 0, 0, 0, 0, 0, 0, 0 };
	//7!*3^5 ... 2!*3^1

	//HELPFHDSAFADSHNFSDK

	//Maybe try a simpler implementation
	//(x+6)!/6!
	uint32_t const factorialSet[7] {
		1, 7, 56, 504, 5040, 55440, 665280
	};


	//Index of all cubibes that HAVEN'T been visited
	//First order of business is fixing this shit

	constexpr int PADDING = 6;
	alignas(uint64_t) uint8_t indices[8] = {
		0, 0, 0, 0, 0, 0, 0, 0
	};

	uint32_t idx = 0;

	//PLEASE PLEASE PLEASE FUCKINGGG WORK
	//12!/6!*2^6
	for (int i = 6; i > 0; i--) {
		//For this to work, each Cubie ID must max out to the number left
		auto info = getCubieInfo(i-1);

		idx += factorialSet[i-1]*indices[info.id]+factorialSet[i]*info.orientation;

		//I'm a genius for this
		uint64_t packed = *reinterpret_cast<uint64_t*>(indices);
		uint64_t subtractConst = (0x010101010101ULL << (info.id*8));
		packed -= subtractConst;
		*reinterpret_cast<uint64_t*>(indices) = packed;
		/*
		for (int j = info.id; j < 8; j++) {
			indices[j]--;
		}*/
	}

	return idx;

}



