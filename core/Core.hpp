/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** Core
*/

#pragma once
#include <iostream>
#include "Libhandler.hpp"
#include "../games/Igames.hpp"
#include "../graphs/Igraphs.hpp"
#include "../Input.hpp"
#include <memory>
#include <filesystem>
#include <chrono>
#include <thread>
namespace ArcadeCore {
    class Core {
       public:
        Core(char * name);
        ~Core(){};
        void Menu();
        void DrawPseudo();
        void checkFocused();
        void DrawMenu();
        void DrawGame();
        void DrawTouch();
        void checkEvent(std::vector<Input> input);
        void refreshLibs();
        void pickNextGame();
        void DrawScoreBoard();
        void SaveScore();
        void pickNextGraph();
       protected:
       private:
        std::unique_ptr<ArcadeCore::Libhandler> _libhandler;
        std::shared_ptr<ArcadeGames::Igames> _game;
        std::shared_ptr<ArcadeGraphs::Igraphs> _graphs;
        int _etat = 0;
        unsigned int _actualGame = 0;
        unsigned int _actualGraph = 0;
        unsigned int _maxGame = 0;
        unsigned int _maxGraph = 0;
        unsigned int _select = 0;
        std::vector<std::string> _pseudo;
        int _whichLetter = 0;
        std::string _alphabet;
        std::chrono::time_point<std::chrono::system_clock> _start;
        std::chrono::time_point<std::chrono::system_clock> _end;
        std::chrono::duration<long> _elapsed_seconds;
        bool paused = false;
    };
};
