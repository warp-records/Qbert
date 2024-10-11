#include <time.h>
#include <cassert>
#include "cube.hpp"
#include "edge_cubies.hpp"
#include "mini_cube.hpp"

#include <iostream>
#include <iterator>
//I don't even remember including this
#include <sys/_types/_off_t.h>
#include <unordered_set>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <locale>
#include <array>
#include "alg.hpp"
#include "cube.hpp"


constexpr std::string_view VERSION = "0.3.0";

int main() {

    //The most optimal algorithm to solve a Rubiks cube
    //is just to peel the stickers

    std::cout << R"(

            ██████    █████                         █████
          ███░░░░███ ░░███                         ░░███
         ███    ░░███ ░███████   ██████  ████████  ███████
        ░███     ░███ ░███░░███ ███░░███░░███░░███░░░███░
        ░███   ██░███ ░███ ░███░███████  ░███ ░░░   ░███
        ░░███ ░░████  ░███ ░███░███░░░   ░███       ░███ ███
         ░░░██████░██ ████████ ░░██████  █████      ░░█████
           ░░░░░░ ░░ ░░░░░░░░   ░░░░░░  ░░░░░        ░░░░░

)" << "Version " << VERSION << R"(

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


    //serializePdb(PDB(EdgeCubies(), 510935040).data, "pdb/7_edge_cubies_first.pdb");
    //return 0;

    //it can do up to 15!
    qb = qb.rotVert(Column::Middle, Direction::Up);
    qb = qb.rotHoriz(Row::Middle, Direction::_180);
    qb = qb.rotVert(Column::Right, Direction::Down);
    qb = qb.rotHoriz(Row::Bottom, Direction::Right);
    qb = qb.rotXaxis(CrossSection::Middle, Direction::Right);
    qb = qb.rotVert(Column::Right, Direction::_180);
    qb = qb.rotHoriz(Row::Bottom, Direction::Left);
    qb = qb.rotXaxis(CrossSection::Front, Direction::_180);
    qb = qb.rotVert(Column::Left, Direction::_180);
    qb = qb.rotXaxis(CrossSection::Front, Direction::Right);
    qb = qb.rotHoriz(Row::Top, Direction::Left);
    qb = qb.rotXaxis(CrossSection::Back, Direction::_180);
    qb = qb.rotVert(Column::Right, Direction::_180);
    qb = qb.rotHoriz(Row::Bottom, Direction::_180);
    //qb = qb.rotXaxis(CrossSection::Middle, Direction::Right);
    //qb = qb.rotHoriz(Row::Bottom, Direction::Right);
    //Check if pattern databases exist, and generate them
    //if they don't
    std::ifstream pdbCheck;

    pdbCheck.open("pdb/corner_cubies.pdb");
    //actually insane that this generates in half a second on my mac
    if (!pdbCheck.good()) { serializePdb(PDB(MiniCube(), 3674160).data, "pdb/corner_cubies.pdb"); }
    pdbCheck.close();
    pdbCheck.open("pdb/edge_cubies_first.pdb");
    if (!pdbCheck.good()) { serializePdb(PDB(EdgeCubies(), 510935040).data, "pdb/7_edge_cubies_first.pdb"); }
    pdbCheck.close();
    //pdbCheck.open("pdb/edge_cubies_second.pdb");
    //if (!pdbCheck.good()) { serializePdb(PDB(EdgeCubies(true), 42577920).data, "pdb/edge_cubies_second.pdb"); }
    //pdbCheck.close();

    std::cout << "Scrambled cube:\n" << qb;
    std::cout << "\nSolving cube using IDA*:" << std::endl;

    //time how long it takes to solve
    auto start = std::chrono::high_resolution_clock::now();

    //solve cube
    auto sol = idaStar(qb);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    int len = sol.first.size()-1;
    bool useAn = len==8 || len==11 || len==18;

    //Remove these two lines if compiling with GCC
    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());

    std::cout << "Done! Found " << (useAn ? "an " : "a ") <<
        (sol.first.size()-1) << " move solution in " << duration.count() << "ms :" << std::endl;
    std::cout << "Generated " << sol.second << " nodes in " << duration.count() << "ms";
    std::cout << " (" << (sol.second*1000/duration.count()) << " nodes/s)";

    for (auto cube : sol.first) {
        std::cout << cube << std::endl;
    }

    return 0;
}
