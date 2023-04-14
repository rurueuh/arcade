/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** ILib
*/

#pragma once

#include <bits/stdc++.h>

class ILib {
    public:
        ILib() = default;
        virtual ~ILib() = default;

        virtual void setAsset(std::map<char, std::string> asset) = 0;
        virtual void setMap(std::vector<std::string> map) = 0;
        virtual void draw() = 0;

        virtual bool isOpen() = 0;

        virtual std::string getEvent() = 0;

        virtual void drawMenu(std::vector<std::pair<std::string, bool>> &menuGraphic, std::vector<std::pair<std::string, bool>> &menuGames) = 0;

        virtual void setScore(std::string name) = 0;
    protected:
    private:
};
