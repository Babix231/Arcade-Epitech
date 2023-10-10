/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** LibrayLib
*/

#pragma once
#include "Agraphs.hpp"
#include "raylib.h"
#include <unistd.h>


namespace ArcadeGraphs {

typedef struct text {
    std::string text;
    MyColor color;
    int x;
    int y;
} text;

typedef struct cube {
    Vector3 pos;
    float width;
    float height;
    float length;
    MyColor color;
} cube;

class LibrayLib : public Agraphs {
    public:
        LibrayLib();
        ~LibrayLib();
        std::string getName() { return "librayLib"; };
        void drawText(const std::string &text, int x, int y,MyColor cl);
        void drawMap(int x, int y, std::vector<std::string> map);
        void setColor(std::map<char, std::tuple<std::string, MyColor>> color);
        void refreshGraph(int);
        void checkEvent();
        void playSound(std::string path);
        void setSound(std::vector<std::string> paths);

       protected:
       private:
        std::vector<text> _textToDraw;
        std::vector<cube> _cubeToDraw;
        int _sizeMap = 0;
        bool _rotate = false;
        Vector3 _cubePosition = { 0.0f, 0.0f, 0.0f };
        Vector3 _startCamera = { 5.0f, 9.0f, 5.0f };
        Vector3 _MovedPosition = { 5.0f, 9.0f, 5.0f };
        Camera3D _camera = { 0 };
        std::map<std::string, Sound> _sounds;
};
}