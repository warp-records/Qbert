#include <iostream>
#include "cube.hpp"

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
    //qb = qb.rotVert(Column::Left, Direction::Up);
    qb = qb.rotVert(Column::Left, Direction::Down);
    std::cout << qb << "\n\n";

    qb = qb.rotHoriz(Row::Top, Direction::Left);
    std::cout << qb << "\n\n";

    qb = qb.rotVert(Column::Left, Direction::Up);
    std::cout << qb << "\n\n";

    qb = qb.rotHoriz(Row::Top, Direction::Right);
    std::cout << qb << "\n\n";

    return 0;
}
