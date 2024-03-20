
#pragma once

#include "alg.hpp"
#include <queue>
#include <vector>


template<typename T> std::vector<uint8_t> pdbGen(T start, int const permuts) {
	std::queue<Node<T>> q;
	//this single line is literally all korf's fabled pdb is
	std::vector<uint8_t> pdb(permuts);

	q.push(Node{start, 0});
	//pdb[start.elem.getIdx()] = tue;

	while (!q.empty()) {
		Node current = q.back();
		q.pop();

		for (T neighbor : node.elem.getNeighbors()) {
			uint32_t idx = neighbor.getIdx();

			if (!pdb[idx]) {
				q.push(Node{neighbor, current.depth+1});
				pdb[idx] = current.depth+1;
			}
		}
	}

	return pdb;
}