/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** dl
*/

#include "dl.hpp"

dl::dl(const std::string &path)
{
    std::string correctPath = path;
    if (path.size() < 3 || path.substr(0, 2) == "./") {
        correctPath.erase(0, 2);
    }
    std::ifstream test(correctPath);
    if (!test.good()) {
        throw Error("dl : File does not exist " + correctPath);
    }
    test.close();
    
    _path = correctPath;
    _handle = dlopen(correctPath.c_str(), RTLD_LAZY);
    if (!_handle) {
        throw Error(dlerror());
    }
}

dl::~dl()
{
    dlclose(_handle);
}

void *dl::getSym(const std::string &sym)
{
    void *ptr = dlsym(_handle, sym.c_str());
    if (!ptr) {
        throw Error(dlerror());
    }
    return ptr;
}

void *dl::getHandle() const
{
    return _handle;
}

void *dl::dlsym(void *handle, const char *symbol)
{
    return ::dlsym(handle, symbol);
}
