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

    std::vector<uint8_t> pdb = pdbGen(qb, 41392);

    
    std::cout << "Cubie ID for:\n" << std::endl;

    for (int i = 0; i < 8; i++) {
        std::cout << "(" << (i&0b001) << ", " << ((i&0b010)>>1) << ", "  << ((i&0b100)>>2) << "): ";
        std::cout << (int) qb.getCubieID(i&0b001, (i&0b010)>>1, (i&0b100)>>2) << std::endl;
    }

    for (int i = 0; i < 100; i++) {
        qb = qb.rotVert(Column::Left, Direction::Down);
        qb = qb.rotHoriz(Row::Top, Direction::Left);
    }

    std::cout << qb << std::endl;

    std::cout << "Cubie IDs after scramble: " << std::endl;

    for (int i = 0; i < 8; i++) {
        std::cout << "(" << (i&0b001) << ", " << ((i&0b010)>>1) << ", "  << ((i&0b100)>>2) << "): ";
        std::cout << (int) qb.getCubieID(i&0b001, (i&0b010)>>1, (i&0b100)>>2) << std::endl;
    }

    std::cout << "Cube:\n" << qb;

    /*
    std::cout << "\nCube faces at:\n" << std::endl;

    std::array<char, 6> const colors {{
        'W', // White  0b000
        'G', // Green  0b001
        'B', // Blue   0b010
        'O', // Orange 0b011
        'R', // Red    0b100
        'Y'  // Yellow 0b101
    }};

    for (int i = 0; i < 8; i++) {
        bool x = i&0b001;
        bool y = i&0b010;
        bool z = i&0b100;

        uint16_t xFace = x==0 ? qb.left : qb.right;
        //checked
        xFace >>= (x^z)==0 ? 0*3 : 1*3;
        xFace >>= y==0 ?     2*3 : 0*3;
        xFace &= 0b111;

        uint16_t yFace = y==0 ? qb.top : qb.bottom;
        //checked
        yFace >>= x==0 ?     1*3 : 0*3;
        yFace >>= (y^z)==0 ? 0*3 : 2*3;
        yFace &= 0b111;

        uint16_t zFace = z==0 ? qb.front : qb.back;
        //check
        //I think we actually ignore z here since the back is inverted!
        zFace >>= (x^z)==0 ?     1*3 : 0*3;
        zFace >>= y==0 ?     2*3 : 0*3;
        zFace &= 0b111;


        std::cout << "(" << (i&0b001) << ", " << ((i&0b010)>>1) << ", "  << ((i&0b100)>>2) << "):\n";
        std::cout << "\tX face: " << colors.at(xFace) << "\n\tY face: " << colors.at(yFace) << 
            "\n\tZ face: " << colors.at(zFace) << "\n\n";
    }*/
    
    //std::vector<Cube> cubeVec;
    
    /*
    std::unordered_map<uint32_t, MiniCube> cubeMap;

    unsigned long long collisions = 0;
    unsigned count = 0;

    auto start = std::chrono::high_resolution_clock::now();

    while (std::chrono::high_resolution_clock::now() - start < std::chrono::milliseconds(1500)) {
        
        qb = qb.rotVert(static_cast<Column>(rand() & 1),  static_cast<Direction>(rand() & 1));
        uint32_t hash = qb.getIdx();
        //Cube hash already exists but it doesn't match this cube
        if (cubeMap.find(hash)!=cubeMap.end() && cubeMap.find(hash)->second != qb) {
            collisions++;
        }
        cubeMap.insert({hash, qb});

        qb = qb.rotHoriz(static_cast<Row>(rand() & 1), static_cast<Direction>((rand() & 1) + 2));
        hash = qb.getIdx();
         if (cubeMap.find(hash)!=cubeMap.end() && cubeMap.find(hash)->second != qb) {
            collisions++;
        }

        cubeMap.insert({hash, qb});


        count += 2;
    }

    std::cout << "collisions: " << collisions << std::endl;
    std::cout << "cubes generated: " << count << std::endl;
    std::cout << "number of unique cubes: " << cubeMap.size() << std::endl;*/

    /*
    std::cout << "Cube:\n" << qb << "\n\nIndex: " << qb.getIdx() << "\n";

    MiniCube qb2 = qb.rotHoriz(Row::Top, Direction::Right);
    qb2 = qb2.rotHoriz(Row::Bottom, Direction::Right);

    std::cout << (qb2 == qb ? "equal" : "not equal") << std::endl;
    //std::cout << "Cube:\n" << qb2 << "\n\nIndex: " << qb2.getIdx() << "\n";

    qb2 = qb2.rotVert(Column::Left, Direction::Up);
    qb2 = qb2.rotVert(Column::Right, Direction::Up);
    std::cout << (qb2 == qb ? "equal" : "not equal") << std::endl;


    //std::cout << "Cube:\n" << qb2 << "\n\nIndex: " << qb2.getIdx() << "\n";

    qb2 = qb2.rotVert(Column::Right, Direction::Up);
    //std::cout << "Cube:\n" << qb2 << "\n\nIndex: " << qb2.getIdx() << "\n";
    std::cout << (qb2 == qb ? "equal" : "not equal") << std::endl;


    qb2 = qb2.rotVert(Column::Left, Direction::Down);
    std::cout << (qb2 == qb ? "equal" : "not equal") << std::endl;

    qb2 = qb2.rotVert(Column::Right, Direction::_180);
    std::cout << (qb2 == qb ? "equal" : "not equal") << std::endl;

    qb2 = qb2.rotHoriz(Row::Top, Direction::_180);
    qb2 = qb2.rotHoriz(Row::Bottom, Direction::_180);
    std::cout << (qb2 == qb ? "equal" : "not equal") << std::endl;*/

    /*
    std::cout << "Cubes that can be solved in [x] moves: [n]\n\n";;
    for (int i = 0; i <= 11; i++) {
        std::cout << i << ": " << std::count(pdb.begin(), pdb.end(), i) << "\n";
    }
    
    for (int i = 0; i < 100; i++) {
        std::cout << "Cube #"<<i<<":\t" << (int) pdb[i] << std::endl;
    }
    */

    return 0;
}

    /*
    MiniCube qb;
    //std::vector<Cube> cubeVec;
    
    std::unordered_map<uint32_t, MiniCube> cubeMap;

    unsigned long long collisions = 0;
    unsigned count = 0;

    auto start = std::chrono::high_resolution_clock::now();

    while (std::chrono::high_resolution_clock::now() - start < std::chrono::milliseconds(1500)) {
        
        qb = qb.rotVert(static_cast<Column>(rand() & 1),  static_cast<Direction>(rand() & 1));
        uint32_t hash = qb.getIdx();
        //Cube hash already exists but it doesn't match this cube
        if (cubeMap.find(hash)!=cubeMap.end() && cubeMap.find(hash)->second != qb) {
            collisions++;
        }
        cubeMap.insert({hash, qb});

        qb = qb.rotHoriz(static_cast<Row>(rand() & 1), static_cast<Direction>((rand() & 1) + 2));
        hash = qb.getIdx();
         if (cubeMap.find(hash)!=cubeMap.end() && cubeMap.find(hash)->second != qb) {
            collisions++;
        }

        cubeMap.insert({hash, qb});


        count += 2;
    }

    std::cout << "collisions: " << collisions << std::endl;
    std::cout << "cubes generated: " << count << std::endl;
    std::cout << "number of unique cubes: " << cubeMap.size() << std::endl;*/


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
