#include <raylib.h>
#include <iostream>
#include <glad.h>
#include <vector>

#include "main.hpp"
#include "classes_and_functions/Shader_Function.hpp"
#include "classes_and_functions/Game_Class.hpp"

#define GLSL_Version 430

void CreateComputeShader();
void Start();
void Update();

Game game(60, 10);

int main()
{
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(width, height, Title);
    
    CreateComputeShader();

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

        std::swap(Current_Particles, Next_Particles);
        
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
    shader = LoadShader(0, TextFormat(Location["Fragment_Shader"], GLSL_Version));
    RT2 = LoadRenderTexture(width, height);

    glGenBuffers(1, &Current_Particles);
    glGenBuffers(1, &Next_Particles);
}

void Update(){
    // Uploading Current Particle position to compute shader
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, Current_Particles);
    glBufferData(
        GL_SHADER_STORAGE_BUFFER,
        game.ParticlePos.size() * sizeof(game.ParticlePos[0]),
        game.ParticlePos.data(),
        GL_DYNAMIC_DRAW
    );
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, Current_Particles);
    
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, Next_Particles);
    // glBufferData(
    //     GL_SHADER_STORAGE_BUFFER,
    //     game.Next_ParticlePos.size() * sizeof(game.Next_ParticlePos[0]),
    //     game.Next_ParticlePos.data(),
    //     GL_DYNAMIC_DRAW
    // );
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, Next_Particles);
    
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    // Running compute shader
    glUseProgram(CompProg);
    glDispatchCompute(1, 1, 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);

    //Uploading Next Particle position to Fragment shader
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, Next_Particles);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, Next_Particles);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}