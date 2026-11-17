#pragma once

#include "Game_Class.hpp"
#include <raylib.h>

extern void Start(Game *game, GLuint *Current_Particles);
extern void Update(Game *game, GLuint *Current_Particles);
extern void Renderer();
extern void UnloadShader();


