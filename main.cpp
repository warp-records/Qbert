//#include "cube.hpp"
#include "pdb_gen/subset_cube.hpp"

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <sstream>
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

    std::cout << "Generating pattern database..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    MiniCube init;

    //MiniCube qb;
    PDB pdb(init, 3674160);

    auto elapsed = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "Finished in " << std::setprecision(2) << elapsed << "s\n" << std::endl;

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

    

    std::array<uint32_t, 12> counts{};

    //std::cout << i << ": " << std::count(pdb.begin(), pdb.end(), i) << "\n";
    for (int i = 0; i < 3674160; i++) {
        uint8_t numMoves = pdb.getDist(i);
        counts[numMoves]++;
    }


    std::cout << "Cubes that can be solved in [x] moves (half turn metric): [n]\n\n";

    for (int i = 0; i < 12; i++) {
        std::cout << i << ": " << counts[i] << "\n";
    }
    
    MiniCube qb;
    qb = qb.rotHoriz(Row::Top, Direction::Left);
    qb = qb.rotHoriz(Row::Bottom, Direction::Right);
    qb = qb.rotVert(Column::Right, Direction::Up);

    std::cout << "It will take " << (int) pdb.getDist(qb.getIdx()) << 
        " moves to solve this cube" << std::endl;


    return 0;
}

