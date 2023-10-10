/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** libSDL
*/

#pragma once

#include "Agraphs.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <unistd.h>

namespace ArcadeGraphs {
class libSDL : public Agraphs {
    public:
        libSDL();
        ~libSDL();
        std::string getName() {return "libSDL";};
        void drawText(const std::string &text, int x, int y,MyColor cl);
        void clearInputs() { _inputV.clear(); }
        void drawMap(int x, int y,std::vector<std::string> map);
        void setColor(std::map<char, std::tuple<std::string, MyColor>> color);
        void refreshGraph(int);
        void checkEvent();
        void playSound(std::string path);
        void setSound(std::vector<std::string> paths);

       protected:
       private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        SDL_Event _event;
        std::vector<SDL_Rect> _rect;
        std::map<char, SDL_Texture*> _texture;
        std::map<std::string, Mix_Chunk*> _sounds;
};
}