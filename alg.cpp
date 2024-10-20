
#include "alg.hpp"
#include "alg_impl.hpp"
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
#include <filesystem>

std::pair<std::vector<Cube>, uint64_t> idaStar(Cube start) {

	struct Node {
		Cube cube;
		int depth;
		Node* prev;
	};

	//PDB<EdgeCubies> firstEdgeCubieDB(deserializePdb("pdb/7_edge_cubies_first.pdb"));
	PDB<EdgeCubies<12>> edgeCubie12DB(deserializePdb("../pdb/edge_cubies_no_orient.pdb"));
	//PDB<EdgeCubies> secondEdgeCubieDB(deserializePdb("pdb/edge_cubies_second.pdb"));
	PDB<EdgeCubies<7>> firstEdgeCubieDB(deserializePdb("../pdb/7_edge_cubies_first.pdb"));
	//PDB<EdgeCubies<6>> secondEdgeCubieDB(deserializePdb("../pdb/edge_cubies_second.pdb"));
	PDB<MiniCube> cornerCubieDB(deserializePdb("../pdb/corner_cubies.pdb"));

	std::cout << "Solving cube:" << std::endl;

	auto heuristic = [&](Cube const& cube) {
		MiniCube cornerCubies(cube);
		EdgeCubies edgeCubies12 = EdgeCubies<12>(cube, false, true);
		EdgeCubies firstEdgeSet = EdgeCubies<7>(cube);
		//EdgeCubies secondEdgeSet = EdgeCubies<6>(cube, true, false);

		return std::max({
		    cornerCubieDB.getDist(cornerCubies.getIdx()),
			edgeCubie12DB.getDist(edgeCubies12.getIdx()),
			firstEdgeCubieDB.getDist(firstEdgeSet.getIdx()),
		    //secondEdgeCubieDB.getDist(secondEdgeSet.getIdx()),
		});
	};

	constexpr int SKYDADDYS_NUMBER = 20;

    uint64_t nodesGenerated = 0;

	for (int depthLim = heuristic(start); depthLim <= SKYDADDYS_NUMBER; depthLim++) {

		std::cout << "Depth " << depthLim << std::endl;

		std::function<std::vector<Cube>(Node)> idaStarInner;
		idaStarInner = [&depthLim, &idaStarInner, &heuristic, &nodesGenerated](Node node) -> std::vector<Cube> {

			if (node.cube.isSolved()) {

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

}

//AI generated lol
std::vector<uint8_t> deserializePdb(std::string filename) {
    std::ifstream is(filename, std::ios::binary);
    if (!is.good()) { throw std::runtime_error("Cannot open file for reading"); }

    //No longer used anymore
    uint32_t oldSizeHeader;
    is.read(reinterpret_cast<char*>(&oldSizeHeader), sizeof(oldSizeHeader));
    if (!is.good()) { throw std::runtime_error("Error reading size"); }

    std::filesystem::path file(filename);
    uint64_t size = std::filesystem::file_size(file) - 4;
    std::vector<uint8_t> bytes(size);
    //std::cout << "size: " << size;

    is.read(reinterpret_cast<char*>(bytes.data()), size);
    if (!is.good()) { throw std::runtime_error("Error reading bytes"); }

    return bytes;
}

void serializePdb(std::vector<uint8_t> const& data, std::string filename) {
    std::ofstream os(filename, std::ios::binary);
    if (!os.good()) { throw std::runtime_error("Cannot open file for writing"); }

    uint32_t size = data.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    if (!os.good()) { throw std::runtime_error("Error writing size"); }

    os.write(reinterpret_cast<const char*>(data.data()), size);
    if (!os.good()) { throw std::runtime_error("Error writing bytes"); }

    os.close();
}
