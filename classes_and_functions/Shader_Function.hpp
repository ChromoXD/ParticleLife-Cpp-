#pragma once

#include <glad.h>
#include <string>
#include <unordered_map>

extern unsigned int CreateShader(const char *ShaderSource, int SHADER_TYPE, std::string type);
extern char *Error_logger(GLuint Shader, std::string ShaderType, int * success, char * log_info);

extern GLuint ComputeShader,
       ComputeProgram, 
       GraphicsProgram, 
       FragmentShader, 
       VertexShader;

extern GLuint VBO, 
       VAO, 
       EBO;

std::unordered_map<std::string, const char *> Location = {
    {"Fragment_Shader", "Shaders/Frag.glsl"},
    {"Vertex_Shader", "Shaders/Vert.glsl"},
    {"Compute_Shader", "Shaders/Comp.glsl"}};

class ShaderFunctions{
    public: 
        void BindBuffers_SSBO(GLuint * Buffer, GLsizeiptr size, const void * data);
        void SSBO_DataPush(GLuint index, GLuint * Buffer, GLsizeiptr size, const void *data);
};