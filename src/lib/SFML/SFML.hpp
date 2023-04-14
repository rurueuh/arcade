/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** SFML
*/

#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../ILib.hpp"

class SFML final : public ILib {
    public:
        SFML();
        ~SFML();

        void setAsset(std::map<char, std::string> asset) override;
        void setMap(std::vector<std::string> map) override;
        void draw() override;

        bool isOpen() override { return _window.isOpen();}

        std::string getEvent() override;
        void drawMenu(std::vector<std::pair<std::string, bool>> &menuGraphic, std::vector<std::pair<std::string, bool>> &menuGames) override;

        void setScore(std::string name) override { (void)name; }

    protected:
    private:
        static int getScore(const std::string& s);
        static bool compareScore(const std::string& s1, const std::string& s2);
        sf::RenderWindow _window;
        std::map<char, std::string> _asset;
        std::map<char, std::pair<sf::Sprite, std::shared_ptr<sf::Texture>>> _mapSprite;
        void loadAsset();
        std::vector<std::string> _map;
        void drawHighscore();
};
