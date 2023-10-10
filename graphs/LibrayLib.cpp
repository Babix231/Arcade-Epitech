/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** LibrayLib
*/

#include "LibrayLib.hpp"
// include for sin
#include <cmath>
extern "C" ArcadeGraphs::Agraphs *createGraph()
{
    return new ArcadeGraphs::LibrayLib();
}

extern "C" void deleteGraph(ArcadeGraphs::Agraphs *lib)
{
    delete lib;
}

ArcadeGraphs::LibrayLib::LibrayLib()
{
    InitWindow(1920, 1080, "Arcade");
    SetTargetFPS(_fps);
    InitAudioDevice();
    SetMasterVolume(0.5f);
    SetTraceLogLevel(LOG_NONE);
    SetExitKey(KEY_NULL);  // Disable window close button
    _camera.position = Vector3{ 0.0f, 10.0f, 10.0f };    // Camera position
    _camera.target = Vector3{ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    _camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    _camera.fovy = 45.0f;                                // Camera field-of-view Y
    _camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type
}

ArcadeGraphs::LibrayLib::~LibrayLib()
{
    _textToDraw.clear();
    _cubeToDraw.clear();
    CloseAudioDevice();
    CloseWindow();
}

void ArcadeGraphs::LibrayLib::drawText(const std::string &text, int x, int y,MyColor color)
{
    _textToDraw.push_back({text, color, x, y});
}

void ArcadeGraphs::LibrayLib::drawMap(int a, int b, std::vector<std::string> map)
{
    (void)a;
    (void)b;
    Vector3 pos = {-5.0f, 0.0f, -5.0f};
    _sizeMap = 0;
    for (auto &it : map) {
        for (auto &it2 : it) {
            _cubeToDraw.push_back({pos, 0.3f, 0.1f, 0.3f, std::get<1>(_color[it2])});
            pos.x += 0.3f;
        }
        pos.x = -5.0f;
        pos.z += 0.3f;
        _sizeMap++;
    }
}

void ArcadeGraphs::LibrayLib::setColor(std::map<char, std::tuple<std::string, MyColor>> color)
{
    _color = color;
}

void ArcadeGraphs::LibrayLib::refreshGraph(int to_sleep)
{
	usleep(to_sleep);
    BeginDrawing();
    for (auto &it : _textToDraw) {
       switch (it.color) {
            case MY_BLACK_RED:
                DrawText(it.text.c_str(), it.x, it.y, 20, RED);
                break;
            case MY_BLACK_GREEN:
                DrawText(it.text.c_str(), it.x, it.y, 20, GREEN);
                break;
            case MY_BLACK_BLUE:
                DrawText(it.text.c_str(), it.x, it.y, 20, BLUE);
                break;
            case MY_BLACK_YELLOW:
                DrawText(it.text.c_str(), it.x, it.y, 20, YELLOW);
                break;
            case MY_BLACK_MAGENTA:
                DrawText(it.text.c_str(), it.x, it.y, 20, MAGENTA);
                break;
            case MY_BLACK_WHITE:
                DrawText(it.text.c_str(), it.x, it.y, 20, WHITE);
                break;
            case MY_RED:
                DrawText(it.text.c_str(), it.x, it.y, 20, RED);
                break;
            case MY_GREEN:
                DrawText(it.text.c_str(), it.x, it.y, 20, GREEN);
                break;
            case MY_BLUE:
                DrawText(it.text.c_str(), it.x, it.y, 20, BLUE);
                break;
            case MY_YELLOW:
                DrawText(it.text.c_str(), it.x, it.y, 20, YELLOW);
                break;
            case MY_MAGENTA:
                DrawText(it.text.c_str(), it.x, it.y, 20, MAGENTA);
                break;
            case MY_WHITE:
                DrawText(it.text.c_str(), it.x, it.y, 20, WHITE);
                break;
            default:
                break;
        }
    }
    ClearBackground(BLACK);

    BeginMode3D(_camera);
    for (auto &it : _cubeToDraw) {
        switch (it.color) {
            case MY_RED:
                DrawCube(it.pos, it.width, it.height, it.length, RED);
                break;
            case MY_GREEN:
                DrawCube(it.pos, it.width, it.height, it.length, GREEN);
                break;
            case MY_BLUE:
                DrawCube(it.pos, it.width, it.height, it.length, BLUE);
                break;
            case MY_YELLOW:
                DrawCube(it.pos, it.width, it.height, it.length, YELLOW);
                break;
            case MY_MAGENTA:
                DrawCube(it.pos, it.width, it.height, it.length, MAGENTA);
                break;
            case MY_WHITE:
                DrawCube(it.pos, it.width, it.height, it.length, WHITE);
                break;
            case MY_BLACK_RED:
                DrawCube(it.pos, it.width, it.height, it.length, RED);
                break;
            case MY_BLACK_GREEN:
                DrawCube(it.pos, it.width, it.height, it.length, GREEN);
                break;
            case MY_BLACK_BLUE:
                DrawCube(it.pos, it.width, it.height, it.length, BLUE);
                break;
            case MY_BLACK_YELLOW:
                DrawCube(it.pos, it.width, it.height, it.length, YELLOW);
                break;
            case MY_BLACK_MAGENTA:
                DrawCube(it.pos, it.width, it.height, it.length, MAGENTA);
                break;
            case MY_BLACK_WHITE:
                DrawCube(it.pos, it.width, it.height, it.length, WHITE);
                break;
            default:
                break;
        }
    }
    if (_rotate == true) {
       _camera.position = _MovedPosition;
       _MovedPosition.x = _camera.position.x * cos(0.01) - _camera.position.z * sin(0.01);
        _MovedPosition.z = _camera.position.x * sin(0.01) + _camera.position.z * cos(0.01);
    }
    EndMode3D();
    EndDrawing();
    _textToDraw.clear();
    _cubeToDraw.clear();
}

void ArcadeGraphs::LibrayLib::checkEvent()
{
    _inputV.clear();
    if (IsKeyReleased(KEY_ONE)) {
        _inputV.push_back(Input::KEY_1);
    }
    if (IsKeyReleased(KEY_TWO)) {
        _inputV.push_back(Input::KEY_2);
    }
    if (IsKeyReleased(KEY_ESCAPE)) {
        _inputV.push_back(Input::ESCAPE);
    }
    if (IsKeyDown(KEY_UP)) {
        _inputV.push_back(Input::UP_ARROW);
    }
    if (IsKeyDown(KEY_DOWN)) {
        _inputV.push_back(Input::DOWN_ARROW);
    }
    if (IsKeyDown(KEY_LEFT)) {
        _inputV.push_back(Input::LEFT_ARROW);
    }
    if (IsKeyDown(KEY_RIGHT)) {
        _inputV.push_back(Input::RIGHT_ARROW);
    }
    if (IsKeyReleased(KEY_ENTER)) {
        _inputV.push_back(Input::ENTER);
    }
    if (IsKeyReleased(KEY_SPACE)) {
        _inputV.push_back(Input::SPACE);
    }
    if (IsKeyReleased(KEY_W)) {
        if (_rotate == true) {
            _rotate = false;
            _camera.position = _startCamera;
        }
        else {
            _rotate = true;
        }
    }
}

void ArcadeGraphs::LibrayLib::playSound(std::string path)
{
    if (_sounds.find(path) != _sounds.end()) {
        if (IsSoundPlaying(_sounds[path]) == false)
        PlaySound(_sounds[path]);
    }
}

void ArcadeGraphs::LibrayLib::setSound(std::vector<std::string> paths)
{
    for (auto &it : paths) {
        if (_sounds.find(it) == _sounds.end())
            _sounds[it] = LoadSound(it.c_str());
    }
}