/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** core
*/

#include "Core.hpp"

ArcadeCore::Core::Core(char *name)
{
    std::string path = name;
    _libhandler = std::make_unique<Libhandler>();
    try {
        _graphs = _libhandler->loadAndGetlib<ArcadeGraphs::Igraphs>(path, "Graph");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::exit(84);
    }
    _select = 0;
    _whichLetter = 0;
    _actualGame = 1;
    _pseudo.push_back("A");
    _pseudo.push_back("A");
    _pseudo.push_back("A");
    _alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_-0123456789";
    Menu();
}

void ArcadeCore::Core::refreshLibs()
{
    _libhandler->refreshLibs();
    _maxGame = _libhandler->getLibGamesPath().size();
    _maxGraph = _libhandler->getLibGraphsPath().size();
}

void ArcadeCore::Core::checkFocused()
{
    if (_select < _libhandler->getLibGamesPath().size()) {
        _game.reset();
        _game = _libhandler->loadAndGetlib<ArcadeGames::Igames>(_libhandler->getLibGamesPath()[_select], "Game");
        _actualGame = _select;
        _etat = 2;
    } else {
        _graphs.reset();
        _graphs = _libhandler->loadAndGetlib<ArcadeGraphs::Igraphs>(_libhandler->getLibGraphsPath()[_select - _libhandler->getLibGamesPath().size()], "Graph");
        _actualGraph = _select - _libhandler->getLibGamesPath().size();
        _etat = 1;
    }
}
void ArcadeCore::Core::pickNextGame()
{
    if (_actualGame + 1 >= _maxGame)
        _actualGame = 0;
    else
        _actualGame += 1;
    _game.reset();
    try
    {
        _game = _libhandler->loadAndGetlib<ArcadeGames::Igames>(_libhandler->getLibGamesPath()[_actualGame], "Game");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::exit(84);
    }
}

void ArcadeCore::Core::pickNextGraph()
{
    if (_actualGraph + 1 >= _maxGraph)
        _actualGraph = 0;
    else
        _actualGraph += 1;
    _graphs.reset();
    try
    {
        _graphs = _libhandler->loadAndGetlib<ArcadeGraphs::Igraphs>(_libhandler->getLibGraphsPath()[_actualGraph], "Graph");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::exit(84);
    }
}

void ArcadeCore::Core::checkEvent(std::vector<Input> inputs)
{
    for (auto input : inputs ) {
    if (input == Input::ENTER) {
        if (_etat == 0)
            _etat = 1;
        else if (_etat == 1)
            checkFocused();
    }
    if (input == Input::SPACE) {
        if (paused == false)
            paused = true;
        else
            paused = false;
    }
    if (input == Input::KEY_1)
        pickNextGame();
    if (input == Input::KEY_2)
        pickNextGraph();
    if (input == Input::UP_ARROW) {
        if (_select > 0)
            _select -= 1;
    }
    if (input == Input::DOWN_ARROW) {
        _select += 1;
        if (_select > _libhandler->getLibGamesPath().size() + _libhandler->getLibGraphsPath().size() - 1)
            _select = _libhandler->getLibGamesPath().size() + _libhandler->getLibGraphsPath().size() - 1;
    }
    if (input == Input::ESCAPE) {
        if (_etat >= 2)
            _etat = 1;
        else {
            _graphs.reset();
            std::exit(0);
        }
    }
    if (input == Input::CLOSE) {
        _graphs.reset();
        std::exit(0);
    }
    }
}

void ArcadeCore::Core::Menu()
{
    while (1) {
        if (_etat == 0)
            DrawPseudo();
        if (_etat == 1)
            DrawMenu();
        if (_etat == 2)
            DrawGame();
        this->refreshLibs();
    }
}