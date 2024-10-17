#pragma once

#include <iterator>
#include <cassert>
#include <iterator>
#include <queue>
#include <type_traits>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

//class PDB;

template<typename T> std::vector<uint8_t> PDB<T>::genPdb(T start, uint64_t const permuts) {

    struct Node {
		T elem;
		uint8_t depth;
	};

    std::queue<Node> q;

	//this single line is literally the entirety of korf's fabled pdb lmao
	std::vector<uint8_t> pdb(permuts/2);

	q.push(Node{start, 0});
	uint64_t nodeCount = 0;
	int percentDone = 0;
	//int iterCount = 0;
	//std::array<uint32_t, 27> invalidRots;

	while (!q.empty()) {

		Node current = q.front();
		q.pop();

		for (T neighbor : current.elem.getNeighbors()) {
		    uint64_t idx = neighbor.getIdx();

			if (!(pdb[idx/2] & ((idx%2) ? 0xf0 : 0x0f))) {
				q.push(Node{neighbor, static_cast<uint8_t>(current.depth + 1)});
				nodeCount++;

				if (nodeCount % 47900160 == 0) {
				    percentDone++;
				    std::cout << percentDone << "%" << std::endl;
				}

				pdb[idx/2] |= (static_cast<uint8_t>(current.depth+1) << ((idx%2) ? 4 : 0));
			}
		}

		//iterCount++;
	}


	std::cout << "Node count: " << nodeCount << std::endl;

	pdb[start.getIdx()/2] &= ~((0b1111 << (start.getIdx()%2 ? 4 : 0)));

	return pdb;
}

template<typename T> uint8_t PDB<T>::getDist(uint64_t idx) const {
	return (data[idx/2] >> ((idx%2) ? 4 : 0))&0b1111;
}
