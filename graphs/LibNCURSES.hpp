/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** libNCURSES
*/

#pragma once

#include "Agraphs.hpp"
#include <ncurses.h>
#include <unistd.h>

namespace ArcadeGraphs {
class libNCURSES : public Agraphs {
   public:
    libNCURSES();
    ~libNCURSES();
    std::string getName() { return "libNCURSES";};
    void drawText(const std::string &text, int x, int y,MyColor color);
    void drawMap(int x, int y, std::vector<std::string> map);
    void setColor(std::map<char, std::tuple<std::string, MyColor>> color);
    void refreshGraph(int);
    void checkEvent();
    void playSound(std::string path) {(void)(path);};
    void setSound(std::vector<std::string> paths){(void)(paths);};

   protected:
   private:
    std::map<std::string, std::vector<std::string>> _mapOfFile;
};
}  // namespace ArcadeGraphs