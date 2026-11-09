#include <raylib.h>
#include <iostream>
#include <glad.h>
#include <vector>
#include <algorithm> 

#include "main.hpp"
#include "classes_and_functions/Shader_Function.hpp"
#include "classes_and_functions/Game_Class.hpp"

#define GLSL_Version 430

void CreateComputeShader();
void Start();
void Update();

Game game(60, 40);

int main()
{
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(width, height, Title);

    Start();
    
    while (!WindowShouldClose())
    {
        game.UpdateTime();

        Update();
    
        BeginTextureMode(RT2);
            ClearBackground((Color){ 15, 14, 18, 255 });
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
        EndTextureMode();
            
            
        BeginDrawing();
        
            BeginShaderMode(shader);
                ClearBackground((Color){ 15, 14, 18, 255 });
                DrawTextureEx(RT2.texture, (Vector2){ 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
            EndShaderMode();

        EndDrawing();
    }

    UnloadFileText((char *)fragShader);
    UnloadFileText((char *)compShader);
    UnloadShader(shader);
    CloseWindow();

    return 0;
}

void CreateComputeShader(){
    CompShad = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(CompShad, 1, &compShader, NULL);
    glCompileShader(CompShad);

    CompProg = glCreateProgram();
    glAttachShader(CompProg, CompShad);
    glLinkProgram(CompProg);
}

void Start(){
    SetTargetFPS(game.getFPS());

    CreateComputeShader();

    shader = LoadShader(0, TextFormat(Location["Fragment_Shader"], GLSL_Version));
    RT2 = LoadRenderTexture(width, height);

    glGenBuffers(1, &Current_Particles);
        
    int SNOP_frag = GetShaderLocation(shader, "NumberOfParticles");
    SetShaderValue(shader, SNOP_frag, &game.NOP, SHADER_UNIFORM_INT);
    
    glUseProgram(CompProg);
    int SNOP_comp = glGetUniformLocation(CompProg, "NumberOfParticles");
    glUniform1i(SNOP_comp, game.NOP);
    glUseProgram(0);

    
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, Current_Particles);
    glBufferData(
        GL_SHADER_STORAGE_BUFFER,
        game.ParticlePos.size() * sizeof(game.ParticlePos[0]),
        game.ParticlePos.data(),
        GL_DYNAMIC_DRAW
    );

}

void Update(){
    // Running compute shader
    glUseProgram(CompProg);
    glDispatchCompute((game.NOP/2 + 63) / 64, 1, 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);


    glBindBuffer(GL_SHADER_STORAGE_BUFFER, Current_Particles);

    GLsizeiptr BufferSize = sizeof(game.ParticlePos[0]) * game.ParticlePos.size(); 
    float* BufferDataMap = (float*)glMapBufferRange(
        GL_SHADER_STORAGE_BUFFER,
        0,
        BufferSize,
        GL_MAP_READ_BIT
    );

    if (BufferDataMap)
    {
        std::copy(BufferDataMap, BufferDataMap + game.ParticlePos.size(), game.ParticlePos.begin());
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    }
    

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, Current_Particles);
    glBufferData(
        GL_SHADER_STORAGE_BUFFER,
        game.ParticlePos.size() * sizeof(game.ParticlePos[0]),
        game.ParticlePos.data(),
        GL_DYNAMIC_DRAW
    );


    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}