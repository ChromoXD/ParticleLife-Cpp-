#pragma once
#include <unordered_map>
#include <string>
#include <glad.h>
#include <raylib.h>

unsigned int CreateShader(const char *ShaderSource, int SHADER_TYPE, std::string type);

std::unordered_map<std::string, const char *> Location = {
    {"Fragment_Shader", "Shaders/Frag.glsl"},
    {"Vertex_Shader", "Shaders/Vert.glsl"},
    {"Compute_Shader", "Shaders/Comp.glsl"}};

int width{800}, height{800};

Shader shader;
RenderTexture2D RT2;
GLuint Current_Particles, Next_Particles;

const char *Title{"Simulation"};
const char *fragShader{LoadFileText(Location["Fragment_Shader"])};
const char *compShader{LoadFileText(Location["Compute_Shader" ])};
unsigned int CompShad;
unsigned int CompProg;