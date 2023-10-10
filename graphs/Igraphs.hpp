/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** Igraphs
*/

#pragma once
#include <iostream>
#include "../Input.hpp"
#include <vector>
#include <fstream>
#include <map>
namespace ArcadeGraphs {
class Igraphs {
    public:
        virtual void drawText(const std::string &text, int x, int y,MyColor cl) = 0;
        virtual void refreshGraph(int) = 0;
        virtual void checkEvent() = 0;
        virtual std::string getName() = 0;
        virtual std::vector<Input> getInputs() = 0;
        virtual int getFps() = 0;
        virtual void drawMap(int x, int y,std::vector<std::string> map) = 0;
        virtual void setColor(std::map<char, std::tuple<std::string, MyColor>>) = 0;
        virtual void playSound(std::string path) = 0;
        virtual void setSound(std::vector<std::string> paths) = 0;

       protected:
       private:
};
}