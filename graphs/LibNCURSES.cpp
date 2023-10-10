/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** libNCURSES
*/

#include "LibNCURSES.hpp"
#include <cmath>

extern "C" ArcadeGraphs::Agraphs *createGraph()
{
    return new ArcadeGraphs::libNCURSES();
}

extern "C" void deleteGraph(ArcadeGraphs::Agraphs *graph)
{
    delete graph;
}

ArcadeGraphs::libNCURSES::libNCURSES()
{
    initscr();
    cbreak();
    wclear(stdscr);
    clear();
    curs_set(0);
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    // init pair RED, LIght RED
    init_pair(1, MY_RED, MY_RED);
    init_pair(2, MY_LIGHT_RED, MY_LIGHT_RED);
    init_color(MY_RED, 1000, 0, 0);
    init_color(MY_LIGHT_RED, 1000, 400, 400);

    // init pair GREEN, LIGHT GREEN
    init_pair(3, MY_GREEN, MY_GREEN);
    init_pair(4, MY_LIGHT_GREEN, MY_LIGHT_GREEN);
    init_color(MY_GREEN, 0, 800, 0);
    init_color(MY_LIGHT_GREEN, 0, 1000, 0);

    // init pair YELLOW, LIGHT YELLOW
    init_pair(5, MY_YELLOW, MY_YELLOW);
    init_pair(6, MY_LIGHT_YELLOW, MY_LIGHT_YELLOW);
    init_color(MY_YELLOW, 1000, 1000, 0);
    init_color(MY_LIGHT_YELLOW, 1000, 1000, 400);

    // init pair BLUE, LIGHT BLUE
    init_pair(7, MY_BLUE, MY_BLUE);
    init_pair(8, MY_LIGHT_BLUE, MY_LIGHT_BLUE);
    init_color(MY_BLUE, 0, 0, 1000);
    init_color(MY_LIGHT_BLUE, 400, 400, 1000);

    // init pair MAGENTA, LIGHT MAGENTA
    init_pair(9, MY_MAGENTA, MY_MAGENTA);
    init_pair(10, MY_LIGHT_MAGENTA, MY_LIGHT_MAGENTA);
    init_color(MY_MAGENTA, 1000, 0, 1000);
    init_color(MY_LIGHT_MAGENTA, 1000, 400, 1000);

    // init pair CYAN, LIGHT CYAN
    init_pair(11, MY_CYAN, MY_CYAN);
    init_pair(12, MY_LIGHT_CYAN, MY_LIGHT_CYAN);
    init_color(MY_CYAN, 0, 1000, 1000);
    init_color(MY_LIGHT_CYAN, 400, 1000, 1000);

    // init pair WHITE, LIGHT WHITE
    init_pair(13, MY_WHITE, MY_WHITE);
    init_color(MY_WHITE, 1000, 1000, 1000);

    // init pair BLACK_RED
    init_pair(14, MY_RED, COLOR_BLACK);

    // init pair BLACK_GREEN
    init_pair(15, MY_GREEN, COLOR_BLACK);

    // init pair BLACK_YELLOW
    init_pair(16, MY_YELLOW, COLOR_BLACK);

    // init pair BLACK_BLUE
    init_pair(17, MY_BLUE, COLOR_BLACK);

    // init pair BLACK_MAGENTA
    init_pair(18, MY_MAGENTA, COLOR_BLACK);

    // init pair BLACK_CYAN
    init_pair(19,MY_CYAN, COLOR_BLACK);

    // init pair BLACK_WHITE
    init_pair(20, MY_WHITE, COLOR_BLACK);
}

ArcadeGraphs::libNCURSES::~libNCURSES()
{
    clear();
    wclear(stdscr);
    endwin();
}

void ArcadeGraphs::libNCURSES::drawText(const std::string &text, int x, int y, MyColor cl)
{
    attron(COLOR_PAIR(cl));
    y /= 10;
    x /= 10;
    mvprintw(y, x, text.c_str(),"%s");
    attroff(COLOR_PAIR(cl));
}

void ArcadeGraphs::libNCURSES::checkEvent()
{
    _inputV.clear();
    while (1) {
        int key = getch();
        if (key == 263) {
            _inputV.push_back(Input::CLOSE);
            break;
        }
        if (key == 27) {
            _inputV.push_back(Input::ESCAPE);
            break;
        }
        if (key == 10) {
            _inputV.push_back(Input::ENTER);
            break;
        }
        if (key == 259) {
            _inputV.push_back(Input::UP_ARROW);
            break;
        }
        if (key == 258) {
            _inputV.push_back(Input::DOWN_ARROW);
            break;
        }
        if (key == 261) {
            _inputV.push_back(Input::RIGHT_ARROW);
            break;
        }
        if (key == 260) {
            _inputV.push_back(Input::LEFT_ARROW);
            break;
        }
        if (key == 38) {
            _inputV.push_back(Input::KEY_1);
            break;
        }
        if (key == 195) {
            _inputV.push_back(Input::KEY_2);
            break;
        } else {
            _inputV.push_back(Input::NO_INPUT);
            break;
        }
    }
    _inputV.push_back(Input::NO_INPUT);
}

void ArcadeGraphs::libNCURSES::refreshGraph(int to_sleep)
{
    refresh();
    clear();
    usleep(to_sleep);
    wrefresh(stdscr);
}

void ArcadeGraphs::libNCURSES::drawMap(int x, int y, std::vector<std::string> map)
{
    int i = 0;
    int j = 0;
    for (auto &line : map) {
        for (auto &c : line) {
            drawText(std::string(1, c), x + (j * 10), y + (i * 10), std::get<1>(_color[c]));
            j++;
        }
        j = 0;
        i++;
    }
}

void ArcadeGraphs::libNCURSES::setColor(std::map<char, std::tuple<std::string, MyColor>> color)
{
    _color = color;
}
