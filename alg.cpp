
#include "alg.hpp"
#include "cube.hpp"
#include "pdb_gen/subset_cube.hpp"
#include <stack>

std::vector<Cube> idaStar(Cube start) {

	PDB cornerCubieDB(MiniCube(), 3674160);

	struct Node {
		Cube cube;
		int depth;
		Node* prev;
	};

	auto heuristic = [](Cube const& cube) {
		return rand()%21;
	};

	constexpr int SKYDADDYS_NUMBER = 20;

	for (int depthLim = heuristic(start); depthLim <= SKYDADDYS_NUMBER; depthLim++) {
		std::stack<Node> s;
		s.push(Node{start, 0, nullptr});

		while (!s.empty()) {
			Node node = s.top();
			s.pop();


			if (node.cube.isSolved()) {
				std::vector<Cube> sol;
				Node* curr = &node;

				while (curr->depth > 0) {
					sol.insert(sol.begin(), curr->cube);
					curr = curr->prev;
				}

				sol.insert(sol.begin(), curr->cube);

				return sol;
			}

			for (Cube const& neighbor : node.cube.getNeighbors()) {
				if (node.depth+1 + heuristic(neighbor) <= depthLim)
					s.push(Node{neighbor, node.depth+1, &node});
			}
		}
	}

	throw std::exception();
}

