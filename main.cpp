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
#include "cube.hpp"


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

    //std::cout << qb;
    //std::cout << qb.rotXaxis(CrossSection::Back, )

    /*
    std::cout << "Cube: " << qb;
    std::cout << qb.changePerspective(Perspective::Left).changePerspective(Perspective::Left).changePerspective(Perspective::Left).changePerspective(Perspective::Left);
    std::cout << "Right perspective: " << qb.changePerspective(Perspective::Right);
    std::cout << "Left perspective: " << qb.changePerspective(Perspective::Left);

    std::cout << MiniCube(qb) << "\n";*/
    
    /*
    std::cout << "Original: " << qb << "\n\n\n";

    std::cout << "X axis back right rot: " << qb.rotXaxis(CrossSection::Back, Direction::Right);
    std::cout << "X axis back left rot: " << qb.rotXaxis(CrossSection::Back, Direction::Left);
    std::cout << "X axis back 180 rot: " << qb.rotXaxis(CrossSection::Back, Direction::_180);
    std::cout << "X axis middle left rot: " << qb.rotXaxis(CrossSection::Middle, Direction::Left);*/


    /*
    std::cout << "Neighbors:" << std::endl;

    for (int i = 0; i < 9; i++) {
        std::cout << qb.getNeighbors()[i];
    }*/

    //srand(time(NULL));
    
    
    //occurs at i=48 ??
    /*
    for (int i = 0; i < 10000000; i++) {
        auto allNeighbors = qb.getNeighbors();

        //std::array<Cube, 18> selectNeighbors;
        //std::copy(allNeighbors.begin(), allNeighbors.begin()+9, selectNeighbors.begin());
        //std::copy(allNeighbors.begin()+18, allNeighbors.begin()+27, selectNeighbors.begin()+9);


        uint32_t nghbrIdx = (rand()%27);
        qb = qb.getNeighbors()[nghbrIdx];

        //std::cout << "neighbor index: " << nghbrIdx;
        //std::cout << qb;
            

        if (!qb.isValidColorDistribution()) {
            
            std::cout << "\n\n\nError:" << std::endl;
            std::cout << "Loop index: " << i << std::endl;
            std::cout << "Neighbor index: " << nghbrIdx << std::endl;
            std::cerr << "Normal cube:\n" << qb;
            std::cout << "\nMini cube:\n" << MiniCube(qb) << std::endl;
            std::cout << "Index: " << MiniCube(qb).getIdx() << std::endl;
            assert(false);
        }
    }



    std::cout << "Old cube: " << qb;
    
    int nghbrIdx = rand()%27;
    qb = qb.getNeighbors()[nghbrIdx];
    MiniCube mini = MiniCube(qb);
    uint32_t cubeIdx = mini.getIdx();

    std::cout << "Neighbor index: " << nghbrIdx << std::endl;
    std::cerr << "New cube:\n" << qb;
    std::cout << "\nMini cube:\n" << MiniCube(qb) << std::endl;
    std::cout << "Index: " << cubeIdx<< std::endl;*/


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
    
    //PDB cornerCubieDB(MiniCube(), 3674160);
    
    using Color::White;
    using Color::Green;
    using Color::Red;
    using Color::Yellow;
    using Color::Blue;
    using Color::Orange;

    Cube qb;

    for (int i = 0; i < 20; i++) {
        auto allNeighbors = qb.getNeighbors();

        //std::array<Cube, 18> selectNeighbors;
        //std::copy(allNeighbors.begin(), allNeighbors.begin()+9, selectNeighbors.begin());
        //std::copy(allNeighbors.begin()+18, allNeighbors.begin()+27, selectNeighbors.begin()+9);


        uint32_t nghbrIdx = (rand()%27);
        qb = qb.getNeighbors()[nghbrIdx];

    }
    
    qb.front = White<<24 | Blue<<21 | Orange<<18
            | Yellow<<15 | Red<<12 | Orange<<9
            | Orange<<6 | White<<3 | Blue;

    qb.back = Orange<<24 | Green<<21 | Red<<18
            | Green<<15 | Orange<<12 | Green<<9
            | Red<<6 | Blue<<3 | Red;

    qb.top = White<<24 | Red<<21 | Blue<<18
            | Yellow<<15 | White<<12 | Red<<9
            | Green<<6 | White<<3 | Green;

    qb.bottom = White<<24 | Orange<<21 | Orange<<18
                | White<<15 | Yellow<<12 | Blue<<9
                | Green<<6 | Orange<<3 | Blue;

    qb.left = Blue<<24 | Blue<<21 | Red<<18
            | Yellow<<15 | Green<<12 | Red<<9
            | Yellow<<6 | Green<<3 | Green;

    qb.right = Yellow<<24 | Blue<<21 | Yellow<<18
            | Yellow<<15 | Blue<<12 | Orange<<9
            | White<<6 | Red<<3 | Yellow;


    /*
    qb = qb.rotVert(Column::Middle, Direction::Up);
    qb = qb.rotHoriz(Row::Middle, Direction::_180);
    qb = qb.rotVert(Column::Right, Direction::Down);
    qb = qb.rotHoriz(Row::Bottom, Direction::Right);
    qb = qb.rotXaxis(CrossSection::Middle, Direction::Right);
    qb = qb.rotVert(Column::Right, Direction::_180);*/



    std::cout << "Scrambled cube: " << qb;
    
    std::cout << "Solving cube using IDA*:" << std::endl;


    auto sol = idaStar(qb);

    std::cout << "Done!" << std::endl;

    for (auto cube : sol) {
        std::cout << cube << std::endl;
    }

    return 0;
}

