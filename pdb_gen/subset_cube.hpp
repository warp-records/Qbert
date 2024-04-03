
#pragma once

#include "../cube.hpp"
#include <cstdint>
#include <iostream>
#include <cassert>
#include <unordered_set>
#include <algorithm>

namespace MiniMask {
	namespace Column {
		uint16_t constexpr Left =  0xE38;
		uint16_t constexpr Right = 0x1C7;
	};

	namespace Row {
		uint16_t constexpr Top = 	0xFC0;
		uint16_t constexpr Bottom = 0x03F;
	}; 

};

struct MiniCube {

	enum SolvedFace {
		WhiteFace =  0x000,
		GreenFace =  0x249,
		BlueFace =   0x492,
		OrangeFace = 0x6DB,
		RedFace = 	 0x924,
		YellowFace = 0xB6D
	};


uint16_t top, bottom,
		 front, back,
		 left, right;

 	MiniCube();
	MiniCube(uint16_t top, uint16_t bottom,
		uint16_t front, uint16_t back,
		uint16_t left, uint16_t right);

	//Normalized so top left front cube is never moved
	MiniCube rotHoriz(Row line, Direction dir) const;
	MiniCube rotVert(Column line, Direction dir) const;

	//Left side view for rotations around the x axis
	MiniCube changePerspective(Perspective per) const {
		MiniCube qb = *this;

		switch (per) {

		case (Perspective::Left) : {
			qb.front = left;
			qb.right = front;
			qb.back = right;
			qb.left = back;
			break;
		}

		case (Perspective::Right) : {
			qb.front = right;
			qb.left = front;
			qb.back = left;
			qb.right = back;
			break;
		}

		}

		return qb;
	}

	MiniCube& operator=(const MiniCube& other) = default;

	std::array<MiniCube, 18> getNeighbors() const;

	//Unique integer generated from cube used as an index into the PDB
	//yields the same value for different orientations of the same cube

	//For some reason this works even though some IDs are used
	//multiple times
	uint32_t getIdx() const {
		bool usedIds[8] { 0, 0, 0, 0, 0, 0, 0, 0 };
		//7!*3^5 ... 2!*3^1

		//HELPFHDSAFADSHNFSDK

		//Maybe try a simpler implementation
		uint32_t const factorial[8] {
			0, 1, 2, 6, 24, 120, 720, 5040
		};

		uint32_t const powerOf3[7] {
			1, 3, 9, 27, 81, 243, 2187
		};

		//Index of all cubibes that HAVEN'T been visited
		uint8_t index[8] {
			0, 1, 2, 3, 4, 5, 6, 7
		};

		uint64_t idx = 0;

		//Last cube is already known given cube numbers 1-6

		//PLEASE PLEASE PLEASE FUCKINGGG WORK
		for (int i = 6; i > 0; i--) {
			//For this to work, each Cubie ID must max out to the number left
			auto info = getCubieInfo(i&0b001, (i&0b010)>>1, (i&0b100)>>2);

			//assert(usedIds[info.id] == false);
			/*
			if (usedIds[info.id]) {
				std::cerr << "Repeat ID: " << std::bitset<8>(info.id) << std::endl;
				assert(false);
			}
			usedIds[info.id] = true;*/

			idx += factorial[i]*index[info.id]*powerOf3[i-1] +
					factorial[i-1]*powerOf3[i-2]*info.orientation;

			for (int j = 0; j < 8; j++) {
				index[j] = index[j] > index[info.id] ? index[j]-1 : index[j];
				//assert(index[j]-i <= 1);
			}


			/*
			for (int j = 0; j < 8; j++) {
				indices[j] = indices[j] > i ? indices[j]-1 : indices[j];
				assert(indices[j] <= i);
			}*/

			//assert(usedIds[getCubieID(i & 0b001, i & 0b010, i & 0b100)] == false);
			//usedIds[getCubieID(i & 0b001, i & 0b010, i & 0b100)] = true;
		}

		return idx;
	}


			//auto info = getCubieInfo((i+1)&0b001, ((i+1)&0b010)>>1, ((i+1)&0b100)>>2);

			//idx += factorials[i]*powersOf3[i+1]*indices[info.id] + powersOf3[i]*info.orientation;

	//Only public for debugging
	struct CubieInfo {
		uint8_t id;
		uint8_t orientation;
	};
	CubieInfo getCubieInfo(bool x, bool y, bool z) const;


private:

	//If this becomes a bottleneck, it could possibly
	//be sped up with a permute instruction
	static uint16_t rotFaceLeft(uint16_t face);
	static uint16_t rotFaceRight(uint16_t face);
	static uint16_t rotFace180(uint16_t face);

	//Get the unique identifier for each cube:
	//the colors of each face from that XOR'd together
	//uint8_t getCubieID(bool x, bool y, bool z) const;

};

std::ostream& operator<<(std::ostream& os, const MiniCube& cube);

//For debbuging
bool operator==(MiniCube const& lhs, MiniCube const& rhs);
bool operator!=(MiniCube const& lhs, MiniCube const& rhs);

