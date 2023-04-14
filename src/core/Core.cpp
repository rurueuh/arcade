/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** Core
*/

#include "Core.hpp"
#include <Dir.hpp>

static void getAllFileInFolder(std::string folder, std::vector<std::string> &callback)
{
    Dir dir;
    dir.open(folder);
    callback = dir.getFile();
}

Core::Core(const std::string &activeLib)
{
    _menuGraphic.clear();
    _menuGames.clear();
    std::vector<std::string> libList;
    std::vector<std::string> gameList;

    getAllFileInFolder("./lib", libList);
    getAllFileInFolder("./lib", gameList);

    static const std::vector<std::string> autorisedLibs = {
        "arcade_ndk++.so",
        "arcade_aalib.so",
        "arcade_libcaca.so",
        "arcade_allegro5.so",
        "arcade_xlib.so",
        "arcade_gtk+.so",
        "arcade_sfml.so",
        "arcade_irrlicht.so",
        "arcade_opengl.so",
        "arcade_vulkan.so",
        "arcade_qt5.so",
        "arcade_sdl2.so",
        "arcade_ncurses.so"
    };

    static const std::vector<std::string> autorisedGames = {
        "arcade_snake.so",
        "arcade_nibbler.so",
        "arcade_pacman.so",
        "arcade_qix.so",
        "arcade_centipede.so",
        "arcade_solarfox.so"
    };

    for (auto &lib : libList) {
        bool isLib = false;
        if (activeLib.find(lib) != std::string::npos)
            isLib = true;
        if (std::find(autorisedLibs.begin(), autorisedLibs.end(), lib) != autorisedLibs.end())
            _menuGraphic.push_back(std::make_pair(lib, isLib));
    }

    for (auto &game : gameList) {
        if (std::find(autorisedGames.begin(), autorisedGames.end(), game) != autorisedGames.end())
            _menuGames.push_back(std::make_pair(game, false));
    }
}

Core::~Core()
{
}

static void selectNext(std::vector<std::pair<std::string, bool>> &menu)
{
    for (auto &item : menu) {
        if (item.second) {
            item.second = false;
            if (item.first != menu.back().first) {
                menu[&item - &menu[0] + 1].second = true;
                break;
            } else {
                menu[0].second = true;
                break;
            }
        }
    }
}

void Core::menuState(std::string activeLib)
{
    if (_menuGames.size() == 0 || _menuGraphic.size() == 0)
        throw std::runtime_error("No lib or game found");
    _menuGames[0].second = true;

    while (_lib->isOpen()) {
        _lib->drawMenu(_menuGraphic, _menuGames);
        
        std::string input = _lib->getEvent();
        if (input == "Z") {
            selectNext(_menuGraphic);
        } else if (input == "S") {
            selectNext(_menuGames);
        } else if (input == " ") {
            for (auto &item : _menuGraphic) {
                if (item.second) {
                    _lib.reset();
                    loadLib("./lib/" + item.first);
                    break;
                }
            }
            for (auto &item : _menuGames) {
                if (item.second) {
                    loadGame("./lib/" + item.first);
                    break;
                }
            }
            _inMenu = false;
            break;
        }
    }
}

static void saveScore(std::string name, int score)
{
    std::ofstream file;
    file.open("score.txt", std::ios::app);
    file << name << " " << score << std::endl;
    file.close();
}

void Core::update()
{
    std::string switchlib = _lib->getEvent();
    if (switchlib == "L") {
        _lib.reset();
        _libDL.reset();
        selectNext(_menuGraphic);
        for (auto &item : _menuGraphic) {
            if (item.second) {
                loadLib("./lib/" + item.first);
                break;
            }
        }
    } else if (switchlib == "M") {
        _game.reset();
        _gameDL.reset();
        for (auto &item : _menuGames) {
            if (item.second) {
                loadGame("./lib/" + item.first);
                break;
            }
        }
    }
    _game->setEvent(switchlib);
    _game->update();
    if (_game == nullptr)
        throw std::runtime_error("No game loaded");
    _lib->setAsset(_game->getAssets());
    _lib->setMap(_game->getMap());
    _lib->draw();
    if (_game->leaveGame()) {
        saveScore(_playerName, _game->getScore());
        _game.reset();
        _gameDL.reset();
        _inMenu = true;
        for (auto &item : _menuGames) {
            item.second = false;
        }
        _menuGames[0].second = true;
    }
    if (switchlib == "P") {
        saveScore(_playerName, _game->getScore());
        _game.reset();
        _gameDL.reset();
        _inMenu = true;
        for (auto &item : _menuGames) {
            item.second = false;
        }
        _menuGames[0].second = true;
    } else if (switchlib == "I") {
        _leave = true;
    }
}

void Core::event(std::string event)
{
}

static void checkGame(const std::string &name)
{
    std::string command = "nm " + name + " | grep ";
    std::string function[] = {"update", "getMap", "getAssets", "setEvent", "leaveGame", "getScore"};
    for (auto &func : function)
        if (System::SystemExec(command + func + " > /dev/null") != 0) 
            throw std::runtime_error("dont't even try to cringe a game for crash arcade ..., you will not succeed, go back read docs !");
}

void Core::loadGame(std::string gameName)
{
    static const std::vector<std::string> autorisedGames = {
        "arcade_snake.so",
        "arcade_nibbler.so",
        "arcade_pacman.so",
        "arcade_qix.so",
        "arcade_centipede.so",
        "arcade_solarfox.so"
    };
    std::string gameCheck = gameName.substr(gameName.find_last_of("/") + 1);
    if (std::find(autorisedGames.begin(), autorisedGames.end(), gameCheck) == autorisedGames.end())
        throw std::runtime_error("Game not autorised");
    checkGame(gameName);
    _gameDL.reset();
    this->_gameDL = std::make_shared<dl>("./" + gameName);
        
    
    this->_dlCreateGame = (std::shared_ptr<IGames> (*)()) _gameDL->getSym("create");
    _game = _dlCreateGame();
}

static void checkLib(const std::string &name)
{
    std::string command = "nm " + name + " | grep ";
    std::string function[] = {"setAsset", "setMap", "draw", "isOpen", "getEvent", "drawMenu"};
    for (auto &func : function)
        if (System::SystemExec(command + func + " > /dev/null") != 0) 
            throw std::runtime_error("dont't even try to rename a lib to game for crash arcade ..., you will not succeed but plz don't try ;()");
}

void Core::loadLib(std::string libName)
{
    static const std::vector<std::string> autorisedLibs = {
        "arcade_ndk++.so",
        "arcade_aalib.so",
        "arcade_libcaca.so",
        "arcade_allegro5.so",
        "arcade_xlib.so",
        "arcade_gtk+.so",
        "arcade_sfml.so",
        "arcade_irrlicht.so",
        "arcade_opengl.so",
        "arcade_vulkan.so",
        "arcade_qt5.so",
        "arcade_sdl2.so",
        "arcade_ncurses.so"
    };
    // remove all char after the last / of the string libName
    std::string libCheck = libName.substr(libName.find_last_of("/") + 1);
    if (std::find(autorisedLibs.begin(), autorisedLibs.end(), libCheck) == autorisedLibs.end())
        throw std::runtime_error("did you try to load a lib but it's a game ... ?");

    checkLib(libName);
    _libDL.reset();
    this->_libDL = std::make_shared<dl>("./" + libName);
        
    
    this->_dlCreateLib = (std::shared_ptr<ILib> (*)()) _libDL->getSym("create");
    _lib = _dlCreateLib();
}