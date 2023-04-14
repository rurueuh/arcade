/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** main
*/

#include "dl/dl.hpp"
#include "../games/IGames.hpp"
#include "Core.hpp"

int main(int ac, char **av)
{
    srand(time(NULL));
    if (ac != 2){
        std::cerr << "Usage: ./arcade [lib]" << std::endl;
        return 84;
    }
    try {
        Core core(av[1]);
        std::string input;
        std::cout << "Enter your name > ";
        std::cin >> input;
        if (input.size() < 3)
            throw std::runtime_error("Name too short");
        core.setPlayerName(input);
        core.loadLib(av[1]);
        // core.loadGame("libcentipede");
        while (core.isWindowOpen() && !core.leave()) {
            if (core.isMenu())
                core.menuState(av[1]);
            else
                core.update();
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
