/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** SDL
*/

#pragma once

#include <bits/stdc++.h>
#include "../ILib.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


class SDL final : public ILib {
    public:
        SDL();
        ~SDL() override;

        bool isOpen() override;
        void setAsset(std::map<char, std::string> asset) override;
        void setMap(std::vector<std::string> map) override;
        void draw() override;

        std::string getEvent() override;

        void drawMenu(std::vector<std::pair<std::string, bool>> &menuGraphic, std::vector<std::pair<std::string, bool>> &menuGames) override;
        void setScore(std::string name) override { (void)name; }

    protected:
    private:

        void destroyWindow();
        void loadAssets();
        void clearWindow();
        void drawMap();
        void createWindow();
        void createRenderer();
        void drawMenuGraphic(std::vector<std::pair<std::string, bool>> &menuGraphic);
        void drawMenuGames(std::vector<std::pair<std::string, bool>> &menuGames);

        std::shared_ptr<SDL_Window> _window;
        std::shared_ptr<SDL_Renderer> _renderer;
        std::map<char, std::shared_ptr<SDL_Texture>> _mapSprite;
        std::map<char, std::string> _asset;
        std::vector<std::string> _map;
        bool _isOpen = true;
        std::shared_ptr<TTF_Font> _font;
};
