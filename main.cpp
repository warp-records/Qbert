//#include "cube.hpp"
#include "pdb_gen/subset_cube.hpp"

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include "alg.hpp"


int main() {

    //The most optimal algorithm to solve a Rubiks cube
    //is just to peel the stickers
    
    std::cout << R"(
        Rubix

         ___ ___ ___
       /___/___/___/|
      /___/___/___/||
     /___/___/__ /|/|
    |   |   |   | /||
    |___|___|___|/|/|
    |   |   |   | /||
    |___|___|___|/|/
    |   |   |   | /
    |___|___|___|/

    )" << std::endl;

    MiniCube qb;
    MiniCube qb2;

    std::vector<uint8_t> pdb = pdbGen(qb, 11022480);

    //std::cout << pdb.size() << std::endl;

    std::unordered_map<uint32_t, MiniCube> cubeMap;

    unsigned long long collisions = 0;
    unsigned count = 0;

    auto start = std::chrono::high_resolution_clock::now();

    while (std::chrono::high_resolution_clock::now() - start < std::chrono::milliseconds(500)) {
        
        qb = qb.rotVert(static_cast<Column>(rand() & 1),  static_cast<Direction>(rand() & 1));
        qb = qb.rotHoriz(static_cast<Row>(rand() & 1), static_cast<Direction>((rand() & 1) + 2));

        qb2 = qb2.rotVert(static_cast<Column>(rand() & 1),  static_cast<Direction>(rand() & 1));
        qb2 = qb2.rotHoriz(static_cast<Row>(rand() & 1), static_cast<Direction>((rand() & 1) + 2));

        if (qb.getIdx() == qb2.getIdx() && qb != qb2) {
            collisions++;
        }


        count += 2;
    }

    std::cout << "collisions: " << collisions << std::endl;
    std::cout << "cubes generated: " << count << std::endl;

    std::cout << "Cubes with same index (" << qb.getIdx() << "):\n\n" << qb << "\n" << qb2 << std::endl;
    //std::cout << "number of unique cubes: " << cubeMap.size() << std::endl;
    
    return 0;
}



/*
    unsigned uniqueCubes = 0;
    unsigned minHash = UINT_MAX;
    unsigned maxHash = 0;

    std::vector<bool> cubeIndices(1000000);

    unsigned long long count = 0;
    //prevent compiler from optimizing out isSolved()
    //uint16_t optimizationBlock = 0;
    
     auto start = std::chrono::high_resolution_clock::now();
    
    while (std::chrono::high_resolution_clock::now() - start < std::chrono::milliseconds(1700)) {
        
        qb = qb.rotVert(static_cast<Column>(rand() & 1),  static_cast<Direction>(rand() & 1));
        uint32_t hash = qb.getIdx();
        //Cube hash already exists but it doesn't match this cube
        uniqueCubes += !cubeIndices.at(hash);
        cubeIndices.at(hash) = true;

        minHash = std::min(hash, minHash);
        maxHash = std::max(hash, maxHash);

        qb = qb.rotHoriz(static_cast<Row>(rand() & 1), static_cast<Direction>((rand() & 1) + 2));
        hash = qb.getIdx();
        uniqueCubes += !cubeIndices.at(hash);
        cubeIndices.at(hash) = true;

        maxHash = std::max(hash, maxHash);
        minHash = std::min(hash, minHash);

        count += 2;

    }
    
    //I CAN'T FUCKING BELIEVE HOW FAST MY CODE IS!
    std::cout << "cubes generated: " << count << "\n\n";
    std::cout << "number of unique cubes: " << uniqueCubes << std::endl;
    std::cout << "min hash idx:" << minHash << std::endl;
    std::cout << "max hash idx: " << maxHash << std::endl;
    std::cout << qb << std:: endl;
*/
