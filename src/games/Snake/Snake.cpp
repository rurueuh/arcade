/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** Snake
*/

#include "Snake.hpp"

static std::map<char, std::string> create_assets() {
    std::map<char, std::string> assets = {
        {' ', "assets/ground.png"},
        {'B', "assets/head_bot.png"},
        {'L', "assets/head_left.png"},
        {'R', "assets/head_right.png"},
        {'T', "assets/head_top.png"},
        {'N', "assets/body.png"},
        {'o', "assets/item.png"},
        {'X', "assets/wall.png"}
    };
    return assets;
}

Snake::Snake()
{  
    _map_size = {12, 12};
    _direction = "B";
    _snake_length = 4;
    create_map();
    update_map();
    _assets = create_assets();
    _score = 0;
    _speed_boost = 0;
    _quit = false;
}

Snake::~Snake()
{
}

void Snake::add_player(void)
{
    bool isEven = (_map.size() % 2 == 0);
    int midLine = _map.size() / 2;
    int lineNum = 0;

    for (int i = 0; i != _map_size.getX(); i++) {
        if (lineNum == midLine) {
            int middleIndex = (_map.at(i).size() - 2) / 2 ;
            _map.at(i).insert(middleIndex, "NP");
            _map.at(i).erase(_map_size.getX() - 2, 2);
        } else if (isEven && lineNum == midLine - 1) {
            int middleIndex = (_map.at(i).size() - 2) / 2;
            _map.at(i).insert(middleIndex, "NN");
            _map.at(i).erase(_map_size.getX() - 2, 2);
        }
        lineNum++;
    }
    _player.push_back({(_map_size.getX() / 2), (_map_size.getY() / 2)});
    _player.push_back({(_map_size.getX() / 2), (_map_size.getY() / 2) - 1});
    _player.push_back({(_map_size.getX() / 2) - 1, (_map_size.getY() / 2) - 1});
    _player.push_back({(_map_size.getX() / 2) - 1, (_map_size.getY() / 2)});
}

void Snake::create_map(void)
{
    _map.push_back({"XXXXXXXXXXXX"});
    for (int i = 0; i != _map_size.getX() - 2; i++)
        _map.push_back({"X          X"});
    _map.push_back({"XXXXXXXXXXXX"});
    _blank_map = _map;
    add_player();
    add_item();
}

void Snake::add_item(void)
{
    int x = random() % (_map_size.getX() - 1);
    int y = random() % (_map_size.getX() - 1);

    if (_map.at(y).at(x) == ' ') {
        _map.at(y).at(x) = 'o';
        _item.setX(x);
        _item.setY(y);
    } else
        return add_item();
}

void Snake::move_bot(void)
{
    int tmp = _player.at(0).getY();

    _last_move = _player.at(_snake_length - 1);
    for (int i = _snake_length - 1; i != 0; i--)
        _player.at(i) = _player.at(i - 1);
    _player.at(0).setY(tmp + 1);
    _direction = "B";
}

void Snake::move_right(void)
{
    int tmp = _player.at(0).getX();

    _last_move = _player.at(_snake_length - 1);
    for (int i = _snake_length - 1; i != 0; i--)
        _player.at(i) = _player.at(i - 1);
    _player.at(0).setX(tmp + 1);
    _direction = "R";
}

void Snake::move_top(void)
{
    int tmp = _player.at(0).getY();

    _last_move = _player.at(_snake_length - 1);
    for (int i = _snake_length - 1; i != 0; i--)
        _player.at(i) = _player.at(i - 1);
    _player.at(0).setY(tmp - 1);
    _direction = "T";
}

void Snake::move_left(void)
{
    int tmp = _player.at(0).getX();

    _last_move = _player.at(_snake_length - 1);
    for (int i = _snake_length - 1; i != 0; i--)
        _player.at(i) = _player.at(i - 1);
    _player.at(0).setX(tmp - 1);
    _direction = "L";
}

void Snake::move_player(void)
{
    if (_current_direction == "S" && _direction != "T")
        return move_bot();
    else if (_current_direction == "D"  && _direction != "L")
        return move_right();
    else if (_current_direction == "Z"  && _direction != "B")
        return move_top();
    else if (_current_direction == "Q"  && _direction != "R")
        return move_left();
    if (_direction == "B")
        return move_bot();
    else if (_direction == "R")
        return move_right();
    else if (_direction == "T")
        return move_top();
    else if (_direction == "L")
        return move_left();
}

void Snake::update_map(void)
{
    take_item();
    _map = _blank_map;
    _map.at(_player.at(0).getY()).replace(_player.at(0).getX(), 1, _direction);
    for (int i = 1; i != _snake_length; i++)
        _map.at(_player.at(i).getY()).replace(_player.at(i).getX(), 1, "N");
    _map.at(_item.getY()).replace(_item.getX(), 1, "o");
    move_wall();
}

void Snake::take_item(void)
{
    if (_player.at(0) != _item)
        return;
    _player.push_back(_last_move);
    _snake_length++;
    _score++;
    add_item();
}

void Snake::loose_game(void)
{
    std::cout << "GAME OVER" << std::endl;
    std::cout << "SPEED : " << _speed_boost + 1 << std::endl;
    std::cout << "APPLES EATEN : " << _score << std::endl;
    std::cout << "TOTAL SCORE : " << _score * (_speed_boost + 1) / 2 << std::endl;
    _quit = true;
}

void Snake::move_wall(void)
{
    if (_player.at(0).getX() == 0)
        loose_game();
    else if (_player.at(0).getY() == 0)
        loose_game();
    else if (_player.at(0).getX() == _map_size.getX() - 1)
        loose_game();
    else if (_player.at(0).getY() == _map_size.getY() - 1)
        loose_game();
    for (int i = 1; i != _snake_length; i++)
        if (_player.at(0) == _player.at(i))
            loose_game();
    return;
}

void Snake::speed_booster(void)
{
    if (_current_direction == " ")
        _speed_boost++;
}

void Snake::update()
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - starto).count() > 500 - (_score * 10) - (_speed_boost * 10)) {
        speed_booster();
        move_player();
        update_map();
        starto = std::chrono::system_clock::now();
    }
}

void Snake::setEvent(std::string event)
{
    if (event == "")
        return;
    _current_direction = event;
}

extern "C" std::shared_ptr<IGames> create()
{
    return std::make_shared<Snake>();
}
