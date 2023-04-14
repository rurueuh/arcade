/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** Ncurses
*/

#pragma once

#include <bits/stdc++.h>
#include "../ILib.hpp"
#include <ncurses.h>

class Ncurses final : public ILib {
    public:
        Ncurses();
        ~Ncurses() override;


        bool isOpen() override;
        void setAsset(std::map<char, std::string> asset) override {};
        void setMap(std::vector<std::string> map) override;
        void draw() override;
        std::string getEvent() override;
        void drawMenu(std::vector<std::pair<std::string, bool>> &menuGraphic, std::vector<std::pair<std::string, bool>> &menuGames) override;

        void setScore(std::string name) override { (void)name; }
    protected:
    private:
        std::vector<std::string> _map;
        bool _isOpen = true;
};
