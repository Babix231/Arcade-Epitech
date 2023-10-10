/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** Libhandler
*/

#include "Libhandler.hpp"

ArcadeCore::Libhandler::Libhandler()
{

}

ArcadeCore::Libhandler::~Libhandler()
{

}

void * ArcadeCore::Libhandler::loadLibrary(const std::string &path)
{
    void *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        throw ArcadeCore::LibhandlerException("Cannot open library");
    }
    return handle;
}

void * ArcadeCore::Libhandler::loadFunction(void *handle, const std::string &name)
{
    void *func = dlsym(handle, name.c_str());
    if (!func) {
        throw ArcadeCore::LibhandlerException("Cannot load function");
    }
    return func;
}

void ArcadeCore::Libhandler::unloadLibrary(void *handle)
{
    dlclose(handle);
}

void ArcadeCore::Libhandler::refreshLibs()
{
    std::vector<std::string> oldLibGamesPath = _libGamesPath;
    std::vector<std::string> oldLibGraphsPath = _libGraphsPath;
    _libGamesPath.clear();
    _libGraphsPath.clear();
    std::ifstream file("./lib/");
    std::string line;
    if (!file.is_open()) {
        throw ArcadeCore::LibhandlerException("Cannot open library");
    }
    for (const auto & entry : std::filesystem::directory_iterator("./lib/")) {
        if (entry.path().filename().string()[0] != '.') {
            std::string path = "./lib/" + entry.path().filename().string();
            void *handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!handle) {
                std::string error = std::string(dlerror());
                throw ArcadeCore::LibhandlerException("Cannot open library: " + error);
            }
            if (dlsym(handle, "createGame")) {
                if (std::find(_libGamesPath.begin(), _libGamesPath.end(), path) == _libGamesPath.end())
                    _libGamesPath.push_back(path);
            }
            else if (dlsym(handle, "createGraph")) {
                if (std::find(_libGraphsPath.begin(), _libGraphsPath.end(), path) == _libGraphsPath.end())
                    _libGraphsPath.push_back(path);
            }
            else {
                std::string error = std::string(dlerror());
                throw ArcadeCore::LibhandlerException("Cannot load symbol createGame or createGraph: " + error);
            }
        }
    }
}