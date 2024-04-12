//#include "cube.hpp"
#include "pdb_gen/subset_cube.hpp"

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <bitset>
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

    /*
    std::cout << "Neighbors:" << std::endl;

    for (auto neighbor : mini.getNeighbors()) {
        std::cout << neighbor << std::endl;
    }

    for (int i = 0; i < 1000000000; i++) {
        mini = mini.getNeighbors()[rand()%9];
        if (!(0 <= mini.getIdx() && mini.getIdx() < 3674160)) {
            std::cerr << i << std::endl;
            std::cerr << mini.getIdx() << std::endl;
            assert(false);
        }
    }*/

    Cube qb;
    qb = qb.rotVert(Column::Left, Direction::Up);
    qb = qb.rotHoriz(Row::Top, Direction::Left);
    qb = qb.rotVert(Column::Right, Direction::Down);
    qb = qb.rotHoriz(Row::Bottom, Direction::Right);
    //qb = qb.rotVert(Column::Middle, Direction::Up);
    //qb = qb.rotHoriz(Row::Middle, Direction::Left);
    //qb = qb.rotVert(Column::Middle, Direction::Up);

    std::cout << qb << std::endl;

    std::cout << "Solving cube using IDDFS:" << std::endl;


    auto sol = idaStar(qb);

    std::cout << "Done!" << std::endl;

    for (auto cube : sol) {
        std::cout << cube << std::endl;
    }

    return 0;
}

