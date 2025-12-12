#include "Library.h"
#include "Game.h"
#include "Utils.h"
#include <iostream>
#include <string>

int main() {
    std::string puzzleFile = "data/puzzles.txt";
    auto puzzles = loadPuzzles(puzzleFile);
    if (puzzles.empty()) {
        std::cerr << "Error: No puzzles loaded from " << puzzleFile << ". Exiting." << std::endl;
        return 1;
    }

   
    Library lib(puzzles);

    Game game(lib);
    game.start();

    return 0;
}