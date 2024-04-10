
#include "alg.hpp"
#include "cube.hpp"
#include "pdb_gen/subset_cube.hpp"
#include <stack>
#include <vector>
#include <functional>

std::vector<Cube> idaStar(Cube start) {

	struct Node {
		Cube cube;
		int depth;
		Node* prev;
	};


	PDB cornerCubieDB(MiniCube(), 3674160);

	auto heuristic = [&cornerCubieDB](Cube const& cube) {
		MiniCube cornerCubies(cube);
		return cornerCubieDB.getDist(cornerCubies.getIdx());
	};

	constexpr int SKYDADDYS_NUMBER = 20;

	for (int depthLim = heuristic(start); depthLim <= SKYDADDYS_NUMBER; depthLim++) {

		std::function<std::vector<Cube>(Node)> idaStarInner;
		idaStarInner = [&depthLim, &idaStarInner, &heuristic](Node node) -> std::vector<Cube> {
			
			if (node.cube.isSolved()) {
				//std::cout << "Solution found!" << std::endl;

				std::vector<Cube> sol;
				Node* curr = &node;

				while (curr->prev != nullptr) {

					sol.insert(sol.begin(), curr->cube);
					curr = curr->prev;
				}

				sol.insert(sol.begin(), curr->cube);

				return sol;
			}

			for (Cube const& neighbor : node.cube.getNeighbors()) {
				if (node.depth+1 + heuristic(neighbor) <= depthLim) {
					auto result = idaStarInner(Node{neighbor, node.depth+1, &node});

					if (!result.empty())
						return result;
				}
			}

			return std::vector<Cube>();
		};


		std::vector<Cube> result = idaStarInner(Node{start, 0, nullptr});

		if (!result.empty()) {
			return result;
		}
	}

	throw std::exception();
}

