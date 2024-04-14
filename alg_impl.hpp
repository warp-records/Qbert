#pragma once

#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

//class PDB;

template<typename T> static std::vector<uint8_t> PDB<T>::genPdb(T start, int const permuts) {

	struct Node {
		T elem;
		uint8_t depth;
	};

    std::queue<Node> q;

	//this single line is literally the entirety of korf's fabled pdb lmao
	std::vector<uint8_t> pdb(permuts/2);

	q.push(Node{start, 0});

	while (!q.empty()) {

		Node current = q.front();
		q.pop();

		for (T neighbor : current.elem.getNeighbors()) {
			uint32_t idx = neighbor.getIdx();

			if (!(pdb[idx/2] & ((idx%2) ? 0xf0 : 0x0f))) {
				q.push(Node{neighbor, static_cast<uint8_t>(current.depth + 1)});

				pdb[idx/2] |= (static_cast<uint8_t>(current.depth+1) << ((idx%2) ? 4 : 0));
			}
		}
	}

	pdb[start.getIdx()/2] &= ~((0b1111 << (start.getIdx()%2 ? 4 : 0)));

	return pdb;
}

template<typename T> int PDB<T>::getDist(int idx) const { 
	return (data[idx/2] >> ((idx%2) ? 4 : 0))&0b1111; 
}