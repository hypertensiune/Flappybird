#include <SDL2/SDL.h>
#include <iostream>

#include "Pipe.h"
#include "defs.h"

class Bird
{
    private:
        float velocity;
        float acceleration;

        SDL_Rect pos;

        SDL_Texture *up;
        SDL_Texture *down;
        SDL_Texture *mid;
        SDL_Texture *currentRenderingTexture;
        SDL_Renderer *renderer;

        int animationFrames;

    public:
        int score;

        Bird(SDL_Texture *up, SDL_Texture *mid, SDL_Texture *down, SDL_Renderer *renderer);

        void init();
        void render();
        void update(bool jump, float elapsedTime);
        void animation();
        bool collisionDetector(Pipe *pipe);
};