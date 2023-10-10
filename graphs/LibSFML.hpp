/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** libSFML
*/

#pragma once

#include "Agraphs.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <chrono>

namespace ArcadeGraphs {
class libSFML : public Agraphs {
    public:
        libSFML();
        ~libSFML();
        std::string getName() {return "libSFML";};
        void drawText(const std::string &text, int x, int y,MyColor cl);
        void checkEvent();
        void refreshGraph(int);
        void drawMap(int x, int y,std::vector<std::string> map);
        void setColor(std::map<char, std::tuple<std::string, MyColor>>);
        void setSound(std::vector<std::string>);
        void playSound(std::string path);
       protected:
       private:
        sf::RenderWindow _window;
        std::map<char, sf::Texture> _texture;
        std::vector<sf::RectangleShape> _rect;
        int _windowSizeX;
        int _windowSizeY;
        sf::Event _event;
        std::map<std::string, sf::SoundBuffer> _soundBuffer;
        std::map<std::string, sf::Sound> _sounds;
};
}