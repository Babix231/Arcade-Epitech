/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** Agames
*/

#pragma once
#include "Igames.hpp"

namespace ArcadeGames {
class Agames : public Igames {
   public:
    virtual ~Agames() = default;
    virtual std::string gameName() = 0;
    std::vector<std::string> getMap() { return _map; };
    std::map<char, std::tuple<std::string, MyColor>> getColorCode() {
        return _codeCouleur;
    };
    virtual void update(std::vector<Input>) = 0;
    std::map<std::string, std::string> getInfo() { return _info; }
    int getStatus() { return status; };
    std::vector<std::string> getSounds() { return {_sounds}; }
   protected:
    std::vector<std::string> _map;
    std::map<char, std::tuple<std::string, MyColor>> _codeCouleur;
    std::map<std::string, std::string> _info;
    int status = -1;
    std::vector<std::string> _sounds;
   private:
};
}