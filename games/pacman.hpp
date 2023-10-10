/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** pacman
*/

#pragma once

#include "Agames.hpp"
#include <queue>
#include <stack>


namespace ArcadeGames {
typedef struct pos {
    int x;
    int y;
} pos;

class pacman : public Agames {
    public:
        pacman();
        ~pacman();
        std::string gameName() { return "arcade_pacman"; };
        void update(std::vector<Input> i);
        void dumpMap();
    protected:
    private:
        void nxtLevel();
        void animate();
        void changeLevel();
        void death();
        int manhattan_distance(pos p1, pos p2);
        std::stack<Input> find_way(pos destination, pos depart);
        pos getRandPos(int radius);
        bool move(Input i, int who);
        bool moveY(int mv, int who);
        bool moveX(int mv, int who);
        void ghost();
        bool follow(pos, int who);
        bool _animatelvl;
        int _lvlTime;
        Input _bef;
        Input _aft;
        bool _mouthOpen;
        bool _super;
        std::vector<bool> _death;
        int _start;
        int _time;
        std::vector<std::stack<Input>> _road;
        std::vector<std::string> _clone;
        std::vector<std::string> _ghmap;
        std::vector<std::string> _path;
        std::vector<pos> _pos;
};

}