#include "Game_Class.hpp"
#include <raylib.h>
#include <iostream>

void Game::UpdateTime(){
        time += 0.1;
}

void Game::InitParticle(){
        for (size_t i = 0; i < ParticlePos.size(); i++) ParticlePos[i] = float(GetRandomValue(0, 800)/800.0f);

        for (size_t i = 0; i < Next_ParticlePos.size(); i++) Next_ParticlePos[i] = 0;
}