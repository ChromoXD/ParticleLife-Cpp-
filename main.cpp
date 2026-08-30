#include <raylib.h>
#include <iostream>
// #include <glad.h>
#include <vector>

#include "main.hpp"
// #include "classes_and_functions/Shader_Function.hpp"
#include "classes_and_functions/Game_Class.hpp"

#define GLSL_Version 430

Game game(15, 200);

int main()
{
    const char *Title{"Simulation"};
    const char *fragShader{LoadFileText(Location["Fragment_Shader"])};
    const char *vertShader{LoadFileText(Location["Vertex_Shader"  ])};
    const char *compShader{LoadFileText(Location["Compute_Shader" ])};

    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(width, height, Title);
    // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    Shader shader = LoadShader(0, TextFormat(fragShader, GLSL_Version));

    RenderTexture2D RT2 = LoadRenderTexture(width, height);

    // glEnable(GL_CULL_FACE);

    // glGenVertexArrays(1, &VAO);
    // for (GLuint *i : {&VBO, &EBO})
    // {
    //     glGenBuffers(1, i);
    // }

    // glBindVertexArray(VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);



    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indeces), Indeces, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    // glEnableVertexAttribArray(0);
    // glEnableVertexAttribArray(1);
    // glBindVertexArray(0);

    // GraphicsProgram = glCreateProgram();

    // FragmentShader = CreateShader(fragShader, GL_FRAGMENT_SHADER, "FRAGMENT_SHADER");
    // VertexShader = CreateShader(vertShader, GL_VERTEX_SHADER, "VERTEX_SHADER");

    // glAttachShader(GraphicsProgram, FragmentShader);
    // glAttachShader(GraphicsProgram, VertexShader);

    // glLinkProgram(GraphicsProgram);

    // glUseProgram(GraphicsProgram);

    // GLint TimeLoc = glGetUniformLocation(GraphicsProgram, "time");

    SetTargetFPS(game.getFPS());

    while (!WindowShouldClose())
    {
        game.UpdateTime();
        

        BeginDrawing();

        EndDrawing();
    }

    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    // glDeleteProgram(GraphicsProgram);
                UnloadFileText((char *)fragShader);
                UnloadFileText((char *)compShader);
    // glDeleteShader(FragmentShader);
    // glDeleteShader(VertexShader);
    CloseWindow();

    return 0;
}