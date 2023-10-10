/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** libSDL
*/

#include "LibSDL.hpp"

extern "C" ArcadeGraphs::Agraphs *createGraph()
{
    return new ArcadeGraphs::libSDL();
}

extern "C" void deleteGraph(ArcadeGraphs::Agraphs *graph)
{
    delete graph;
}

ArcadeGraphs::libSDL::libSDL()
{
    TTF_Init();
    SDL_Init(SDL_INIT_EVERYTHING);
    _window = SDL_CreateWindow("Arcade", 0, 0, 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    _renderer = SDL_CreateRenderer(_window,-1, 0);
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
      printf("%s", Mix_GetError());
   }
}

ArcadeGraphs::libSDL::~libSDL()
{
    Mix_CloseAudio();
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void ArcadeGraphs::libSDL::drawText(const std::string &str, int x, int y,MyColor color)
{
    TTF_Font *font = TTF_OpenFont("./ressources/Basico.otf", 30);
    if (!font) {
        return;
    }
    SDL_Surface *text = nullptr;
    switch (color) {
        case MY_BLACK_RED:
            text = TTF_RenderText_Solid(font, str.c_str(), {255, 0, 0, 255});
            break;
        case MY_BLACK_GREEN:
            text = TTF_RenderText_Solid(font, str.c_str(), {0, 255, 0, 255});
            break;
        case MY_BLACK_BLUE:
            text = TTF_RenderText_Solid(font, str.c_str(), {0, 0, 255, 255});
            break;
        case MY_BLACK_YELLOW:
            text = TTF_RenderText_Solid(font, str.c_str(), {255, 255, 0, 255});
            break;
        case MY_BLACK_MAGENTA:
            text = TTF_RenderText_Solid(font, str.c_str(), {255, 0, 255, 255});
            break;
        case MY_BLACK_CYAN:
            text = TTF_RenderText_Solid(font, str.c_str(), {0, 255, 255, 255});
            break;
        case MY_BLACK_WHITE:
            text = TTF_RenderText_Solid(font, str.c_str(), {255, 255, 255, 255});
            break;
        default:
            text = TTF_RenderText_Solid(font, str.c_str(), {255, 255, 255, 255});
            break;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, text);
    if (!texture) {
        return;
    }
    SDL_Rect rect = {x, y, 0, 0};
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(_renderer, texture, NULL, &rect);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void ArcadeGraphs::libSDL::checkEvent()
{
    _inputV.clear();
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT) {
            _inputV.push_back(Input::CLOSE);
        }
        if (_event.type == SDL_KEYDOWN) {
            switch (_event.key.keysym.sym) {
                case SDLK_UP:
                    if (_event.key.repeat == 0)
                        _inputV.push_back(Input::UP_ARROW);
                    break;
                case SDLK_DOWN:
                    if (_event.key.repeat == 0)
                    _inputV.push_back(Input::DOWN_ARROW);
                    break;
                case SDLK_LEFT:
                    if (_event.key.repeat == 0)
                    _inputV.push_back(Input::LEFT_ARROW);
                    break;
                case SDLK_RIGHT:
                    if (_event.key.repeat == 0)
                    _inputV.push_back(Input::RIGHT_ARROW);
                    break;
                case SDLK_ESCAPE:
                    if (_event.key.repeat == 0)
                    _inputV.push_back(Input::ESCAPE);
                    break;
                case SDLK_RETURN:
                    if (_event.key.repeat == 0)
                    _inputV.push_back(Input::ENTER);
                    break;
                case SDLK_SPACE:
                    if (_event.key.repeat == 0)
                    _inputV.push_back(Input::SPACE);
                    break;
                case SDLK_1:
                    if (_event.key.repeat == 0)
                    _inputV.push_back(Input::KEY_1);
                    break;
                case SDLK_2:
                    if (_event.key.repeat == 0)
                    _inputV.push_back(Input::KEY_2);
                    break;
                default:
                    _inputV.push_back(Input::NO_INPUT);
            }
        }
    }
    _inputV.push_back(Input::NO_INPUT);
}

void ArcadeGraphs::libSDL::refreshGraph(int to_sleep)
{
    usleep(to_sleep);
    SDL_RenderPresent(_renderer);
    SDL_RenderClear(_renderer);
}

void ArcadeGraphs::libSDL::drawMap(int x, int y, std::vector<std::string> map)
{
    if (_rect.size() != (map.size() * map[0].size())) {
        _rect.clear();
        for (size_t i = 0; i < map.size(); i++) {
            for (size_t j = 0; j < map[i].size(); j++) {
                _rect.push_back(SDL_Rect{static_cast<int>(x + j * 40), static_cast<int>(y + i * 40), 40, 40});
            }
        }
    }
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            char c = map[i][j];
            if (_texture.find(c) != _texture.end()) {
                SDL_Texture* texture = _texture[c];
                SDL_RenderCopy(_renderer, texture, NULL, &_rect[i * map[i].size() + j]);
            }
        }
    }
}


void ArcadeGraphs::libSDL::setColor(std::map<char, std::tuple<std::string, MyColor>> color)
{
    _color = color;
    for (auto it = _color.begin(); it != _color.end(); it++) {
        SDL_Surface* surface = IMG_Load(std::get<0>(it->second).c_str());
        if (!surface) {
            continue;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
        if (!texture) {
            SDL_FreeSurface(surface);
            continue;
        }
        _texture[it->first] = texture;
        SDL_FreeSurface(surface);
    }
}

void ArcadeGraphs::libSDL::setSound(std::vector<std::string> paths)
{
        for (auto it = paths.begin(); it != paths.end(); it++) {
            if (_sounds.find(*it) == _sounds.end()) {
                Mix_Chunk* sound = Mix_LoadWAV(it->c_str());
                _sounds[*it] = sound;
            }
        }

}


void ArcadeGraphs::libSDL::playSound(std::string path)
{
    // if a sound is already playing, stop it
    if (Mix_Playing(-1) != 0) {
        return;
    }
    if (_sounds.find(path) != _sounds.end()) {
        Mix_PlayChannel(-1, _sounds[path], 0);
    }
}

