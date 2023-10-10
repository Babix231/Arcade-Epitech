/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** Igames
*/

#pragma once
#include <iostream>
#include <map>
#include <vector>

#include "../Input.hpp"
namespace ArcadeGames {
class Igames {
   public:
    virtual std::string gameName() = 0;
    virtual std::vector<std::string> getMap() = 0;
    virtual std::map<char, std::tuple<std::string, MyColor>> getColorCode() = 0;
    virtual void update(std::vector<Input>) = 0;
    virtual std::map<std::string, std::string> getInfo() = 0;
    virtual int getStatus() = 0;
    virtual std::vector<std::string> getSounds() = 0;
   protected:
   private:
};
}