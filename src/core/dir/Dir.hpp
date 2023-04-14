/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** Dir
*/

#pragma once

#include <bits/stdc++.h>
#include <dirent.h>

class Dir {
    public:
        Dir();
        ~Dir();

        void open(std::string path);

        std::vector<std::string> getFile();

    protected:
    private:
        DIR *dir;
        struct dirent *ent;
        bool _isOpen = false;

};
