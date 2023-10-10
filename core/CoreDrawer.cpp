/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** CoreDrawer
*/

#include "Core.hpp"
#include <unistd.h>

void ArcadeCore::Core::DrawPseudo()
{
    _start = std::chrono::system_clock::now();
    _graphs->checkEvent();
    std::vector<Input> inputV = _graphs->getInputs();
    std::vector<Input> inputWithoutEnter = inputV;
    inputWithoutEnter.erase(std::remove(inputWithoutEnter.begin(), inputWithoutEnter.end(), Input::ENTER), inputWithoutEnter.end());
    this->checkEvent(inputWithoutEnter);
    for (auto input : inputV) {
    if (input == Input::UP_ARROW) {
        if (_alphabet.find(_pseudo[_whichLetter]) == _alphabet.size() - 1)
            _pseudo[_whichLetter] = _alphabet[0];
        else
            _pseudo[_whichLetter] = _alphabet[(_alphabet.find(_pseudo[_whichLetter]) + 1)];
    }
    else if (input == Input::DOWN_ARROW) {
        if (_alphabet.find(_pseudo[_whichLetter]) == 0)
            _pseudo[_whichLetter] = _alphabet[_alphabet.size() - 1];
        else
            _pseudo[_whichLetter] = _alphabet[(_alphabet.find(_pseudo[_whichLetter]) - 1)];
    }
    else if (_whichLetter < 2 && input == Input::ENTER) {
        _whichLetter += 1;
    }
    else if (_whichLetter == 2 && input == Input::ENTER) {
        _etat = 1;
    }
    }
    _graphs->drawText("Votre pseudo :", 0, 0, MY_BLACK_RED);
    _graphs->drawText(_pseudo[0], 10, 50, MY_BLACK_GREEN);
    _graphs->drawText(_pseudo[1], 60, 50, MY_BLACK_GREEN);
    _graphs->drawText(_pseudo[2], 110, 50, MY_BLACK_GREEN);
    _graphs->drawText("Touches :", 600, 0, MY_BLACK_RED);
    _graphs->drawText("Entrer : Valider lettre par lettre", 600, 50, MY_BLACK_GREEN);
    _end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = _end - _start;
    int elapsewanted = 1000000 / _graphs->getFps();
    elapsewanted -= elapsed_seconds.count() * 1000000;
    if (elapsewanted < 0)
        elapsewanted = 0;
    _graphs->refreshGraph(elapsewanted);
}

void ArcadeCore::Core::DrawTouch()
{
    _graphs->drawText("Touches :", 600, 0, MY_BLACK_RED);
    _graphs->drawText("Tab : Changer de librairie graphique", 600, 50, MY_BLACK_GREEN);
    _graphs->drawText("Echap : Quitter le jeu / retour au menu", 600, 100, MY_BLACK_GREEN);
    _graphs->drawText("Entrer : Valider", 600, 150, MY_BLACK_GREEN);
    _graphs->drawText("1 : Changer de jeu", 600, 200, MY_BLACK_GREEN);
    _graphs->drawText("2 : Changer de graphique", 600, 250, MY_BLACK_GREEN);
}

void ArcadeCore::Core::DrawScoreBoard()
{
    for (unsigned int i = 0; i < _libhandler->getLibGamesPath().size(); i++) {
        std::string gameName = _libhandler->getLibGamesPath()[i].substr(6, _libhandler->getLibGamesPath()[i].size() - 9);
        std::ifstream file("./core/scoreboard/" + gameName + ".scoreboard");
        if (!file) {
            std::ofstream file("./core/scoreboard/" + gameName + ".scoreboard");
            file.close();
        }
    }
    if (_select >= _libhandler->getLibGamesPath().size())
        return;
    std::string gameName = _libhandler->getLibGamesPath()[_select].substr(6, _libhandler->getLibGamesPath()[_select].size() - 9);
    std::ifstream file("./core/scoreboard/" + gameName + ".scoreboard");
    std::string line;
    int i = 1;
    _graphs->drawText("ScoreBoard", 1400, 0, MY_BLACK_BLUE);
    while (std::getline(file, line)) {
        if (i == 7)
            break;
        _graphs->drawText(line, 1400, (i * 50), MY_BLACK_GREEN);
        i++;
    }
    file.close();
}

void ArcadeCore::Core::DrawMenu()
{
    _start = std::chrono::system_clock::now();
    _graphs->checkEvent();
    std::vector<Input> inputV = _graphs->getInputs();
    this->checkEvent(inputV);
    _graphs->drawText("Les jeux :", 10, 50, MY_BLACK_RED);
    std::string pseudo = _pseudo.at(0) + _pseudo.at(1) + _pseudo.at(2);
    _graphs->drawText("Votre Pseudo : " + pseudo, 1400, 350, MY_BLACK_RED);
    for (unsigned int i = 0; i < _libhandler->getLibGamesPath().size(); i++) {
        if (i == _select)
            _graphs->drawText(_libhandler->getLibGamesPath()[i], 10, 100 + (i * 50), MY_BLACK_YELLOW);
        else
            _graphs->drawText(_libhandler->getLibGamesPath()[i], 10, 100 + (i * 50), MY_BLACK_BLUE);
    }
    _graphs->drawText("Les graphiques :", 0, 100 + (_libhandler->getLibGamesPath().size() * 50),MY_BLACK_RED);
    for (unsigned int i = 0; i < _libhandler->getLibGraphsPath().size(); i++) {
        if (i + _libhandler->getLibGamesPath().size() == _select)
            _graphs->drawText(_libhandler->getLibGraphsPath()[i], 10, 150 + (_libhandler->getLibGamesPath().size() * 50) + (i * 50), MY_BLACK_YELLOW);
        else
            _graphs->drawText(_libhandler->getLibGraphsPath()[i], 10, 150 + (_libhandler->getLibGamesPath().size() * 50) + (i * 50), MY_BLACK_BLUE);
    }
    DrawTouch();
    DrawScoreBoard();
    _graphs->drawText(_graphs->getName(), 10, 10, MY_BLACK_RED);
    _end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = _end - _start;
    int elapsewanted = 1000000 / _graphs->getFps();
    elapsewanted -= elapsed_seconds.count() * 1000000;
    if (elapsewanted < 0)
        elapsewanted = 0;
    _graphs->refreshGraph(elapsewanted);
}

void ArcadeCore::Core::SaveScore()
{
    std::string gameName = _libhandler->getLibGamesPath()[_actualGame].substr(6, _libhandler->getLibGamesPath()[_actualGame].size() - 9);
    std::string fileName = "./core/scoreboard/" + gameName + ".scoreboard";
    std::ifstream file(fileName);
    std::string line;
    std::vector<std::string> scoreboard;
    while (std::getline(file, line)) {
        scoreboard.push_back(line);
    }
    file.close();

    std::ofstream file2(fileName);
    std::string pseudo = _pseudo.at(0) + _pseudo.at(1) + _pseudo.at(2);
    std::string score = _game->getInfo().at("Score");
    std::string scoreLine = pseudo + " : " + score;
    scoreboard.push_back(scoreLine);
    std::sort(scoreboard.begin(), scoreboard.end(), [](std::string a, std::string b) {
        return std::stoi(a.substr(a.find(":") + 2, a.size())) > std::stoi(b.substr(b.find(":") + 2, b.size()));
    });
    for (auto &line : scoreboard) {
        file2 << line << std::endl;
    }
    file2.close();
}

void ArcadeCore::Core::DrawGame()
{
    _start = std::chrono::system_clock::now();
    _graphs->checkEvent();
    std::vector<Input> inputV = _graphs->getInputs();
    this->checkEvent(inputV);
    int y = 50;
    if (_game->getStatus() == 0) {
        SaveScore();
        _etat = 1;
        _select = 0;
        return;
    }
    if (paused == false) {
        _game->update(inputV); // 10 fois par seconde
    }
    _graphs->setColor(_game->getColorCode());
    _graphs->drawMap(400, 50,_game->getMap());
    _graphs->setSound(_game->getSounds());
    for (auto &sound : _game->getSounds()) {
        _graphs->playSound(sound);
    }
    for (auto &info : _game->getInfo()) {
        _graphs->drawText(info.first + " : " + info.second, 10, y, MY_BLACK_GREEN);
        y += 50;
    }
    _graphs->drawText(_graphs->getName(), 10, 10, MY_BLACK_RED);
    _end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = _end - _start;
    int elapsewanted = 1000000 / _graphs->getFps();
    elapsewanted -= elapsed_seconds.count() * 1000000;
    if (elapsewanted < 0)
        elapsewanted = 0;
    _graphs->refreshGraph(elapsewanted);
}
