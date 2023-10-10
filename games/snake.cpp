/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** snake
*/

#include "snake.hpp"

extern "C" ArcadeGames::Agames *createGame()
{
    return new ArcadeGames::snake();
}

extern "C" void deleteGame(ArcadeGames::Agames *game)
{
    delete game;
}

ArcadeGames::snake::node::node(char type, int x, int y)
{
    this->type = type;
    this->x = x;
    this->y = y;
}

ArcadeGames::snake::node::~node()
{
}

void ArcadeGames::snake::handleRight()
{
    nodes.at(0).type = 'R';
    for (int i = nodes.size() - 1; i >= 1; i--) {
        nodes.at(i).x = nodes.at(i-1).x;
        nodes.at(i).y = nodes.at(i-1).y;
        nodes.at(i).orientation = nodes.at(i - 1).orientation;
    }
    if (_map.at(nodes.at(0).y).at(nodes.at(0).x + 1) != ' ' && _map.at(nodes.at(0).y).at(nodes.at(0).x + 1) != 'F')
        status = 0;
    else if (_map.at(nodes.at(0).y).at(nodes.at(0).x + 1) == 'F')
        eatApple();
    nodes.at(0).x += 1;
}

void ArcadeGames::snake::handleBackward()
{
    nodes.at(0).type = 'D';
    for (int i = nodes.size() - 1; i >= 1; i--) {
        nodes.at(i).x = nodes.at(i-1).x;
        nodes.at(i).y = nodes.at(i-1).y;
        nodes.at(i).orientation = nodes.at(i - 1).orientation;
    }
    if (_map.at(nodes.at(0).y + 1).at(nodes.at(0).x) != ' ' && _map.at(nodes.at(0).y + 1).at(nodes.at(0).x) != 'F')
        status = 0;
    else if (_map.at(nodes.at(0).y + 1).at(nodes.at(0).x) == 'F')
        eatApple();
    nodes.at(0).y += 1;
}

void ArcadeGames::snake::handleLeft()
{
    nodes.at(0).type = 'L';
    for (int i = nodes.size() - 1; i >= 1; i--) {
        nodes.at(i).x = nodes.at(i-1).x;
        nodes.at(i).y = nodes.at(i-1).y;
        nodes.at(i).orientation = nodes.at(i - 1).orientation;
    }
    if (_map.at(nodes.at(0).y).at(nodes.at(0).x - 1) != ' ' && _map.at(nodes.at(0).y).at(nodes.at(0).x - 1) != 'F')
        status = 0;
    else if (_map.at(nodes.at(0).y).at(nodes.at(0).x - 1) == 'F')
        eatApple();
    nodes.at(0).x -= 1;
}

void ArcadeGames::snake::handleForward()
{
    nodes.at(0).type = 'U';
    for (int i = nodes.size() - 1; i >= 1; i--) {
        nodes.at(i).x = nodes.at(i-1).x;
        nodes.at(i).y = nodes.at(i-1).y;
        nodes.at(i).orientation = nodes.at(i - 1).orientation;
    }
    if (_map.at(nodes.at(0).y - 1).at(nodes.at(0).x) != ' ' && _map.at(nodes.at(0).y - 1).at(nodes.at(0).x) != 'F')
        status = 0;
    else if (_map.at(nodes.at(0).y - 1).at(nodes.at(0).x) == 'F')
        eatApple();
    nodes.at(0).y -= 1;
}

void ArcadeGames::snake::dump() const
{
    for (auto &i : _map) {
        std::cout << i << std::endl;
    }
}

void ArcadeGames::snake::eatApple()
{
    _sounds.push_back(_eatSound);
    if (nodes.at(nodes.size() - 1).orientation == Input::UP_ARROW)
        nodes.push_back(node('B', nodes.at(nodes.size() - 1).x, nodes.at(nodes.size() - 1).y + 1));
    else if (nodes.at(nodes.size() - 1).orientation == Input::DOWN_ARROW)
        nodes.push_back(node('B', nodes.at(nodes.size() - 1).x, nodes.at(nodes.size() - 1).y - 1));
    else if (nodes.at(nodes.size() - 1).orientation == Input::LEFT_ARROW)
        nodes.push_back(node('B', nodes.at(nodes.size() - 1).x + 1, nodes.at(nodes.size() - 1).y));
    else if (nodes.at(nodes.size() - 1).orientation == Input::RIGHT_ARROW)
        nodes.push_back(node('B', nodes.at(nodes.size() - 1).x - 1, nodes.at(nodes.size() - 1).y));
    nodes.at(nodes.size() - 1).setParent(&nodes.at(nodes.size() - 2));
    nodes.at(nodes.size() - 1).orientation = nodes.at(nodes.size() - 2).orientation;
    nodes.at(nodes.size() - 2).type = 'B';
    fruit = true;
    bool isPosible = false;
    int x = 0;
    int y = 0;
    while (isPosible == false) {
        x = rand() % 20;
        y = rand() % 20;
        for (auto &i : nodes) {
            if (i.x == x && i.y == y) {
                isPosible = false;
                break;
            } else {
                isPosible = true;
            }
        }
    }
    fruitX = x;
    fruitY = y;
    _info["Score"] = std::to_string(score += 10);
}

void ArcadeGames::snake::refreshMap()
{
    if (nodes.at(nodes.size() - 2).orientation == Input::UP_ARROW) {
        nodes.at(nodes.size() - 1).type = 'T';
    } else if (nodes.at(nodes.size() - 2).orientation == Input::DOWN_ARROW) {
        nodes.at(nodes.size() - 1).type = 'Y';
    } else if (nodes.at(nodes.size() - 2).orientation == Input::LEFT_ARROW) {
        nodes.at(nodes.size() - 1).type = 'I';
    } else if (nodes.at(nodes.size() - 2).orientation == Input::RIGHT_ARROW) {
        nodes.at(nodes.size() - 1).type = 'O';
    }
    for (auto &i : nodes) {
        if (i.type == 'B' || i.type == 'K' || i.type == '1' || i.type == '2' || i.type == '3' || i.type == '4') {
            if (i.orientation == Input::UP_ARROW || i.orientation == Input::DOWN_ARROW)
                i.type = 'B';
            else if (i.orientation == Input::LEFT_ARROW || i.orientation == Input::RIGHT_ARROW)
                i.type = 'K';
        }
    }
    checkCorner();
    for (auto &i : nodes) {
        _map.at(i.y).at(i.x) = i.type;
    }
    if (!fruit)
        _map.at(lastNodeY).at(lastNodeX) = ' ';
}

ArcadeGames::snake::snake()
{
    _map.push_back("###########################");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("#                         #");
    _map.push_back("###########################");

    nodes.reserve(525);
    std::srand(std::time(nullptr));
    fruitX = std::rand() % 20;
    fruitY = std::rand() % 20;
    nodes.push_back(node('U', 13, 11));
    nodes.push_back(node('B', 13, 12));
    nodes.push_back(node('B', 13, 13));
    nodes.push_back(node('T', 13, 14));
    nodes.at(1).setParent(&nodes.at(0));
    nodes.at(2).setParent(&nodes.at(1));
    nodes.at(3).setParent(&nodes.at(2));

    for (auto &i : nodes) {
        _map.at(i.y).at(i.x) = i.type;
    }
    _codeCouleur['T'] = std::make_tuple("./ressources/snake/tail_down.jpg", MyColor::MY_LIGHT_CYAN);
    _codeCouleur['Y'] = std::make_tuple("./ressources/snake/tail_up.jpg", MyColor::MY_LIGHT_CYAN);
    _codeCouleur['I'] = std::make_tuple("./ressources/snake/tail_right.jpg", MyColor::MY_LIGHT_CYAN);
    _codeCouleur['O'] = std::make_tuple("./ressources/snake/tail_left.jpg", MyColor::MY_LIGHT_CYAN);
    _codeCouleur['U'] = std::make_tuple("./ressources/snake/head_up.jpg", MyColor::MY_LIGHT_BLUE);
    _codeCouleur['D'] = std::make_tuple("./ressources/snake/head_down.jpg", MyColor::MY_LIGHT_BLUE);
    _codeCouleur['L'] = std::make_tuple("./ressources/snake/head_left.jpg", MyColor::MY_LIGHT_BLUE);
    _codeCouleur['R'] = std::make_tuple("./ressources/snake/head_right.jpg", MyColor::MY_LIGHT_BLUE);
    _codeCouleur['B'] = std::make_tuple("./ressources/snake/body_vertical.jpg", MyColor::MY_BLUE);
    _codeCouleur['K'] = std::make_tuple("./ressources/snake/body_horizontal.jpg", MyColor::MY_BLUE);
    _codeCouleur['1'] = std::make_tuple("./ressources/snake/body_bottomleft.jpg", MyColor::MY_BLUE);
    _codeCouleur['2'] = std::make_tuple("./ressources/snake/body_bottomright.jpg", MyColor::MY_BLUE);
    _codeCouleur['3'] = std::make_tuple("./ressources/snake/body_topleft.jpg", MyColor::MY_BLUE);
    _codeCouleur['4'] = std::make_tuple("./ressources/snake/body_topright.jpg", MyColor::MY_BLUE);
    _codeCouleur['#'] = std::make_tuple("./ressources/snake/wall.jpg", MyColor::MY_GREEN);
    _codeCouleur['F'] = std::make_tuple("./ressources/snake/apple.jpeg", MyColor::MY_RED);
    _codeCouleur[' '] = std::make_tuple("./ressources/snake/void.jpg", MyColor::MY_LIGHT_GREEN);
    _info["Score"] = std::to_string(score);
    fruit = true;
}

void ArcadeGames::snake::checkCorner()
{
    for (size_t i = 1 ; i < nodes.size() - 1 ; i++) {
        if (nodes.at(i).type == 'T' || nodes.at(i).type == 'Y' || nodes.at(i).type == 'I' || nodes.at(i).type == 'O')
            break;
        if (nodes.at(i).x == nodes.at(i).parent->x + 1 && nodes.at(i).y == nodes.at(i).parent->y) {
            if (nodes.at(i).x == nodes.at(i+1).x && nodes.at(i).y == nodes.at(i+1).y - 1)
                nodes.at(i).type = '1';
        }
        else if (nodes.at(i).x == nodes.at(i).parent->x && nodes.at(i).y == nodes.at(i).parent->y + 1) {
            if (nodes.at(i).x == nodes.at(i+1).x + 1 && nodes.at(i).y == nodes.at(i+1).y) {
                nodes.at(i).type = '3';
            }
        }
        else if (nodes.at(i).x == nodes.at(i).parent->x && nodes.at(i).y == nodes.at(i).parent->y - 1) {
            if (nodes.at(i).x == nodes.at(i+1).x - 1 && nodes.at(i).y == nodes.at(i+1).y) {
                nodes.at(i).type = '2';
            }
        }
        else if (nodes.at(i).x == nodes.at(i).parent->x - 1 && nodes.at(i).y == nodes.at(i).parent->y) {
            if (nodes.at(i).x == nodes.at(i+1).x  && nodes.at(i).y == nodes.at(i+1).y + 1)
                nodes.at(i).type = '4';
       }
       if (nodes.at(i).x == nodes.at(i).parent->x && nodes.at(i).y == nodes.at(i).parent->y - 1) {
            if (nodes.at(i).x == nodes.at(i+1).x + 1 && nodes.at(i).y == nodes.at(i+1).y)
                nodes.at(i).type = '1';
        }
        else if (nodes.at(i).x == nodes.at(i).parent->x + 1&& nodes.at(i).y == nodes.at(i).parent->y ) {
            if (nodes.at(i).x == nodes.at(i+1).x && nodes.at(i).y == nodes.at(i+1).y + 1) {
                nodes.at(i).type = '3';
            }
        }
        else if (nodes.at(i).x == nodes.at(i).parent->x - 1 && nodes.at(i).y == nodes.at(i).parent->y) {
            if (nodes.at(i).x == nodes.at(i+1).x && nodes.at(i).y == nodes.at(i+1).y - 1) {
                nodes.at(i).type = '2';
            }
        }
        else if (nodes.at(i).x == nodes.at(i).parent->x && nodes.at(i).y == nodes.at(i).parent->y + 1) {
            if (nodes.at(i).x == nodes.at(i+1).x - 1 && nodes.at(i).y == nodes.at(i+1).y)
                nodes.at(i).type = '4';
       }
    }
}

ArcadeGames::snake::~snake() {}

void ArcadeGames::snake::update(std::vector<Input> inputs)
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
    if (actual == Input::ENTER) {
        _caca = !_caca;
        if (_caca) {
            _codeCouleur['U'] = std::make_tuple(
                "./ressources/snake/head_upcaca.jpg", MyColor::MY_LIGHT_BLUE);
            _codeCouleur['D'] = std::make_tuple(
                "./ressources/snake/head_downcaca.jpg", MyColor::MY_LIGHT_BLUE);
            _codeCouleur['L'] = std::make_tuple(
                "./ressources/snake/head_leftcaca.jpg", MyColor::MY_LIGHT_BLUE);
            _codeCouleur['R'] =
                std::make_tuple("./ressources/snake/head_rightcaca.jpg",
                                MyColor::MY_LIGHT_BLUE);
            _codeCouleur['F'] =
                std::make_tuple("./ressources/snake/caca.jpg", MyColor::MY_RED);
            _eatSound = "./ressources/snake/fart.wav";
        } else {
            _codeCouleur['U'] = std::make_tuple(
                "./ressources/snake/head_up.jpg", MyColor::MY_LIGHT_BLUE);
            _codeCouleur['D'] = std::make_tuple(
                "./ressources/snake/head_down.jpg", MyColor::MY_LIGHT_BLUE);
            _codeCouleur['L'] = std::make_tuple(
                "./ressources/snake/head_left.jpg", MyColor::MY_LIGHT_BLUE);
            _codeCouleur['R'] = std::make_tuple(
                "./ressources/snake/head_right.jpg", MyColor::MY_LIGHT_BLUE);
            _codeCouleur['F'] = std::make_tuple("./ressources/snake/apple.jpeg",
                                                MyColor::MY_GREEN);
            _eatSound = "./ressources/snake/crunch.wav";
        }
    }
    nodes.at(0).orientation = lastInput;
    if (fruitX < 1) fruitX++;
    if (fruitY < 1) fruitY++;
    fruit = false;
    _map.at(fruitY).at(fruitX) = 'F';
    lastNodeX = nodes.at(nodes.size() - 1).x;
    lastNodeY = nodes.at(nodes.size() - 1).y;
    if (nodes.at(0).orientation == Input::UP_ARROW) {
        if (actual == Input::LEFT_ARROW || actual == Input::RIGHT_ARROW)
            lastInput = actual;
        if (lastInput == Input::LEFT_ARROW) {
            handleLeft();
        } else if (lastInput == Input::RIGHT_ARROW) {
            handleRight();
        } else if (lastInput == Input::UP_ARROW) {
            handleForward();
        }
    } else if (nodes.at(0).orientation == Input::DOWN_ARROW) {
        if (actual == Input::LEFT_ARROW || actual == Input::RIGHT_ARROW)
            lastInput = actual;
        if (lastInput == Input::LEFT_ARROW) {
            handleLeft();
        } else if (lastInput == Input::RIGHT_ARROW) {
            handleRight();
        } else if (lastInput == Input::DOWN_ARROW) {
            handleBackward();
        }
    } else if (nodes.at(0).orientation == Input::LEFT_ARROW) {
        if (actual == Input::UP_ARROW || actual == Input::DOWN_ARROW)
            lastInput = actual;
        if (lastInput == Input::UP_ARROW) {
            handleForward();
        } else if (lastInput == Input::DOWN_ARROW) {
            handleBackward();
        } else if (lastInput == Input::LEFT_ARROW) {
            handleLeft();
        }
    } else if (nodes.at(0).orientation == Input::RIGHT_ARROW) {
        if (actual == Input::UP_ARROW || actual == Input::DOWN_ARROW)
            lastInput = actual;
        if (lastInput == Input::UP_ARROW) {
            handleForward();
        } else if (lastInput == Input::DOWN_ARROW) {
            handleBackward();
        } else if (lastInput == Input::RIGHT_ARROW) {
            handleRight();
        }
    }
    if (status != 0)
        refreshMap();
}
