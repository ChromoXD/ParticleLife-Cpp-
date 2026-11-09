#pragma once
#include <string>
#include <glad.h>
#include <raylib.h>

unsigned int CreateShader(const char *ShaderSource, int SHADER_TYPE, std::string type);

int width{800}, height{800};
GLuint Current_Particles, Next_Particles, Number_Of_Particles;

const char *Title{"Simulation"};