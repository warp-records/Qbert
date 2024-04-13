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

    Cube qb;

    
    for (int i = 0; i <  100; i++) {
        qb = qb.rotVert(Column::Middle, Direction::Up);
        //std::cout << qb << "\n";

        qb = qb.rotHoriz(Row::Middle, Direction::_180);
        //std::cout << qb << "\n";

        qb = qb.rotVert(Column::Right, Direction::Down);
        //std::cout << qb << "\n";

        qb = qb.rotHoriz(Row::Bottom, Direction::Right);
        //std::cout << qb << "\n";
    }

    std::cout << "Cube: " << qb;
    std::cout << qb.changePerspective(Perspective::Left).changePerspective(Perspective::Left).changePerspective(Perspective::Left).changePerspective(Perspective::Left);
    std::cout << "Right perspective: " << qb.changePerspective(Perspective::Right);
    std::cout << "Left perspective: " << qb.changePerspective(Perspective::Left);

    std::cout << MiniCube(qb) << "\n";
    

    //std::cout << "Original: " << qb << "\n\n\n";
    
    //std::cout << "Neighbors:" << std::endl;

    
    std::cout << "Cube before z axis rot: " << qb;


    std::cout << "Cube after rot:";
    std::cout << qb.getNeighbors()[0];

    //srand(time(NULL));
    
    /*
    //occurs at i=48 ??
    for (int i = 0; i < 10000000; i++) {
        int nghbrIdx = (rand()%18+9);
        qb = qb.getNeighbors()[nghbrIdx];
            

        if (!(0 <= MiniCube(qb).getIdx() && MiniCube(qb).getIdx() < 3674160)) {
            
            std::cout << "Loop index: " << i << std::endl;
            std::cout << "Neighbor index: " << nghbrIdx << std::endl;
            std::cerr << "Normal cube:\n" << qb;
            std::cout << "\nMini cube:\n" << MiniCube(qb) << std::endl;
            std::cout << "Index: " << MiniCube(qb).getIdx() << std::endl;
            assert(false);
        }
    }*/


    /*
    std::cout << "Old cube: " << qb;
    
    int nghbrIdx = rand()%27;
    qb = qb.getNeighbors()[nghbrIdx];

    std::cout << "Neighbor index: " << nghbrIdx << std::endl;
    std::cerr << "New cube:\n" << qb;
    std::cout << "\nMini cube:\n" << MiniCube(qb) << std::endl;
    std::cout << "Index: " << MiniCube(qb).getIdx() << std::endl;*/


    //for (int i = 0; i < )

    
    //PDB database(MiniCube(), 3674160);
    /*
    MiniCube qb;
    qb = qb.rotVert(Column::Left, Direction::Up);
    std::cout << (int) database.getDist(qb.getIdx()) << std::endl;

    qb = qb.rotHoriz(Row::Top, Direction::Left);
    std::cout << (int) database.getDist(qb.getIdx()) << std::endl;

    qb = qb.rotVert(Column::Right, Direction::Down);
    std::cout << (int) database.getDist(qb.getIdx()) << std::endl;*/
    /*
    std::array<uint32_t, 12> counts{};
    PDB database(MiniCube(), 3674160);

    for (int i = 0; i < 3674160; i++) {
        uint8_t numMoves = database.getDist(i);
        counts[numMoves]++;
    }

    std::cout << "Cubes that can be solved in [x] moves: [n]\n\n";

    for (int i = 0; i < 12; i++) {
        std::cout << i << ": " << counts[i] << "\n";
    }

    std::cout << qb << std::endl;*/

    /*
    Cube qb;

    qb = qb.rotVert(Column::Right, Direction::Down);
    std::cout << database.getDist(MiniCube(qb).getIdx()) << std::endl;

    qb = qb.rotHoriz(Row::Bottom, Direction::Right);
    std::cout << database.getDist(MiniCube(qb).getIdx()) << std::endl;

    qb = qb.rotVert(Column::Right, Direction::Up);
    std::cout << database.getDist(MiniCube(qb).getIdx()) << std::endl;

    qb = qb.rotHoriz(Row::Bottom, Direction::Right);
    std::cout << database.getDist(MiniCube(qb).getIdx()) << std::endl;

    std::cout << "Index: " << MiniCube(qb).getIdx() << std::endl;
    std::cout << "Cube: " << qb << std::endl;
    std::cout << "Minicube:\n" << MiniCube(qb) << std::endl;*/

    
    //return 0;

    
    //Cube qb;
    

    qb = qb.rotVert(Column::Middle, Direction::Up);

    qb = qb.rotHoriz(Row::Middle, Direction::_180);
    qb = qb.rotVert(Column::Right, Direction::Down);
    qb = qb.rotHoriz(Row::Bottom, Direction::Right);



    
    std::cout << "Solving cube using IDDFS:" << std::endl;


    auto sol = idaStar(qb);

    std::cout << "Done!" << std::endl;

    for (auto cube : sol) {
        std::cout << cube << std::endl;
    }

    return 0;
}

