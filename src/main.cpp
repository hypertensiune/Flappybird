#include "Game.h"
#include "defs.h"
#undef main

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    Game game("Flappy bird", WIDTH, HEIGHT);

    game.Start();

    return 0;
}