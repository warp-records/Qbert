
#pragma once
#include "cube.hpp"
#include <ostream>
#include <fstream>
#include <vector>
#include <utility>

template<typename T> class PDB {
//only public for debugging
public:
	std::vector<uint8_t> const data;

	static std::vector<uint8_t> genPdb(T start, int const permuts);
	static PDB<T> deserialize(std::string filename);
	void serialize(std::string filename);

	friend std::ostream& operator<<(std::ofstream os, PDB<T> const& pdb);

//public:
	PDB(T start, int const permuts) : data{genPdb(start, permuts)} {};
	int getDist(int idx) const;

};

std::pair<std::vector<Cube>, uint64_t> idaStar(Cube start);

//template<typename T> std::ostream& operator<<(std::ofstream os, PDB<T> const& pdb);

#include "alg_impl.hpp"
