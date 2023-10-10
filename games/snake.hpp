/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** snake
*/

#pragma once

#include "Agames.hpp"
#include <cstdlib>
#include <ctime>
namespace ArcadeGames {
class snake : public Agames {
    class node {
       public:
        node(char type, int x, int y);
        ~node();
        void setParent(node *parent) { this->parent = parent; }
        int x;
        int y;
        char type;
        Input orientation = Input::UP_ARROW;
        node *parent;
    };

    public:
        snake();
        ~snake();
        std::string gameName() { return "arcade_snake"; };
        void handleForward();
        void handleBackward();
        void handleLeft();
        void handleRight();
        void update(std::vector<Input>);
        void eatApple();
        void checkCorner();
        void refreshMap();
        void dump() const;
    protected:
    private:
        int score = 0;
        int fruitX;
        bool _caca = false;
        std::string _eatSound = "./ressources/snake/crunch.wav";
        int fruitY;
        int lastNodeX;
        int lastNodeY;
        Input lastInput = Input::UP_ARROW;
        bool fruit;
        std::vector<node> nodes;
};
}