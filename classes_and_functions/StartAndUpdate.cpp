#include <raylib.h>
#include <glad.h>

#include "StartAndUpdate.hpp"

const char *fragShader{LoadFileText("Shaders/Frag.glsl")};
const char *compShader{LoadFileText("Shaders/Comp.glsl")};
unsigned int CompShad;
unsigned int CompProg;

Shader shader;
RenderTexture2D RT2;

#define GLSL_Version 430

void CreateComputeShader(){
    CompShad = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(CompShad, 1, &compShader, NULL);
    glCompileShader(CompShad);

    CompProg = glCreateProgram();
    glAttachShader(CompProg, CompShad);
    glLinkProgram(CompProg);
}


void Start(Game *game, GLuint *Current_Particles){
    SetTargetFPS(game->getFPS());

    CreateComputeShader();

    shader = LoadShader(0, TextFormat("Shaders/Frag.glsl", GLSL_Version));
    RT2 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    glGenBuffers(1, Current_Particles);
        
    int SNOP_frag = GetShaderLocation(shader, "NumberOfParticles");
    SetShaderValue(shader, SNOP_frag, &game->ANOP, SHADER_UNIFORM_INT);
    
    glUseProgram(CompProg);
    int SNOP_comp = glGetUniformLocation(CompProg, "NumberOfParticles");
    glUniform1i(SNOP_comp, game->ANOP);
    glUseProgram(0);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, *Current_Particles);
    glBufferData(
        GL_SHADER_STORAGE_BUFFER,
        game->ParticlePos.size() * sizeof(game->ParticlePos[0]),
        game->ParticlePos.data(),
        GL_DYNAMIC_DRAW
    );
}

void Update(Game *game){
    glUseProgram(CompProg);
    glDispatchCompute((game->NOP/2 + 63) / 64, 1, 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void Renderer(){
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

void UnloadShader(){
    UnloadFileText((char*)fragShader);
    UnloadFileText((char*)compShader);
    UnloadShader(shader);
    CloseWindow();
}