#include <iostream>
#include "cube.hpp"
#include <chrono>


int main() {

    //The most optimal algorithm to solve a Rubiks cube
    //is just to peel and rearrange the stickers
    
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

    Cube qb;
    //std::vector<Cube> cubeVec(10000000);

    auto start = std::chrono::high_resolution_clock::now();

    unsigned long long count = 0;
    //prevent compiler from optimizing out isSolved()
    bool optimizationBlock = 0;

    while (std::chrono::high_resolution_clock::now() - start < std::chrono::seconds(1)) {
        
        qb = qb.rotVert(static_cast<Column>(count & 1),  static_cast<Direction>(count & 1));
        optimizationBlock ^= qb.isSolved();

        qb = qb.rotHoriz(static_cast<Row>(count & 1), static_cast<Direction>((count & 1) + 2));
        optimizationBlock ^= qb.isSolved();

        count += 2;
    }

    //I CAN'T FUCKING BELIEVE HOW FAST MY CODE IS!
    std::cout << "cubes generated: " << count << "\n\n";

    std::cout << qb << std:: endl;

    return 0;
}
