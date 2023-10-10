/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** Libhandler
*/

#pragma once
#include <iostream>
#include <dlfcn.h>
#include <exception>
#include <filesystem>
#include "../games/Igames.hpp"
#include "../graphs/Igraphs.hpp"
#include <memory>
#include <algorithm>
#include <vector>

namespace ArcadeCore {
class LibhandlerException : public std::exception {
    public:
        LibhandlerException(std::string const &message) : _message(message) {};
        const char *what() const noexcept override { return _message.c_str(); };
    protected:
    private:
        std::string _message;
};

class Libhandler {
    public:
        Libhandler();
        ~Libhandler();
        void refreshLibs();
        template<typename Object>
        std::shared_ptr<Object> loadAndGetlib(std::string libPath, std::string functionName)
        {
            void* libHandle = loadLibrary(libPath);

            Object* (*createFunc)() = (Object* (*)())loadFunction(libHandle, "create" + functionName);
            void (*deleteFunc)(Object*) = (void (*)(Object*))loadFunction(libHandle, "delete" + functionName);

            Object* obj = createFunc();
            return std::shared_ptr<Object>(obj, [=](Object* p) {
                deleteFunc(p);
                unloadLibrary(libHandle);
            });
        }
        std::vector<std::string> getLibGamesPath() { return _libGamesPath; };
        std::vector<std::string> getLibGraphsPath() { return _libGraphsPath; };
    protected:
    private:
     std::vector<std::string> _libGamesPath;
     std::vector<std::string> _libGraphsPath;
     void *loadLibrary(const std::string &path);
     void *loadFunction(void *handle, const std::string &name);
     void unloadLibrary(void *handle);
};
}