
#pragma once

#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

template<class T> struct Node {
	T elem;
	uint8_t depth;
};

//std::unordered_set();

//(0b1111 << ((idx%2) ? 4 : 0))

template<typename T> std::vector<uint8_t> pdbGen(T start, int const permuts) {

    std::queue<Node<T>> q;

	//this single line is literally the entirety of korf's fabled pdb lmao
	std::vector<uint8_t> pdb(permuts/2);

	q.push(Node<T>{start, 0});

	while (!q.empty()) {

		Node current = q.front();
		q.pop();

		for (T neighbor : current.elem.getNeighbors()) {
			uint32_t idx = neighbor.getIdx();

			if (!(pdb[idx/2] & ((idx%2) ? 0xf0 : 0x0f))) {
				q.push(Node<T>{neighbor, static_cast<uint8_t>(current.depth + 1)});

				pdb[idx/2] |= (static_cast<uint8_t>(current.depth+1) << ((idx%2) ? 4 : 0));
			}
		}
	}

	pdb[start.getIdx()/2] &= ~((start.getIdx()%2) ? 0xf0 : 0x0f);
	
	return pdb;
}