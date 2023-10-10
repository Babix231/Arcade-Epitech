/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** main
*/

#include <iostream>
#include "./core/Core.hpp"
int main(int ac, char **av)
{
    if (ac != 2) {
        std::cout << "Usage: ./arcade [./lib/xxxx.so]" << std::endl;
        return 84;
    }
    ArcadeCore::Core core(av[1]);
    return 0;
}