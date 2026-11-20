#include <raylib.h>

#include "main.hpp"
#include "classes_and_functions/StartAndUpdate.hpp"

Game game(60, 400);

int main()
{
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(width, height, Title);

    Start(&game, &Current_Particles);
    
    while (!WindowShouldClose())
    {
        Update(&game);
        Renderer();
    }

    UnloadShader();
    return 0;
}