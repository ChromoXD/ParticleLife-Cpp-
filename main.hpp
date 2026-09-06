#pragma once
#include <unordered_map>
#include <vector>
#include <array>
#include <string>

unsigned int CreateShader(const char *ShaderSource, int SHADER_TYPE, std::string type);

std::unordered_map<std::string, const char *> Location = {
    {"Fragment_Shader", "Shaders/Frag.glsl"},
    {"Vertex_Shader", "Shaders/Vert.glsl"},
    {"Compute_Shader", "Shaders/Comp.glsl"}};

int width{800}, height{800};