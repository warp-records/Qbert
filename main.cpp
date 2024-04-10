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

    std::cout << "Solving cube using IDDFS:" << std::endl;

    Cube qb;
    qb = qb.rotVert(Column::Left, Direction::Up);
    qb = qb.rotHoriz(Row::Top, Direction::Left);
    qb = qb.rotVert(Column::Right, Direction::Down);
    qb = qb.rotHoriz(Row::Bottom, Direction::Right);
    //qb = qb.rotVert(Column::Middle, Direction::Up);
    //qb = qb.rotVert(Column::Middle, Direction::Up);


    auto sol = idaStar(qb);

    std::cout << "Done!" << std::endl;

    for (auto cube : sol) {
        std::cout << cube << std::endl;
    }

    return 0;
}

