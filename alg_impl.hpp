
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

template<typename T> std::vector<uint8_t> pdbGen(T start, int const permuts) {
	
	std::queue<Node<T>> q;
	//this single line is literally the entirety of korf's fabled pdb
	std::vector<uint8_t> pdb(permuts);

	q.push(Node<T>{start, 0});

	int maxDepth = 0;

	while (!q.empty()) {

		Node current = q.front();
		q.pop();

		for (T neighbor : current.elem.getNeighbors()) {
			uint32_t idx = neighbor.getIdx();

			if (!pdb[idx]) {
				q.push(Node<T>{neighbor, static_cast<uint8_t>(current.depth + 1)});
				pdb[idx] = static_cast<uint8_t>(current.depth+1);
			}
		}
	}

	pdb[start.getIdx()] = 0;
	
	return pdb;
}