/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** Dir
*/

#include "Dir.hpp"

Dir::Dir()
{
}

Dir::~Dir()
{
    if (_isOpen)
        closedir(dir);
}

void Dir::open(std::string path)
{
    if ((dir = opendir(path.c_str())) != NULL) {
        _isOpen = true;
    } else {
        throw std::runtime_error("Can't open folder");
    }
}

std::vector<std::string> Dir::getFile()
{
    std::vector<std::string> callback;
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_name[0] != '.')
            callback.push_back(ent->d_name);
    }
    return callback;
}
