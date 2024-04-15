
#pragma once
#include "cube.hpp"
#include <vector>
#include <utility>

template<typename T> class PDB {
	std::vector<uint8_t> const data;

	static std::vector<uint8_t> genPdb(T start, int const permuts);

public:
	PDB(T start, int const permuts) : data{genPdb(start, permuts)} {};
	int getDist(int idx) const;
};


std::pair<std::vector<Cube>, uint64_t> idaStar(Cube start);

#include "alg_impl.hpp"
