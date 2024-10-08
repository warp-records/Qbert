
#include "alg.hpp"
#include <ostream>
#include "cube.hpp"
#include "mini_cube.hpp"
#include "edge_cubies.hpp"
#include <stack>
#include <vector>
#include <functional>
#include <utility>
#include <array>
#include <array>

std::pair<std::vector<Cube>, uint64_t> idaStar(Cube start) {

	struct Node {
		Cube cube;
		int depth;
		Node* prev;
	};

	std::cout << "Generating pattern databases:" << std::endl;
	PDB firstEdgeCubieDB(EdgeCubies(), 42577920);
	PDB secondEdgeCubieDB(EdgeCubies(true), 42577920);
	PDB cornerCubieDB(MiniCube(), 3674160);

	std::cout << "Solving cube:" << std::endl;

	auto heuristic = [&cornerCubieDB, &firstEdgeCubieDB, &secondEdgeCubieDB](Cube const& cube) {
	    //return 0;
		MiniCube cornerCubies(cube);
		EdgeCubies edgeCubies(cube);
		uint32_t edgesIdx = edgeCubies.getIdx();
		return std::max({cornerCubieDB.getDist(cornerCubies.getIdx()),
		                firstEdgeCubieDB.getDist(edgesIdx),
		                secondEdgeCubieDB.getDist(edgesIdx)  });

	};

	constexpr int SKYDADDYS_NUMBER = 20;

    uint64_t nodesGenerated = 0;

	for (int depthLim = heuristic(start); depthLim <= SKYDADDYS_NUMBER; depthLim++) {

		std::cout << "Depth " << depthLim << std::endl;

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
            //Reduce branching factor
			for (Cube const& neighbor : node.cube.getNeighbors()) {
				//assert(node.depth+1 + heuristic(neighbor) <= SKYDADDYS_NUMBER);
                nodesGenerated++;

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
			return std::make_pair(result, nodesGenerated);
		}
	}

	//throw std::exception();
}

template<typename T> std::ostream& operator<<(std::ostream os, PDB<T> const& pdb) {
    uint64_t len = pdb.data.size();
    os << len;
    for (uint8_t byte : pdb.data) {
        os << byte;
    }
}
