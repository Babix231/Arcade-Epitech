/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** libSFML
*/

#include "LibSFML.hpp"
#include <unistd.h>

extern "C" ArcadeGraphs::Agraphs *createGraph()
{
    return new ArcadeGraphs::libSFML();
}

extern "C" void deleteGraph(ArcadeGraphs::Agraphs *graph)
{
    delete graph;
}

ArcadeGraphs::libSFML::libSFML()
{
    _window.create(sf::VideoMode(1920,1080), "Arcade" , sf::Style::Default);
    _window.setFramerateLimit(_fps);
    _window.setKeyRepeatEnabled(false);
}

ArcadeGraphs::libSFML::~libSFML()
{
    _window.close();
}

void ArcadeGraphs::libSFML::drawText(const std::string &text, int x, int y ,MyColor color)
{
    sf::Font font;
    font.loadFromFile("./ressources/basico.otf");
    sf::Text textSFML;
    textSFML.setFont(font);
    textSFML.setString(text);
    textSFML.setCharacterSize(30);
    switch (color) {
        case MY_BLACK_RED:
            textSFML.setFillColor(sf::Color::Red);
            break;
        case MY_BLACK_GREEN:
            textSFML.setFillColor(sf::Color::Green);
            break;
        case MY_BLACK_BLUE:
            textSFML.setFillColor(sf::Color::Blue);
            break;
        case MY_BLACK_YELLOW:
            textSFML.setFillColor(sf::Color::Yellow);
            break;
        case MY_BLACK_MAGENTA:
            textSFML.setFillColor(sf::Color::Magenta);
            break;
        case MY_BLACK_CYAN:
            textSFML.setFillColor(sf::Color::Cyan);
            break;
        case MY_BLACK_WHITE:
            textSFML.setFillColor(sf::Color::White);
            break;
        default:
            textSFML.setFillColor(sf::Color::Black);
            break;
    }
    textSFML.setPosition(x, y);
    _window.draw(textSFML);
}

void ArcadeGraphs::libSFML::checkEvent()
{
    _inputV.clear();
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _inputV.push_back(Input::CLOSE);
        if (_event.type == sf::Event::KeyPressed) {
            switch (_event.key.code) {
                case sf::Keyboard::Up:
                        _inputV.push_back(Input::UP_ARROW);
                    break;
                case sf::Keyboard::Down:
                    _inputV.push_back(Input::DOWN_ARROW);
                    break;
                case sf::Keyboard::Left:
                    _inputV.push_back(Input::LEFT_ARROW);
                    break;
                case sf::Keyboard::Right:
                    _inputV.push_back(Input::RIGHT_ARROW);
                    break;
                case sf::Keyboard::Escape:
                    _inputV.push_back(Input::ESCAPE);
                    break;
                case sf::Keyboard::Return:
                    _inputV.push_back(Input::ENTER);
                    break;
                case sf::Keyboard::Space:
                    _inputV.push_back(Input::SPACE);
                    break;
                case sf::Keyboard::Num1:
                    _inputV.push_back(Input::KEY_1);
                    break;
                case sf::Keyboard::Num2:
                    _inputV.push_back(Input::KEY_2);
                    break;
                case sf::Keyboard::Num3:
                    _inputV.push_back(Input::KEY_3);
                    break;
                case sf::Keyboard::Num4:
                    _inputV.push_back(Input::KEY_4);
                    break;
                case sf::Keyboard::Num5:
                    _inputV.push_back(Input::KEY_5);
                    break;
                default:
                    _inputV.push_back(Input::NO_INPUT);
            }
        }
    }
    _inputV.push_back(Input::NO_INPUT);
}

void ArcadeGraphs::libSFML::refreshGraph(int to_sleep)
{
    usleep(to_sleep);
    _window.display();
    _window.clear();
}

void ArcadeGraphs::libSFML::drawMap(int x, int y, std::vector<std::string> map)
{
    sf::err().rdbuf(NULL);
    if (_rect.size() != (map.size() * map[0].size())) {
        _rect.clear();
        for (size_t i = 0; i < map.size(); i++) {
            for (size_t j = 0; j < map[i].size(); j++) {
                _rect.push_back(sf::RectangleShape(sf::Vector2f(40, 40)));
            }
        }
    }
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            _rect[i * map[i].size() + j].setTexture(&_texture[map[i][j]]);
            _rect[i * map[i].size() + j].setPosition(x + j * 40, y + i * 40);
            _window.draw(_rect[i * map[i].size() + j]);
        }
    }
}

void ArcadeGraphs::libSFML::setColor(std::map<char, std::tuple<std::string, MyColor>> color)
{
    _color = color;
    for (auto it = _color.begin(); it != _color.end(); it++) {
        _texture[it->first].loadFromFile(std::get<0>(it->second));
    }
}

void ArcadeGraphs::libSFML::setSound(std::vector<std::string> paths)
{
    for (auto it = paths.begin(); it != paths.end(); it++) {
        if (_soundBuffer.find(*it) == _soundBuffer.end()) {
             _soundBuffer[*it].loadFromFile(*it);
             _sounds[*it].setBuffer(_soundBuffer[*it]);
        }
    }
}

void ArcadeGraphs::libSFML::playSound(std::string path)
{
    if (_sounds[path].getStatus() == sf::Sound::Playing)
        return;
    _sounds[path].play();
}