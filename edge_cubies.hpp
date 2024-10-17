#pragma once

#include "cube.hpp"
#include <cstdint>
#include <iostream>
#include <cassert>
#include <unordered_set>
#include <algorithm>
#include <array>

//Set of 6
struct EdgeCubies : public Cube {
    static constexpr int NUM_CUBIES = 12;

    struct CubieInfo {
		uint8_t id;
		uint8_t orientation;
	};

	uint64_t getIdx() const;
    EdgeCubies::CubieInfo getCubieInfo(int idx) const;

    std::array<EdgeCubies, 27> getNeighbors() const;

    EdgeCubies(bool ss = false, bool noOrnt = true);

    EdgeCubies(uint32_t top, uint32_t bottom,
		uint32_t front, uint32_t back,
		uint32_t left, uint32_t right);

    EdgeCubies(const Cube& largeCube, bool ss = false) : Cube(largeCube), secondSet(ss) {};

    bool secondSet;
    bool noOrient;

    operator Cube() const { return Cube(top, bottom, front, back, left, right); }
};
