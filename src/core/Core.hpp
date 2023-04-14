/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** Core
*/

#pragma once

#include <bits/stdc++.h>
#include "../games/IGames.hpp"
#include "../lib/ILib.hpp"
#include "dl/dl.hpp"

class Core {
    public:
        Core(const std::string &activeLib);
        ~Core();

        void update();
        void event(std::string event);   

        void loadGame(std::string gameName);
        void loadLib(std::string libName);

        void isGameLoaded() { if (!_game) throw std::runtime_error("Game not loaded"); }
        void isLibLoaded() { if (!_lib) throw std::runtime_error("Lib not loaded"); }

        bool isWindowOpen() { return _lib->isOpen(); }

        void menuState(std::string activeLib);
        bool isMenu() { return _inMenu; }
        void setMenu(bool state) { _inMenu = state; }

        std::string getPlayerName() { return _playerName; }
        void setPlayerName(std::string name) { _playerName = name; }

        bool leave() { return _leave; };

    protected:
    private:
        std::shared_ptr<dl> _gameDL;
        std::shared_ptr<IGames> (*_dlCreateGame)(void) = nullptr;
        std::shared_ptr<IGames> _game;

        std::shared_ptr<dl> _libDL;
        std::shared_ptr<ILib> (*_dlCreateLib)(void) = nullptr;
        std::shared_ptr<ILib> _lib;

        bool _inMenu = true;
        bool _leave = false;

        std::string _playerName = "Player";

        std::vector<std::pair<std::string, bool>> _menuGraphic;
        std::vector<std::pair<std::string, bool>> _menuGames;
};


#include <unistd.h>
class System {
    public:
        static int SystemExec(const std::string &cmd) {
            return system(cmd.c_str());
        }

    protected:
    private:
};
