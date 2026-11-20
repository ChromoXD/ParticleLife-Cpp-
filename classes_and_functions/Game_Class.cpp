#include "Game_Class.hpp"
#include <raylib.h>
#include <ctime>
#include <bits/stdc++.h>
#include <random>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int RandomFactor()
{
    std::time_t now{std::time(nullptr)};
    std::tm *localTIme{std::localtime(&now)};
    int hour{localTIme->tm_hour};
    int min{localTIme->tm_min};
    int sec{localTIme->tm_sec};

    int factor{hour + min + sec};

    return factor;
}

void Game::InitParticle(){

    for (size_t i = 0; i < NOP; i++) ParticlePos[i] = float(std::uniform_int_distribution<int>(1, 800)(rng)/800.0f);
}