
#pragma once

#include "cube.hpp"
#include <ostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>

template<typename T> class PDB {
//only public for debugging
public:
	std::vector<uint8_t> const data;

	static std::vector<uint8_t> genPdb(T start, uint64_t const permuts);

	PDB(std::vector<uint8_t> data) : data{data} {};

	friend std::ostream& operator<<(std::ofstream os, PDB<T> const& pdb);

//public:
	PDB(T start, uint64_t const permuts) : data{genPdb(start, permuts)} {};
	//good enough lol
	PDB(std::string filename);
	uint8_t getDist(uint64_t idx) const;

};

std::pair<std::vector<Cube>, uint64_t> idaStar(Cube start);
std::vector<uint8_t> deserializePdb(std::string filename);
void serializePdb(std::vector<uint8_t> const&, std::string filename);
//template<typename T> std::ostream& operator<<(std::ofstream os, PDB<T> const& pdb);

#include "alg_impl.hpp"
