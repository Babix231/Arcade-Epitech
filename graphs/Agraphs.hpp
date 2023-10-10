/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** Agraphs
*/

#pragma once
#include "Igraphs.hpp"

namespace ArcadeGraphs {
class Agraphs : public Igraphs {
    public:
        virtual ~Agraphs() = default;
        virtual void drawText(const std::string &text, int x, int y,MyColor cl) = 0;
        virtual void refreshGraph(int) = 0;
        virtual void checkEvent() = 0;
        virtual std::string getName() = 0;
        int getFps() { return _fps; }
        std::vector<Input> getInputs() { return _inputV; }
        virtual void drawMap(int x, int y,std::vector<std::string> map) = 0;
        virtual void setColor(std::map<char, std::tuple<std::string, MyColor>>) = 0;
        virtual void setSound(std::vector<std::string> paths) = 0;
        virtual void playSound(std::string path) = 0;

       protected:
        std::map<char, std::tuple<std::string, MyColor>> _color;
        std::vector<Input> _inputV = {Input::NO_INPUT};
        int _fps = 14;
    private:
};
}