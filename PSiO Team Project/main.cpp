#include "Game.h"

#include <iostream>

int main() {
    std::cout << "Poznan University of Technology\n";
    std::cout << "Structural and Object-Oriented Programming\n";
    std::cout << "[June 2023]\n";
    std::cout << "Team Project\n";
    std::cout << "@KonradCeglarski\n@IgnacyChrobak\n";

    Game game;
    game.run();

    return 0;
}
