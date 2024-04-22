
#include "edge_cubies.hpp"
#include <array>

EdgeCubies rotHoriz(Row line) const {
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


EdgeCubies rotXAxis(CrossSection line) const {
	EdgeCubies newCube(*this);

	uint32_t ySwapMask = line==CrossSection::Front ? 0x7 : 0x7<<6;
			 ySwapMask = line==CrossSection::Middle ? 0x7<<3 : ySwapMask;

	newCube.top &= ySwapMask;
	newCube.top |= bottom&ySwapMask;

	newCube.bottom &= ySwapMask;
	newCube.bottom |= top&ySwapMask;



	uint32_t xBottomTileMask = line==CrossSection::Front ? 0b111 : 0b111<<6;
			 xBottomTileMask = line==CrossSection::Middle ? 0b111<<3 : xTileMask;

	uint32_t xTopTileMask = xTileMask<<9;

	newCube.left &= ~(xTopTileMask | xBottomTileMask);
	newCube.left |= (right&xBottomTileMask)<<9;
	newCube.left |= (right&xTopTileMask)>>9;

	newCube.right &= ~(xTopTileMask | xBottomTileMask);
	newCube.left |= (left&xBottomTileMask)<<9;
	newCube.left |= (left&xTopTileMask)>>9;


	return newCube;
}

std::array<EdgeCubies, 5> getNeighbors() const {
	return std::array<EdgeCubies, 5> {{
		rotHoriz(Row::Top), 
		rotHoriz(Row::Bottom),
		rotXaxis(CrossSection::Front), 
		rotXaxis(CrossSection::Middle),
		rotXaxis(CrossSection::Back),
	}};
}

EdgeCubies() {
	front = 0x00;
	top = 0xE07;
	left = 0x12492;

	back = 0x1B;
	bottom = 0x124;
	right = 0x2DB6D;
}
