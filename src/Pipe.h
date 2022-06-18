#ifndef PIPE_H_
#define PIPE_H_

#include <SDL2/SDL.h>
#include "defs.h"

struct Pipe
{
    SDL_Rect top_src, top_dst;
    SDL_Rect bottom_dst, bottom_src;

    bool passed;

    Pipe(int x, int height)
    {   
        bottom_dst.x = x;
        bottom_dst.y = HEIGHT - height;
        bottom_dst.w = PIPE_WIDTH;
        bottom_dst.h = height;

        bottom_src.x = 0;
        bottom_src.y = 0;
        bottom_src.w = PIPE_WIDTH_SRC;
        bottom_src.h = height;

        top_dst.x = x;
        top_dst.y = 0;
        top_dst.w = PIPE_WIDTH;
        top_dst.h = HEIGHT - height - PIPE_GAP;

        top_src.x = top_src.y = 0;
        top_src.w = PIPE_WIDTH_SRC;
        top_src.h = top_dst.h;

        passed = false;
    }

    void render(SDL_Renderer *renderer, SDL_Texture *tex)
    {
        SDL_RenderCopy(renderer, tex, &bottom_src, &bottom_dst);
        SDL_RenderCopyEx(renderer, tex, &top_src, &top_dst, 0, NULL, SDL_FLIP_VERTICAL);
    }
};

#endif