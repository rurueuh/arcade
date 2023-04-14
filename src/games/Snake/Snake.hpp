/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** Snake
*/

#pragma once

#include "../IGames.hpp"
#include "../../core/Engine/Vector2/Vector2.hpp"
#include <unistd.h>


class Snake final : public IGames {
    public:
        Snake();
        ~Snake() override;

        void update() override;

        std::vector<std::string> getMap() const override {return _map;};
        std::map<char, std::string> getAssets() const override {return _assets;};

        void setEvent(std::string string) override;
        bool leaveGame() const override {return _quit;};
        int getScore() const override {return _score;};

        //PLAYER
        void move_bot(void);
        void move_right(void);
        void move_top(void);
        void move_left(void);
        void move_player(void);
        void move_wall(void);
        void take_item(void);
        void speed_booster(void);

        //MAP
        void create_map(void);
        void add_player(void);
        void add_item(void);
        void update_map(void);

        //GAME
        void loose_game(void);
    private:
        std::map<char, std::string> _assets;

        //MAP
        Engine::Vector2<int> _map_size;
        std::vector<std::string> _blank_map;
        std::vector<std::string> _map;
        Engine::Vector2<int> _item;

        //PLAYER
        std::string _direction;
        std::string _current_direction;
        std::vector<Engine::Vector2<int>> _player;
        int _speed_boost;
        int _snake_length;
        Engine::Vector2<int>_last_move;
        int _score = 0;

        //CHRONO
        std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
        std::chrono::time_point<std::chrono::system_clock> starto = std::chrono::system_clock::now();

        bool _quit = false;
};
