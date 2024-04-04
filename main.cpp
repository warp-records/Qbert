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

    
    std::vector<uint8_t> pdb = pdbGen(qb, 9972719);

    /*
    std::cout << qb << "\n";

    qb = qb.changePerspective(Perspective::Right);
    std::cout << qb << std::endl;

    qb = qb.changePerspective(Perspective::Left);
    std::cout << qb << std::endl;*/

    
    /*
    for (MiniCube neighbor : qb.getNeighbors()) {
        std::cout << neighbor << std::endl;
    }*/

    
    
    std::cout << "Cubes that can be solved in [x] moves: [n]\n\n";;
    for (int i = 0; i <= 11; i++) {
        std::cout << i << ": " << std::count(pdb.begin(), pdb.end(), i) << "\n";
    }
    
    /*
    MiniCube qb;
    
    
    std::cout << qb << "\nCubie IDs:" << std::endl;

    for (int i = 0; i < 8; i++) {
        std::cout << "(" << (i&0b001) << ", " << ((i&0b010)>>1) << ", "  << ((i&0b100)>>2) << "): ";
        std::cout << (int) qb.getCubieInfo(i&0b001, (i&0b010)>>1, (i&0b100)>>2).id << std::endl;
    }

    srand(time(NULL));

    for (int i = 0; i < rand()%1000; i++) {
        qb = qb.rotVert(Column::Right, Direction::Down);
        qb = qb.rotHoriz(Row::Top, Direction::Left);
    }

    std::cout << "\n" << qb << "\nCubie IDs after scramble:\n" << std::endl;

    for (int i = 0; i < 8; i++) {
        std::cout << "(" << (i&0b001) << ", " << ((i&0b010)>>1) << ", "  << ((i&0b100)>>2) << "): ";
        std::cout << (int) qb.getCubieInfo(i&0b001, (i&0b010)>>1, (i&0b100)>>2).id << std::endl;
    }*/

    /*
    MiniCube qb;

    std::cout << qb << "\n";

    qb = qb.rotVert(Column::Left, Direction::Down);
    std::cout << qb << "\n";

    qb = qb.rotHoriz(Row::Top, Direction::Left);
    std::cout << qb << "\n";

    qb = qb.rotVert(Column::Right, Direction::Up);
    std::cout << qb << "\n";

    qb = qb.rotHoriz(Row::Bottom, Direction::Left);
    std::cout << qb << "\n";*/

    //std::vector<uint8_t> pdb = pdbGen(qb, 11022480);

    //std::cout << pdb.size() << std::endl;

    /*
    std::unordered_map<uint64_t, MiniCube> cubeMap;

    unsigned long long collisions = 0;
    unsigned count = 0;

    auto start = std::chrono::high_resolution_clock::now();

    while (std::chrono::high_resolution_clock::now() - start < std::chrono::milliseconds(5000)) {
        
        qb = qb.rotVert(static_cast<Column>(rand() & 1),  static_cast<Direction>(rand() & 1));
        qb = qb.rotHoriz(static_cast<Row>(rand() & 1), static_cast<Direction>((rand() & 1) + 2));


        if (cubeMap.contains(qb.getIdx()) && cubeMap.at(qb.getIdx()) != qb) {
            assert(false);
        }
        cubeMap.insert({qb.getIdx(), qb});


        
        if (qb.getIdx() == qb2.getIdx() && qb != qb2) {
            collisions++;
            //assert(false);
            for (int i = 0; i < 8; i++) {
                std::cout << "(" << (i&0b001) << ", " << ((i&0b010)>>1) << ", "  << ((i&0b100)>>2) << "): ";
                std::cout << (int) qb.getCubieInfo(i&0b001, (i&0b010)>>1, (i&0b100)>>2).id << std::endl;
            }

            std::cout << "\n\n\n";
            for (int i = 0; i < 8; i++) {
                std::cout << "(" << (i&0b001) << ", " << ((i&0b010)>>1) << ", "  << ((i&0b100)>>2) << "): ";
                std::cout << (int) qb2.getCubieInfo(i&0b001, (i&0b010)>>1, (i&0b100)>>2).id << std::endl;
            }

            std::cout << "Cubes with same index (" << qb.getIdx() << "):\n\n" << qb << "\n" << qb2 << std::endl;

            break;
        }


        count += 1;
    }

    std::cout << "collisions: " << collisions << std::endl;
    std::cout << "cubes generated: " << count << std::endl;

    std::cout << "IT WORKKSSS!!" << std::endl;
    //std::cout << "number of unique cubes: " << cubeMap.size() << std::endl;*/
    
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
