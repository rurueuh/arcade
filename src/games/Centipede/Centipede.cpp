/*
** EPITECH PROJECT, 2023
** CENtip
** File description:
** CENTIP
*/

#include "Centipede.hpp"

static std::map<char, std::string> create_assets() {
    std::map<char, std::string> assets = {
        {' ', "assets/ground.png"},
        {'P', "assets/player.png"},
        {'5', "assets/obstacles_5.png"},
        {'4', "assets/obstacles_4.png"},
        {'3', "assets/obstacles_3.png"},
        {'2', "assets/obstacles_2.png"},
        {'1', "assets/obstacles_1.png"},
        {'B', "assets/body.png"},
        {'T', "assets/body.png"},
        {'R', "assets/head_right.png"},
        {'L', "assets/head_left.png"},
        {'|', "assets/bullet.png"},
        {'X', "assets/wall.png"}
    };
    return assets;
}

Centipede::Centipede()
{
    _map_y = 31;
    _map_x = 31;
    create_map();
    add_snake();
    _killed = 0;
    _player = {16, 30};
    _shooted = false;
    _score = 0;
    _assets = create_assets();
}

Centipede::~Centipede()
{
    _map = _blank_map;
    _player = {0,0};
    _bullet = {0,0};
    _shooted = false;
    _snakes.clear();
    _snakes_direction.clear();
    _snakes_alive.clear();
    _killed = 0;
}

void Centipede::update()
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - starto).count() > 75) {
        update_map();
        move_player(_saveLastEvent);
        _saveLastEvent = "";
        starto = std::chrono::system_clock::now();
    }
}

void Centipede::setEvent(std::string event)
{
    if (event == "")
        return;
    _saveLastEvent = event;
    shoot_projectile(event);
}

extern "C" std::shared_ptr<IGames> create()
{
    return std::make_shared<Centipede>();
}

void Centipede::create_map(void)
{
    for (int i = 0; i != _map_y - 1; i++)
        _map.push_back({"X                              X"});
    _blank_map = _map;
    _map.push_back({"X               P              X"});
    _map.push_back({"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"});
    _blank_map.push_back({"X                              X"});
    _blank_map.push_back({"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"});
    add_obstacles();
}

void Centipede::count_obstacles(void)
{
    for (int i = 0; i != _map_y; i++) {
        for (int o = 0; o != _map_x; o++) {
            if (_map.at(i).at(o) == '5')
                _obstacles_5.push_back({i,o});
            if (_map.at(i).at(o) == '4')
                _obstacles_4.push_back({i,o});
            if (_map.at(i).at(o) == '3')
                _obstacles_3.push_back({i,o});
            if (_map.at(i).at(o) == '2')
                _obstacles_2.push_back({i,o});
            if (_map.at(i).at(o) == '1')
                _obstacles_1.push_back({i,o});
        }
    }
}

void Centipede::add_obstacles(void)
{
    int randtmp = 0;
    int howmany = 0;

    for (int i = 3; i != _map_y - 1; i++) {
        howmany = (random() % 2) + 1;
        for (int o = 0; o != howmany; o++) {
            randtmp = random() % 30;
            _map.at(i).at(randtmp + 1) = '5';
        }
    }
    count_obstacles();
}

void Centipede::move_map(int x, int y)
{
    int tmpx = _player.getX();
    int tmpy = _player.getY();

    if (tmpy + y == _map_y - 7 && y < 0)
        return;
    if (_map.at(_player.getY() + y).at(_player.getX() + x) == ' ' || _map.at(_player.getY() + y).at(_player.getX() + x) == 'T'
        || _map.at(_player.getY() + y).at(_player.getX() + x) == 'L' || _map.at(_player.getY() + y).at(_player.getX() + x) == 'B'
        || _map.at(_player.getY() + y).at(_player.getX() + x) == 'R') {
        _player.setX(tmpx + x);
        _player.setY(tmpy + y);
        }
}

void Centipede::move_player(std::string direction)
{
    if (direction == "Q")
        move_map(-1, 0);
    if (direction == "D")
        move_map(1, 0);
    if (direction == "Z")
        move_map(0, -1);
    if (direction == "S")
        move_map(0, 1);
}

void Centipede::bullet_collision(void)
{
    if (_bullet.getY() < 1) {
        _shooted = false;
        _bullet = {0,0};
        return;
    }
    if (_map.at(_bullet.getY()).at(_bullet.getX()) == ' ' 
        || _map.at(_bullet.getY()).at(_bullet.getX()) == 'P') {
        return;
    } else if (_map.at(_bullet.getY()).at(_bullet.getX()) == 'X') {
        _shooted = false;
        _bullet = {0,0};
    } else if (_map.at(_bullet.getY()).at(_bullet.getX()) == '5') {
        for (int i = 0; i != _obstacles_5.size(); i++)
            if (_bullet.getX() == _obstacles_5.at(i).getY() && _bullet.getY() == _obstacles_5.at(i).getX()) {
                _obstacles_4.push_back(_obstacles_5.at(i));
                _obstacles_5.erase(_obstacles_5.begin() + i);
                _shooted = false;
                _bullet = {0,0};
                return;
            }
    } else if (_map.at(_bullet.getY()).at(_bullet.getX()) == '4') {
        for (int i = 0; i != _obstacles_4.size(); i++)
            if (_bullet.getX() == _obstacles_4.at(i).getY() && _bullet.getY() == _obstacles_4.at(i).getX()) {
                _obstacles_3.push_back(_obstacles_4.at(i));
                _obstacles_4.erase(_obstacles_4.begin() + i);
                _shooted = false;
                _bullet = {0,0};
                return;
            }
    } else if (_map.at(_bullet.getY()).at(_bullet.getX()) == '3') {
        for (int i = 0; i != _obstacles_3.size(); i++)
            if (_bullet.getX() == _obstacles_3.at(i).getY() && _bullet.getY() == _obstacles_3.at(i).getX()) {
                _obstacles_2.push_back(_obstacles_3.at(i));
                _obstacles_3.erase(_obstacles_3.begin() + i);
                _shooted = false;
                _bullet = {0,0};
                return;
            }
    } else if (_map.at(_bullet.getY()).at(_bullet.getX()) == '2') {
        for (int i = 0; i != _obstacles_2.size(); i++)
            if (_bullet.getX() == _obstacles_2.at(i).getY() && _bullet.getY() == _obstacles_2.at(i).getX()) {
                _obstacles_1.push_back(_obstacles_2.at(i));
                _obstacles_2.erase(_obstacles_2.begin() + i);
                _shooted = false;
                _bullet = {0,0};
                return;
            }
    } else if (_map.at(_bullet.getY()).at(_bullet.getX()) == '1') {
        for (int i = 0; i != _obstacles_1.size(); i++)
            if (_bullet.getX() == _obstacles_1.at(i).getY() && _bullet.getY() == _obstacles_1.at(i).getX()) {
                _obstacles_1.erase(_obstacles_1.begin() + i);
                _score++;
                _shooted = false;
                _bullet = {0,0};
                return;
            }
    } else if (_map.at(_bullet.getY()).at(_bullet.getX()) == 'L' ||_map.at(_bullet.getY()).at(_bullet.getX()) == 'R') {
        for (int i = 0; i != _snakes.size(); i++) {
            if (_snakes.at(i).at(0).getX() == _bullet.getX() && _snakes.at(i).at(0).getY() == _bullet.getY()) {
                if (_snakes.at(i).size() != 1) {
                    _snakes.at(i) = short_snake_head(i);
                    create_obstacle(_bullet);
                    return;
                } else {
                    _snakes_alive.at(i) = false;
                    create_obstacle(_bullet);
                    _killed++;
                    add_snake();
                }
            }
            if (_snakes.at(i).at(0).getX() == _bullet.getX() - 1 && _snakes.at(i).at(0).getY() == _bullet.getY()) {
                if (_snakes.at(i).size() != 1) {
                    _snakes.at(i) = short_snake_head(i);
                    create_obstacle(_bullet - (Engine::Vector2<int>){1, 0});
                    return;
                } else {
                    _snakes_alive.at(i) = false;
                    create_obstacle(_bullet - (Engine::Vector2<int>){1, 0});
                    _killed++;
                    add_snake();
                }
            }
            if (_snakes.at(i).at(0).getX() == _bullet.getX() + 1 && _snakes.at(i).at(0).getY() == _bullet.getY()) {
                if (_snakes.at(i).size() != 1) {
                    _snakes.at(i) = short_snake_head(i);
                    create_obstacle(_bullet - (Engine::Vector2<int>){1, 0});
                    return;
                } else {
                    _snakes_alive.at(i) = false;
                    create_obstacle(_bullet - (Engine::Vector2<int>){1, 0});
                    _killed++;
                    add_snake();
                }
            }
            if (_snakes.at(i).at(0).getX() == _bullet.getX() && _snakes.at(i).at(0).getY() + 1== _bullet.getY()) {
                if (_snakes.at(i).size() != 1) {
                    _snakes.at(i) = short_snake_head(i);
                    create_obstacle(_bullet - (Engine::Vector2<int>){1, 0});
                    return;
                } else {
                    _snakes_alive.at(i) = false;
                    create_obstacle(_bullet - (Engine::Vector2<int>){1, 0});
                    _killed++;
                    add_snake();
                }
            }
            if (_snakes.at(i).at(0).getX() == _bullet.getX() + 1 && _snakes.at(i).at(0).getY() + 1 == _bullet.getY()) {
                if (_snakes.at(i).size() != 1) {
                    _snakes.at(i) = short_snake_head(i);
                    create_obstacle(_bullet - (Engine::Vector2<int>){1, 0});
                    return;
                } else {
                    _snakes_alive.at(i) = false;
                    create_obstacle(_bullet - (Engine::Vector2<int>){1, 0});
                    _killed++;
                    add_snake();
                }
            }
            if (_snakes.at(i).at(0).getX() == _bullet.getX() - 1 && _snakes.at(i).at(0).getY() + 1 == _bullet.getY()) {
                if (_snakes.at(i).size() != 1) {
                    _snakes.at(i) = short_snake_head(i);
                    create_obstacle(_bullet - (Engine::Vector2<int>){1, 0});
                    return;
                } else {
                    _snakes_alive.at(i) = false;
                    create_obstacle(_bullet - (Engine::Vector2<int>){1, 0});
                    _killed++;
                    add_snake();
                }
            }
        }
    } else {
        snake_collision();
        _bullet = {0,0};
        _shooted = false;
    }
}

std::vector<Engine::Vector2<int>> Centipede::short_snake_head(int i) {
    std::vector<Engine::Vector2<int>> tmp;

    for (int o = 0; o != _snakes.at(i).size() - 1; o++)
        tmp.push_back(_snakes.at(i).at(o + 1));
    return tmp;
}

std::vector<Engine::Vector2<int>> Centipede::short_snake_tail(int i) {
    std::vector<Engine::Vector2<int>> tmp;

    for (int o = 0; o != _snakes.at(i).size() - 1; o++)
        tmp.push_back(_snakes.at(i).at(o));
    return tmp;
}

void Centipede::create_obstacle(Engine::Vector2<int> coords)
{
    Engine::Vector2<int> new_coords = {coords.getY(), coords.getX()};

    _obstacles_5.push_back(new_coords);
}

void Centipede::snake_collision(void)
{
    for (int i = 0; i != _snakes.size(); i++) {
        if (_snakes_alive.at(i) == true) {
            if (_snakes.at(i).at(_snakes.at(i).size() - 1) == _bullet) {
                if (_snakes.at(i).size() == 2) {
                    _snakes.at(i).erase(_snakes.at(i).begin() + 1);
                    create_obstacle(_snakes.at(i).at(_snakes.at(i).size() - 1));
                } else {
                    _snakes.at(i) = short_snake_tail(i);
                    create_obstacle(_snakes.at(i).at(_snakes.at(i).size() - 1));
                }
            } else
                for (int o = 0; o != _snakes.at(i).size(); o++)
                    if (_snakes.at(i).at(o) == _bullet) {
                        create_obstacle(_snakes.at(i).at(o));
                        snake_split(i, o);
                        return;
                    }
        }
    }
}

void Centipede::snake_split(int i, int o)
{
    std::vector<Engine::Vector2<int>> snake_1;
    std::vector<Engine::Vector2<int>> snake_2;
    std::vector<std::vector<Engine::Vector2<int>>> new_snakes;
    std::vector<char> new_dir;

    for (int p = 0; p != o; p++)
        snake_1.push_back(_snakes.at(i).at(p));
    for (int p = o + 1; p != _snakes.at(i).size(); p++)
        snake_2.push_back(_snakes.at(i).at(p));
    if (_snakes.size() == 1) {
        new_snakes.push_back(snake_1);
        new_snakes.push_back(snake_2);
        _snakes = new_snakes;
        _snakes_direction.push_back(_snakes_direction.at(0));
        _snakes_alive.push_back(true);
        return;
    } else {
        for (int p = 0; p != i; p++) {
            new_snakes.push_back(_snakes.at(p));
            new_dir.push_back(_snakes_direction.at(p));
        }
        for (int p = i + 1; p != _snakes.size(); p++) {
            new_snakes.push_back(_snakes.at(p));
            new_dir.push_back(_snakes_direction.at(p));
        }
        new_snakes.push_back(snake_1);
        new_snakes.push_back(snake_2);
        _snakes = new_snakes;
        new_dir.push_back(_snakes_direction.at(i));
        new_dir.push_back(_snakes_direction.at(i));
        _snakes_direction = new_dir;
        _snakes_alive.push_back(true);
        return;
    }
}

char Centipede::which_head(int i)
{
    if (_snakes_direction.at(i) == 'R')
        return 'R';
    else
        return 'L';
}

void Centipede::maybe_lose(void)
{
    for (int i = 0; i != _snakes.size(); i++)
        for (int o = 0; o != _snakes.at(i).size(); o++)
            if (_snakes.at(i).at(o) == _player){
                std::cout << "YOU LOSE" << std::endl;
                std::cout << "KILLED : " << _killed << std::endl;
                std::cout << "SCORE : " << _score << std::endl;
                _quit = true;
            }
}

void Centipede::update_map(void)
{
    for (int i = 0; i < _snakes.size(); i++)
        _snakes.at(i) = move_snake(_snakes.at(i), _snakes_direction.at(i), i);
    _bullet = {_bullet.getX(), _bullet.getY() - 1};
    bullet_collision();
    if (_killed == 20) { //WIN
        std::cout << "YOU WIN";
        std::cout << "KILLED : " << _killed << std::endl;
        std::cout << "SCORE : " << _score << std::endl;
        _quit = true;
    }
    if (count_alive() == 0)
        add_snake();
    _map = _blank_map;
    _map.at(_player.getY()).at(_player.getX()) = 'P';
    for (int i = 0; i != _snakes.size(); i++) {
        if (_snakes_alive.at(i) == true) {
            if (_snakes.at(i).size() != 1) {
                _map.at(_snakes.at(i).at(0).getY()).at(_snakes.at(i).at(0).getX()) = which_head(i);
                _map.at(_snakes.at(i).at(_snakes.at(i).size() - 1).getY()).at(_snakes.at(i).at(_snakes.at(i).size() - 1).getX()) = 'T';
                for (int o = 1; o < _snakes.at(i).size() - 1; o++)
                  _map.at(_snakes.at(i).at(o).getY()).at(_snakes.at(i).at(o).getX()) = 'B';
            } else
                _map.at(_snakes.at(i).at(0).getY()).at(_snakes.at(i).at(0).getX()) = which_head(i);
        }
    }
    maybe_lose();
    if (_bullet.getX() > 0 && _bullet.getY() > 0)
        if (_map.at(_bullet.getY()).at(_bullet.getX()) == ' ')
            _map.at(_bullet.getY()).at(_bullet.getX()) = '|';
    if (_obstacles_5.size() != 0)
        for (int i = 0; i != _obstacles_5.size(); i++)
            _map.at(_obstacles_5.at(i).getX()).at(_obstacles_5.at(i).getY()) = '5';
    if (_obstacles_4.size() != 0)
        for (int i = 0; i != _obstacles_4.size(); i++)
            _map.at(_obstacles_4.at(i).getX()).at(_obstacles_4.at(i).getY()) = '4';
    if (_obstacles_3.size() != 0)
        for (int i = 0; i != _obstacles_3.size(); i++)
            _map.at(_obstacles_3.at(i).getX()).at(_obstacles_3.at(i).getY()) = '3';
    if (_obstacles_2.size() != 0)
        for (int i = 0; i != _obstacles_2.size(); i++)
            _map.at(_obstacles_2.at(i).getX()).at(_obstacles_2.at(i).getY()) = '2';
    if (_obstacles_1.size() != 0)
        for (int i = 0; i != _obstacles_1.size(); i++)
            _map.at(_obstacles_1.at(i).getX()).at(_obstacles_1.at(i).getY()) = '1';
}

void Centipede::shoot_projectile(std::string input)
{
    if (input != " ")
        return;
    if (_shooted == true)
        return;
    _shooted = true;
    _bullet = {_player.getX(), _player.getY() + 1};
}

void Centipede::add_snake(void)
{
    Engine::Vector2<int> head(5,1);
    Engine::Vector2<int> body_1(4,1);
    Engine::Vector2<int> body_2(3,1);
    Engine::Vector2<int> body_3(2,1);
    Engine::Vector2<int> tail(1,1);
    std::vector<Engine::Vector2<int>> first;

    first.push_back(head);
    first.push_back(body_1);
    first.push_back(body_2);
    first.push_back(body_3);
    first.push_back(tail);
    _snakes.push_back(first);
    _snakes_direction.push_back('R');
    _snakes_alive.push_back(true);
}

int Centipede::count_alive() {
    int count = 0;

    for (int i = 0; i != _snakes_alive.size(); i++)
        if (_snakes_alive.at(i) == true)
            count++;
    return count;
}

std::vector<Engine::Vector2<int>> Centipede::snake_left(std::vector<Engine::Vector2<int>> snake, int i)
{
    for (int i = snake.size() - 1; i != 0; i--)
        snake.at(i) = snake.at(i - 1);
    if (_map.at(snake.at(0).getY()).at(snake.at(0).getX() - 1) == ' ')
        snake.at(0).setX(snake.at(0).getX() - 1);
    else if (_map.at(snake.at(0).getY()).at(snake.at(0).getX() - 1) == 'P')
        snake.at(0).setX(snake.at(0).getX() - 1);
    else if (_map.at(snake.at(0).getY()).at(snake.at(0).getX() - 1) == '|')
        snake.at(0).setX(snake.at(0).getX() - 1);
    else if ((_map.at(snake.at(0).getY()).at(snake.at(0).getX() - 1) == 'X' && snake.at(0).getY() + 1 == _map_y) ||
             (_map.at(snake.at(0).getY()).at(snake.at(0).getX() - 1) == 'R' && snake.at(0).getY() + 1 == _map_y) ||
             (_map.at(snake.at(0).getY()).at(snake.at(0).getX() - 1) == 'L' && snake.at(0).getY() + 1 == _map_y) ||
             (_map.at(snake.at(0).getY()).at(snake.at(0).getX() - 1) == 'T' && snake.at(0).getY() + 1 == _map_y) ||
             (_map.at(snake.at(0).getY()).at(snake.at(0).getX() - 1) == 'B' && snake.at(0).getY() + 1 == _map_y)) {
        if (count_alive() != 1) {
            _snakes_alive.at(i) = false;
            _score = _score - 10;
        } else {
            _snakes_alive.at(i) = false;
            _score = _score - 10;
            add_snake();
        }
    } else {
        snake.at(0).setY(snake.at(0).getY() + 1);
        _snakes_direction.at(i) = 'R';  
    }
    return snake;
}

std::vector<Engine::Vector2<int>> Centipede::snake_right(std::vector<Engine::Vector2<int>> snake, int i)
{
    for (int o = snake.size() - 1; o != 0; o--)
        snake.at(o) = snake.at(o - 1);
    if (_map.at(snake.at(0).getY()).at(snake.at(0).getX() + 1) == ' ')
        snake.at(0).setX(snake.at(0).getX() + 1);
    else if (_map.at(snake.at(0).getY()).at(snake.at(0).getX() + 1) == 'P')
        snake.at(0).setX(snake.at(0).getX() + 1);
    else if (_map.at(snake.at(0).getY()).at(snake.at(0).getX() + 1) == '|')
        snake.at(0).setX(snake.at(0).getX() + 1);
    else if ((_map.at(snake.at(0).getY()).at(snake.at(0).getX() + 1) == 'X' && snake.at(0).getY() + 1 == _map_y) ||
             (_map.at(snake.at(0).getY()).at(snake.at(0).getX() + 1) == 'R' && snake.at(0).getY() + 1 == _map_y) ||
             (_map.at(snake.at(0).getY()).at(snake.at(0).getX() + 1) == 'L' && snake.at(0).getY() + 1 == _map_y) ||
             (_map.at(snake.at(0).getY()).at(snake.at(0).getX() + 1) == 'T' && snake.at(0).getY() + 1 == _map_y) ||
             (_map.at(snake.at(0).getY()).at(snake.at(0).getX() + 1) == 'B' && snake.at(0).getY() + 1 == _map_y)) {
        if (count_alive() != 1) {
            _snakes_alive.at(i) = false;
            _score = _score - 10;
        } else {
            _snakes_alive.at(i) = false;
            _score = _score - 10;
            add_snake();
        }
    } else {
        snake.at(0).setY(snake.at(0).getY() + 1);
        _snakes_direction.at(i) = 'L';
    }
    return snake;
}

std::vector<Engine::Vector2<int>> Centipede::move_snake(std::vector<Engine::Vector2<int>> snake, char direction, int i)
{
    if (_snakes_alive.at(i) == false)
        return snake;
    if (direction == 'R')
        return snake_right(snake, i);
    else
        return snake_left(snake, i);
}
