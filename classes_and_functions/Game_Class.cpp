#include "Game_Class.hpp"
#include <raylib.h>
#include <iostream>

void Game::UpdateTime(){
        time += 0.1;
}

void Game::InitParticle(){
        for (size_t i = 0; i < ParticlePos.size(); i++) {
                ParticlePos[i] = float(GetRandomValue(0, 800)/800.0f);
                std::cout << ParticlePos[i] << std::endl;
        }
}