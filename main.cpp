#include <raylib.h>
#include <iostream>
#include <glad.h>
#include <vector>

#include "main.hpp"
#include "classes_and_functions/Shader_Function.hpp"
#include "classes_and_functions/Game_Class.hpp"

#define GLSL_Version 430

Game game(60, 10);

int main()
{
    const char *Title{"Simulation"};
    const char *fragShader{LoadFileText(Location["Fragment_Shader"])};
    const char *compShader{LoadFileText(Location["Compute_Shader" ])};

    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(width, height, Title);

    Shader shader = LoadShader(0, TextFormat(Location["Fragment_Shader"], GLSL_Version));

    RenderTexture2D RT2 = LoadRenderTexture(width, height);

    GLuint Particles;
    glGenBuffers(1, &Particles);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, Particles);
    glBufferData(
        GL_SHADER_STORAGE_BUFFER,
        game.ParticlePos.size() * sizeof(game.ParticlePos[0]),
        game.ParticlePos.data(),
        GL_DYNAMIC_DRAW
    );
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, Particles);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);




    while (!WindowShouldClose())
    {
        game.UpdateTime();
    
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