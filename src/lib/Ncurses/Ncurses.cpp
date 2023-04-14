/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** Ncurses
*/

#include "Ncurses.hpp"
#include <unistd.h>

Ncurses::Ncurses()
{
    initscr();
    cbreak();
    clear();
    start_color();
    noecho();
    mousemask(ALL_MOUSE_EVENTS, NULL);
    keypad(stdscr, TRUE);
    nodelay(stdscr, true);
}

Ncurses::~Ncurses()
{
    reset_shell_mode();
    _isOpen = false;
}

void Ncurses::setMap(std::vector<std::string> map)
{
    _map = map;
}

void Ncurses::draw()
{
    int x = 0;
    for (auto i : _map) {
        mvprintw(LINES / 2 - _map.size() / 2 + x, COLS / 2 - i.size() / 2, i.c_str());
        x++;
    }
}

std::string Ncurses::getEvent()
{
    int key = getch();
    switch (key) {
        case KEY_MOUSE:
            MEVENT event;
            if (getmouse(&event) == OK && event.bstate && BUTTON1_PRESSED) {
                int color_pair = rand() % 8 + 1;
                int foreground_color = rand() % 8 + 1;
                int background_color = rand() % 8 + 1;

                init_pair(color_pair, foreground_color, background_color);

                bkgd(COLOR_PAIR(color_pair));
                clear();
            }
        case -1:
            return "";
        case KEY_UP:
        case 'z':
            return "Z";
        case KEY_DOWN:
        case 's':
            return "S";
        case KEY_LEFT:
        case 'q':
            return "Q";
        case KEY_RIGHT:
        case 'd':
            return "D";
        case ' ':
            return " ";
        case 'l':
            return "L";
        case 'm':
            return "M";
        case 'p':
            return "P";
        case 'i':
            return "I";
        default:
            return "";
        
    }
}

bool Ncurses::isOpen()
{
    return _isOpen;
}

void Ncurses::drawMenu(std::vector<std::pair<std::string, bool>> &menuGraphic, std::vector<std::pair<std::string, bool>> &menuGames)
{
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int column_width = max_x / 2;

    for (int i = 0; i < menuGames.size(); i++)
    {
        std::string text = menuGames[i].first;
        bool selected = menuGames[i].second;
        attron(selected ? A_REVERSE : A_NORMAL);
        mvprintw(i, 0, "%-*s", column_width, text.c_str());
        attroff(selected ? A_REVERSE : A_NORMAL);
    }
    for (int i = 0; i < menuGraphic.size(); i++)
    {
        std::string text = menuGraphic[i].first;
        bool selected = menuGraphic[i].second;
        attron(selected ? A_REVERSE : A_NORMAL);
        mvprintw(i, column_width, "%-*s", column_width, text.c_str());
        attroff(selected ? A_REVERSE : A_NORMAL);
    }
    refresh();
    erase();
    // wait 1 second
    usleep(100000);

}

extern "C" std::shared_ptr<ILib> create()
{
    return std::make_shared<Ncurses>();
}