/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** pacman
*/

#include "pacman.hpp"
#include <unistd.h>

extern "C" ArcadeGames::Agames *createGame()
{
    return new ArcadeGames::pacman();
}

extern "C" void deleteGame(ArcadeGames::Agames *game)
{
    delete game;
}

ArcadeGames::pacman::pacman()
{
    _map.push_back("###########################");
    _map.push_back("#S...........#...........S#");
    _map.push_back("#.####.#####.#.#####.####.#");
    _map.push_back("#.####.#####.#.#####.####.#");
    _map.push_back("#.........................#");
    _map.push_back("#.####.#.#########.#.####.#");
    _map.push_back("#......#.....#.....#......#");
    _map.push_back("######.#####.#.#####.######");
    _map.push_back("#CCCC#.#           #.#CCCC#");
    _map.push_back("######.# ###///### #.######");
    _map.push_back(" ......# #1 2 3 4# ....... ");
    _map.push_back("######.# ######### #.######");
    _map.push_back("#CCCC#.#           #.#CCCC#");
    _map.push_back("######.#.#########.#.######");
    _map.push_back("#............#............#");
    _map.push_back("#.####.#####.#.#####.####.#");
    _map.push_back("#....#.......U.......#....#");
    _map.push_back("####.#.#.#########.#.#.####");
    _map.push_back("#......#.....#.....#......#");
    _map.push_back("#.##########.#.##########.#");
    _map.push_back("#S.......................S#");
    _map.push_back("###########################");

    _clone = _map;

    srand(time(NULL));

    _animatelvl = false;
    _lvlTime = 0;
    _codeCouleur['#'] = std::make_tuple("./ressources/pacman/WallPacman.jpg", MyColor::MY_BLUE);
    _codeCouleur['.'] = std::make_tuple("./ressources/pacman/Point.jpg",MyColor::MY_BLACK_YELLOW);
    _codeCouleur[' '] = std::make_tuple("./ressources/pacman/Void.jpg", MyColor::MY_BLACK);
    _codeCouleur['1'] = std::make_tuple("./ressources/pacman/blueleft.jpg", MyColor::MY_CYAN);
    _codeCouleur['2'] = std::make_tuple("./ressources/pacman/orangeleft.jpg", MyColor::MY_LIGHT_YELLOW);
    _codeCouleur['3'] = std::make_tuple("./ressources/pacman/redright.jpg", MyColor::MY_RED);
    _codeCouleur['4'] = std::make_tuple("./ressources/pacman/pinkright.jpg", MyColor::MY_LIGHT_MAGENTA);
    _codeCouleur['U'] = std::make_tuple("./ressources/pacman/PacmanUp.jpg", MyColor::MY_YELLOW);
    _codeCouleur['D'] = std::make_tuple("./ressources/pacman/PacmanDown.jpg", MyColor::MY_YELLOW);
    _codeCouleur['L'] = std::make_tuple("./ressources/pacman/PacmanLeft.jpg", MyColor::MY_YELLOW);
    _codeCouleur['R'] = std::make_tuple("./ressources/pacman/PacmanRight.jpg", MyColor::MY_YELLOW);
    _codeCouleur['/'] = std::make_tuple("./ressources/pacman/Door.jpg", MyColor::MY_BLUE);
    _codeCouleur['C'] = std::make_tuple("./ressources/pacman/Void.jpg", MyColor::MY_BLACK);
    _codeCouleur['S'] = std::make_tuple("./ressources/pacman/Super.jpg", MyColor::MY_BLACK_WHITE);

    _pos.push_back({13, 16});
    _pos.push_back({10, 10});
    _pos.push_back({12, 10});
    _pos.push_back({14, 10});
    _pos.push_back({16, 10});

    for (int i = 0; i < 5; i++)
        _clone[_pos[i].y][_pos[i].x] = ' ';

    _ghmap = _clone;
    _info["Game"] = "Pacman";
    _info["Life"] = "3";
    _info["Score"] = "0";
    _info["Level"] = "1";

    _road.push_back(std::stack<Input>());
    _road.push_back(std::stack<Input>());
    _road.push_back(std::stack<Input>());
    _road.push_back(std::stack<Input>());
    _death.push_back(false);
    _death.push_back(false);
    _death.push_back(false);
    _death.push_back(false);
    _bef = Input::NO_INPUT;
    _aft = Input::NO_INPUT;
    _mouthOpen = false;
    _super = false;
    _start = -1;
    _time = 0;
}

ArcadeGames::pacman::~pacman() {}

bool ArcadeGames::pacman::move(Input i, int who)
{
    if (i == Input::Z_KEY || i == Input::UP_ARROW)
        return moveY(-1, who);
    if (i == Input::S_KEY || i == Input::DOWN_ARROW)
        return moveY(1, who);
    if (i == Input::Q_KEY || i == Input::LEFT_ARROW)
        return moveX(-1, who);
    if (i == Input::D_KEY || i == Input::RIGHT_ARROW)
        return moveX(1, who);
    return false;
}

void ArcadeGames::pacman::animate()
{
    if (_super) {
        for (int i = 1; i < 5; i++)
            if (_death[i - 1] == true)
                _codeCouleur[i + '0'] = std::make_tuple("./ressources/pacman/eyes.jpg", MyColor::MY_WHITE);
            else
                _codeCouleur[i + '0'] = std::make_tuple("./ressources/pacman/Dead.jpg", MyColor::MY_RED);
    } else {
        _codeCouleur['1'] = std::make_tuple("./ressources/pacman/blueleft.jpg", MyColor::MY_CYAN);
        _codeCouleur['2'] = std::make_tuple("./ressources/pacman/orangeleft.jpg", MyColor::MY_LIGHT_YELLOW);
        _codeCouleur['3'] = std::make_tuple("./ressources/pacman/redright.jpg", MyColor::MY_RED);
        _codeCouleur['4'] = std::make_tuple("./ressources/pacman/pinkright.jpg", MyColor::MY_LIGHT_MAGENTA);
    }
    if (!_mouthOpen) {
        _codeCouleur['U'] = std::make_tuple("./ressources/pacman/Pacman.jpg",MyColor::MY_YELLOW);
        _codeCouleur['D'] = std::make_tuple("./ressources/pacman/Pacman.jpg",MyColor::MY_YELLOW);
        _codeCouleur['L'] = std::make_tuple("./ressources/pacman/Pacman.jpg",MyColor::MY_YELLOW);
        _codeCouleur['R'] = std::make_tuple("./ressources/pacman/Pacman.jpg",MyColor::MY_YELLOW);
    } else {
        _codeCouleur['U'] = std::make_tuple("./ressources/pacman/PacmanUp.jpg",MyColor::MY_YELLOW);
        _codeCouleur['D'] = std::make_tuple("./ressources/pacman/PacmanDown.jpg",MyColor::MY_YELLOW);
        _codeCouleur['L'] = std::make_tuple("./ressources/pacman/PacmanLeft.jpg",MyColor::MY_YELLOW);
        _codeCouleur['R'] = std::make_tuple("./ressources/pacman/PacmanRight.jpg",MyColor::MY_YELLOW);
    }
    _mouthOpen = !_mouthOpen;
}

bool ArcadeGames::pacman::moveY(int mv, int w)
{
    if (w == 0 && _ghmap.at(_pos.at(w).y + mv).at(_pos.at(w).x) == '.') {
        _info["Score"] = std::to_string(std::stoi(_info["Score"]) + 10);
        _sounds.push_back("./ressources/pacman/pacman_chomp.wav");
    }
    if (w == 0 && _map.at(_pos.at(w).y + mv).at(_pos.at(w).x) == 'S') {
        _info["Score"] = std::to_string(std::stoi(_info["Score"]) + 10);
        _super = true;
        _start = _time;
    }
    if (_map.at(_pos.at(w).y + mv).at(_pos.at(w).x) != '#' &&
    (_map.at(_pos.at(w).y + mv).at(_pos.at(w).x) != '/' || w != 0 )) {
        if (w == 0) {
            _map.at(_pos.at(w).y).at(_pos.at(w).x) = ' ';
            _ghmap.at(_pos.at(w).y).at(_pos.at(w).x) = ' ';
            _pos.at(w).y += mv;
            if (mv > 0) {
                _map.at(_pos.at(w).y).at(_pos.at(w).x) = 'D';
                _bef = Input::S_KEY;
            } else {
                _map.at(_pos.at(w).y).at(_pos.at(w).x) = 'U';
                _bef = Input::Z_KEY;
            }
        } else {
            _map.at(_pos.at(w).y).at(_pos.at(w).x) = _ghmap.at(_pos.at(w).y).at(_pos.at(w).x);
            _pos.at(w).y += mv;
            _map.at(_pos.at(w).y).at(_pos.at(w).x) = std::to_string(w)[0];
        }
        return true;
    }
    return false;
}

bool ArcadeGames::pacman::moveX(int mv, int w)
{

    if (_pos.at(0).y == 10 && (_pos.at(w).x == 0 || _pos.at(w).x == 26)) {
        if (w == 0) {
            _map.at(_pos.at(w).y).at(_pos.at(w).x) = ' ';
            _ghmap.at(_pos.at(w).y).at(_pos.at(w).x) = ' ';
            if (_pos.at(w).x == 0)
                _pos.at(w).x = 25;
            else
                _pos.at(w).x = 1;
            if (mv > 0) {
                _map.at(_pos.at(w).y).at(_pos.at(w).x) = 'R';
                _bef = Input::D_KEY;
            } else {
                _map.at(_pos.at(w).y).at(_pos.at(w).x) = 'L';
                _bef = Input::Q_KEY;
            }
        } else {
            _map.at(_pos.at(w).y).at(_pos.at(w).x) = _ghmap.at(_pos.at(w).y).at(_pos.at(w).x);
            _pos.at(w).x += mv;
            _map.at(_pos.at(w).y).at(_pos.at(w).x) = std::to_string(w)[0];
        }
    }
    if (w == 0 && _ghmap.at(_pos.at(w).y).at(_pos.at(w).x + mv) == '.') {
        _info["Score"] = std::to_string(std::stoi(_info["Score"]) + 10);
        _sounds.push_back("./ressources/pacman/pacman_chomp.wav");
    }
    if (w == 0 && _map.at(_pos.at(w).y).at(_pos.at(w).x + mv) == 'S') {
        _info["Score"] = std::to_string(std::stoi(_info["Score"]) + 10);
        _super = true;
        _start = _time;
    }
    if (_map.at(_pos.at(w).y).at(_pos.at(w).x + mv) != '#' &&
    (_map.at(_pos.at(w).y).at(_pos.at(w).x + mv) != '/' || w > 0)) {
        if (w == 0) {
            _map.at(_pos.at(w).y).at(_pos.at(w).x) = ' ';
            _ghmap.at(_pos.at(w).y).at(_pos.at(w).x) = ' ';
            _pos.at(w).x += mv;
            if (mv > 0) {
                _map.at(_pos.at(w).y).at(_pos.at(w).x) = 'R';
                _bef = Input::D_KEY;
            } else {
                _map.at(_pos.at(w).y).at(_pos.at(w).x) = 'L';
                _bef = Input::Q_KEY;
            }
        } else {
            _map.at(_pos.at(w).y).at(_pos.at(w).x) = _ghmap.at(_pos.at(w).y).at(_pos.at(w).x);
            _pos.at(w).x += mv;
            _map.at(_pos.at(w).y).at(_pos.at(w).x) = std::to_string(w)[0];
        }
        return true;
    }
    return false;
}

void ArcadeGames::pacman::death()
{
    for (int i = 1; i < 5; i++) {
        if (_super && _pos.at(0).x == _pos.at(i).x && _pos.at(0).y == _pos.at(i).y) {
            std::stack<Input> path = find_way(_pos.at(i), {10, 10});
            if (path.empty())
                return;
            while (!path.empty()) {
                _road[i - 1].push(path.top());
                path.pop();
            }
            _death[i - 1] = true;
            _codeCouleur[i + '0'] = std::make_tuple("./ressources/pacman/redright.jpg", MyColor::MY_BLUE);
        } else if (_pos.at(0).x == _pos.at(i).x && _pos.at(0).y == _pos.at(i).y) {
            _map.clear();
            _map = _ghmap;
            _bef = Input::NO_INPUT;
            _aft = Input::NO_INPUT;
            _pos.clear();
            _pos.push_back({13, 16});
            _map[16][13] = 'U';
            _pos.push_back({10, 10});
            _pos.push_back({12, 10});
            _pos.push_back({14, 10});
            _pos.push_back({16, 10});
            _info["Life"] = std::to_string(std::stoi(_info["Life"]) - 1);
            if (std::stoi(_info["Life"]) == 0)
                status = 0;
        }
    }
}

void ArcadeGames::pacman::nxtLevel()
{
    if (std::stoi(_info["Score"]) == 2260 * std::stoi(_info["Level"])) {
        _animatelvl = true;
        _info["Level"] = std::to_string(std::stoi(_info["Level"]) + 1);
        _super = false;
        _map.clear();
        _map = _clone;
        _ghmap.clear();
        _ghmap = _clone;
        _bef = Input::NO_INPUT;
        _aft = Input::NO_INPUT;
        _time = 0;
        _pos.clear();
        _pos.push_back({13, 16});
        _map[16][13] = 'U';
        _pos.push_back({10, 10});
        _pos.push_back({12, 10});
        _pos.push_back({14, 10});
        _pos.push_back({16, 10});
    }
}

int ArcadeGames::pacman::manhattan_distance(pos p1, pos p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

std::stack<Input> ArcadeGames::pacman::find_way(pos destination, pos depart)
{
    std::queue<pos> frontier;
    std::vector<std::vector<bool>> explored(_map.size(), std::vector<bool>(_map[0].size(), false));
    pos tmp;
    tmp.x = -1;
    tmp.y = -1;
    std::vector<std::vector<pos>> came_from(_map.size(), std::vector<pos>(_map[0].size(), tmp));
    std::vector<std::vector<int>> cost_so_far(_map.size(), std::vector<int>(_map[0].size(), 1000000));

    frontier.push(depart);
    cost_so_far[depart.y][depart.x] = 0;

    while (!frontier.empty()) {
        pos current = frontier.front();
        frontier.pop();

        if (current.x == destination.x && current.y == destination.y) {
            break;
        }

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 || j == 0) {
                    size_t new_x = current.x + j;
                    size_t new_y = current.y + i;
                    if (new_x >= 0 && new_x < _map[0].size() && new_y >= 0 && new_y < _map.size() && _map[new_y][new_x] != '#' && !explored[new_y][new_x]) {
                        int new_cost = cost_so_far[current.y][current.x] + 1;
                        if (new_cost < cost_so_far[new_y][new_x]) {
                            cost_so_far[new_y][new_x] = new_cost;
                            pos next;
                            next.x = new_x;
                            next.y = new_y;
                            frontier.push(next);
                            explored[new_y][new_x] = true;
                            came_from[new_y][new_x] = current;
                        }
                    }
                }
            }
        }
    }

    std::stack<Input> path;
    pos current = destination;
    while (current.x != depart.x || current.y != depart.y) {
        pos next = came_from[current.y][current.x];
        if (next.x < current.x) {
            path.push(Input::LEFT_ARROW);
        } else if (next.x > current.x) {
            path.push(Input::RIGHT_ARROW);
        } else if (next.y < current.y) {
            path.push(Input::UP_ARROW);
        } else if (next.y > current.y) {
            path.push(Input::DOWN_ARROW);
        }
        current = next;
    }
    return path;
}

bool ArcadeGames::pacman::follow(pos pcm, int fantome)
{
    std::stack<Input> path = find_way(_pos.at(fantome), pcm);

    if (path.empty()) {
        return false;
    }
    while (!path.empty()) {
        _road[fantome - 1].push(path.top());
        path.pop();
    }
    return true;
}

ArcadeGames::pos ArcadeGames::pacman::getRandPos(int radius)
{
    pos tmp;
    size_t x = _pos.at(0).x + rand() % radius;
    size_t y = _pos.at(0).y + rand() % radius;
    if (x >= _map[0].size())
        x = _map[0].size() - 2;
    if (x <= 0)
        x = 2;
    if (y >= _map.size())
        y = _map.size() - 2;
    if (y <= 0)
        y = 2;
    if (_map[y][x] == 'C' || _map[y][x] == '#')
        return getRandPos(radius);
    tmp.x = x;
    tmp.y = y;
    return tmp;
}

void ArcadeGames::pacman::ghost()
{
    for (int i = 0; i < 4; i++) {
        if (_time % 2 == 0 || _death[i] == true) {
            if (_road[i].empty()) {
                _death[i] = false;
                follow(getRandPos(5 - std::stoi(_info["Level"]) + (i + 1) * 2), i + 1);
            } else {
                move(_road[i].top(), i + 1);
                _road[i].pop();
            }
        }
    }
}

void ArcadeGames::pacman::changeLevel()
{
    if (_lvlTime % 4 == 0)
        _codeCouleur['#'] = std::make_tuple("./ressources/pacman/white.jpg", MyColor::MY_WHITE);
    else
        _codeCouleur['#'] = std::make_tuple("./ressources/pacman/WallPacman.jpg", MyColor::MY_BLUE);
    if (_lvlTime == 20) {
        _animatelvl = false;
        _codeCouleur['#'] = std::make_tuple("./ressources/pacman/WallPacman.jpg", MyColor::MY_BLUE);
    }
}

void ArcadeGames::pacman::update(std::vector<Input> inputs)
{
    _sounds.clear();
    Input actual = Input::NO_INPUT;
    if (inputs.size() > 0) {
        for (auto &input : inputs) {
            if (input == Input::LEFT_ARROW || input == Input::RIGHT_ARROW || input == Input::UP_ARROW || input == Input::DOWN_ARROW || input == Input::ENTER) {
                actual = input;
                break;
            }
        }
    }
    if (_map.at(_pos.at(0).y).at(_pos.at(0).x) == ' ')
        _map.at(_pos.at(0).y).at(_pos.at(0).x) = 'U';
    if (actual == Input::ENTER)
        _super = !_super;
    if (_animatelvl == true) {
        changeLevel();
        _lvlTime++;
        return;
    }
    animate();
    if (!move(actual, 0)) {
        if (!move(_aft, 0))
            move(_bef, 0);
        else
            _aft = Input::NO_INPUT;
        if (actual != Input::NO_INPUT)
        _aft = actual;
    }
    death();
    nxtLevel();
    ghost();
    death();
    if (_time - _start == 90 && _start != -1) {
        _start = -1;
        _super = false;
    }
    _time++;
    _lvlTime = 0;
}

void ArcadeGames::pacman::dumpMap()
{
    for (auto &i : _clone) {
        std::cout << i.c_str() << std::endl;
    }
}
