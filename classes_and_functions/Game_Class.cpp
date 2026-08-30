#include "Game_Class.hpp"
#include <raylib.h>

void Game::UpdateTime(){
        time += 0.1;
}

void Game::InitParticle(){
        for (size_t i = 0; i < NOP; i++) Particles[i] = GetRandomValue(GetScreenWidth(), GetScreenHeight());
}