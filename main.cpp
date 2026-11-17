#include <raylib.h>

#include "main.hpp"
#include "classes_and_functions/StartAndUpdate.hpp"

Game game(60, 10);

int main()
{
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(width, height, Title);

    Start(&game, &Current_Particles);
    
    while (!WindowShouldClose())
    {
        game.UpdateTime();

        Update(&game, &Current_Particles);
    
        Renderer();
    }

    UnloadShader();
    return 0;
}