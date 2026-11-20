#include "Game_Class.hpp"
#include <raylib.h>

void Game::InitParticle(){for (size_t i = 0; i < NOP; i++) ParticlePos[i] = float(GetRandomValue(0, 800)/800.0f);}