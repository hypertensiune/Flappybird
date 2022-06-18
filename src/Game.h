#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <list>
#include <chrono>
#include <random>
#include <time.h>
#include <string>

#include "Bird.h"
#include "Pipe.h"
#include "defs.h"

class Game
{
    public:
        SDL_Texture *tex_background;
        SDL_Texture *tex_ground;
        SDL_Texture *tex_playerUp;
        SDL_Texture *tex_playerMid;
        SDL_Texture *tex_playerDown;
        SDL_Texture *tex_pipe;
        SDL_Texture *tex_numbers[10];
        SDL_Texture *tex_gameover;

        bool isRunning;

        Game(const char *title, int _width, int _height);
        
        void Start();
        void Close();
        void update(bool jump, float elapsedTime, bool &gameover);
        void render();
        void gameOver();
        void init();

    private:
        SDL_Renderer *renderer;
        SDL_Window *window;

        SDL_Event event;

        Bird *bird;

        std::list<Pipe*> pipes;

        int ground1, ground2;

        bool gameStarted, gameover;

        void loadTextures();
};
