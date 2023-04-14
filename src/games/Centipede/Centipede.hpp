/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** Snake
*/

#pragma once

#include <stdio.h>
#include "../IGames.hpp"
#include "../../core/Engine/Vector2/Vector2.hpp"

class Centipede final : public IGames {
    public:
        Centipede();
        ~Centipede() override;

        void update() override;
        std::vector<std::string> getMap() const override {return _map;};
        std::map<char, std::string> getAssets() const override {return _assets;};
        void setEvent(std::string string) override;
        int getScore() const override {return _score;};

        //MAP
        void create_map(void);
        void add_obstacles(void);
        void update_map(void);
        
        //MOVES
        void move_map(int, int);
        void move_player(std::string);

        //PROJECTILE
        void shoot_projectile(std::string);
        void bullet_collision(void);

        //CENTIPEDES
        void add_snake(void);
        std::vector<Engine::Vector2<int>> move_snake(std::vector<Engine::Vector2<int>>, char, int);
        std::vector<Engine::Vector2<int>> snake_right(std::vector<Engine::Vector2<int>>, int);
        std::vector<Engine::Vector2<int>> snake_left(std::vector<Engine::Vector2<int>>, int);
        void snake_collision(void);
        void snake_split(int, int);
        std::vector<Engine::Vector2<int>> short_snake_head(int);
        std::vector<Engine::Vector2<int>> short_snake_tail(int);
        char which_head(int);
        int count_alive(void);

        //OBSTACLES
        void create_obstacle(Engine::Vector2<int>);
        void count_obstacles(void);

        void maybe_lose(void);
        bool leaveGame() const override{return _quit;};
    private:
        //MAP
        std::vector<std::string> _map;
        std::vector<std::string> _blank_map;
        int _map_x;
        int _map_y;

        //PLAYER
        Engine::Vector2<int> _player;
        int _score = 0;

        //BULLET
        Engine::Vector2<int> _bullet;
        bool _shooted;

        //CENTIPEDES
        std::vector<std::vector<Engine::Vector2<int>>> _snakes;
        std::vector<char> _snakes_direction;
        std::vector<bool> _snakes_alive;
        int _killed;

        //OBSTACLES
        std::vector<Engine::Vector2<int>>_obstacles_5;
        std::vector<Engine::Vector2<int>>_obstacles_4;
        std::vector<Engine::Vector2<int>>_obstacles_3;
        std::vector<Engine::Vector2<int>>_obstacles_2;
        std::vector<Engine::Vector2<int>>_obstacles_1;
        
        //CHRONO
        std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
        std::chrono::time_point<std::chrono::system_clock> starto = std::chrono::system_clock::now();

        std::map<char, std::string> _assets;
        std::string _saveLastEvent = "";

        bool _quit = false;
    protected:

};