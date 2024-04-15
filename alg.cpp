
#include "alg.hpp"
#include "cube.hpp"
#include "subset_cube.hpp"
#include <stack>
#include <vector>
#include <functional>
#include <utility>

std::pair<std::vector<Cube>, uint64_t> idaStar(Cube start) {

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
    
    uint64_t nodesGenerated = 0;

	for (int depthLim = heuristic(start); depthLim <= SKYDADDYS_NUMBER; depthLim++) {

		std::function<std::vector<Cube>(Node)> idaStarInner;
		idaStarInner = [&depthLim, &idaStarInner, &heuristic, &nodesGenerated](Node node) -> std::vector<Cube> {

			
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
				//assert(node.depth+1 + heuristic(neighbor) <= SKYDADDYS_NUMBER);

				if (node.depth+1 + heuristic(neighbor) <= depthLim) {
				 	nodesGenerated++;

					auto result = idaStarInner(Node{neighbor, node.depth+1, &node});

					if (!result.empty())
						return result;
				}
			}

			return std::vector<Cube>();
		};


		std::vector<Cube> result = idaStarInner(Node{start, 0, nullptr});

		if (!result.empty()) {
			return std::make_pair(result, nodesGenerated);
		}
	}

	throw std::exception();
}

