#pragma once
#include <string>
#include <glad.h>

unsigned int CreateShader(const char *ShaderSource, int SHADER_TYPE, std::string type);

int width{1000}, height{1000};
GLuint Current_Particles[2], Next_Particles, Number_Of_Particles;

const char *Title{"Simulation"};