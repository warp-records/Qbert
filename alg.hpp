
#pragma once
#include "cube.hpp"
#include <vector>

template<typename T> class PDB {
	std::vector<uint8_t> const data;

	static std::vector<uint8_t> genPdb(T start, int const permuts);

public:
	PDB(T start, int const permuts) : data{genPdb(start, permuts)} {};
	int getDist(int idx) const;
};


std::vector<Cube> idaStar(Cube start);

#include "alg_impl.hpp"