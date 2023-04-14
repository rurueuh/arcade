/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** IGames
*/

#pragma once

#include <bits/stdc++.h>

class IGames {
    public:
        IGames() = default;
        virtual ~IGames() = default;

        virtual void update() = 0;

        virtual std::vector<std::string> getMap() const = 0;
        virtual std::map<char, std::string> getAssets() const = 0;

        virtual void setEvent(std::string string) = 0;

        virtual bool leaveGame() const = 0;
        virtual int getScore() const = 0;

    protected:
    private:
};
