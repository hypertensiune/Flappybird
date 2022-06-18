#include "Game.h"

Game::Game(const char *title, int width, int height)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    loadTextures();

    bird = new Bird(tex_playerDown, tex_playerMid, tex_playerUp, renderer);

    isRunning = true;
    gameover = false;

    ground1 = -WIDTH / 2;
    ground2 = WIDTH   / 2;

    srand(time(NULL));
}

void Game::init()
{
    bird->init();

    for(auto pipe : pipes)
        pipes.pop_front();

    pipes.push_back(new Pipe(WIDTH * 2 + PIPE_DISTANCE, rand() % 301 + 150));
    pipes.push_back(new Pipe(pipes.back()->bottom_dst.x + PIPE_DISTANCE, rand() % 301 + 150));
    pipes.push_back(new Pipe(pipes.back()->bottom_dst.x + PIPE_DISTANCE, rand() % 301 + 150));

    gameStarted = false;
    gameover = false;

    render();
}   

void Game::Start()
{    
    // initialize everything before the game starts
    init();

    auto t1 = std::chrono::system_clock::now();
    auto t2 = t1;

    // main game loop
    while(isRunning)
    {
        t1 = t2;
        t2 = std::chrono::system_clock::now();
        
        std::chrono::duration<float> dt = t2 - t1;

        bool jump = false;
        while(SDL_PollEvent(&event))
        {  
            if(event.type == SDL_QUIT)
                isRunning = false;

            if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) || (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT))
                jump = gameStarted = true;
        }

        if(frameDelay > dt.count())
            SDL_Delay(frameDelay - dt.count());
        
        if(gameStarted)
        {
            update(jump, dt.count(), gameover);
            if(gameover)
                gameOver();
        }
    }

    Close();
}

void Game::update(bool jump, float elapsedTime, bool &gameover)
{
    bird->update(jump, elapsedTime);
    
    for(auto p : pipes)
    {
        p->bottom_dst.x -= PIPE_V;
        p->top_dst.x = p->bottom_dst.x;

        if(p->bottom_dst.x + p->bottom_dst.w < 0)
        {
            pipes.pop_front();
            pipes.push_back(new Pipe(pipes.back()->bottom_dst.x + PIPE_DISTANCE, rand() % 301 + 150));
        }

        if(bird->collisionDetector(p))
            gameover = true;
    }

    ground1 -= PIPE_V;
    ground2 -= PIPE_V;

    if(ground1 + WIDTH < 0)
        ground1 = WIDTH - 10;
    if(ground2 + WIDTH < 0)
        ground2 = WIDTH - 10;

    render();
}

void Game::gameOver()
{
    gameStarted = false;

    SDL_RenderCopy(renderer, tex_gameover, NULL, new SDL_Rect{WIDTH / 2 - 96, HEIGHT / 3, 192, 42});
    SDL_RenderPresent(renderer);

    SDL_Delay(1000);

    bool wait = true, playagain = false;
    while(wait)
    {
        while(SDL_PollEvent(&event))
        {   
            if(event.type == SDL_QUIT)
                wait = false;

            if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) || (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT))
                wait = false, playagain = true;
        }
    }

    if(playagain)
        Start();
    else 
        isRunning = false;
}

void Game::render()
{   
    SDL_RenderClear(renderer);
    
    // background
    SDL_RenderCopy(renderer, tex_background, NULL, NULL);

    // pipes
    for(auto pipe : pipes)
    {
        pipe->render(renderer, tex_pipe);
    }

    // score
    if(bird->score > 9)
    {
        SDL_RenderCopy(renderer, tex_numbers[bird->score / 10 % 10], NULL, new SDL_Rect{WIDTH / 2 - 20, 100, 40, 52});
        SDL_RenderCopy(renderer, tex_numbers[bird->score % 10], NULL, new SDL_Rect{WIDTH / 2 + 20, 100, 40, 52});
    }
    else
        SDL_RenderCopy(renderer, tex_numbers[bird->score], NULL, new SDL_Rect{WIDTH / 2, 100, 40, 52});

    // ground
    SDL_RenderCopy(renderer, tex_ground, NULL, new SDL_Rect{ground1, HEIGHT - GROUND_HEIGHT, WIDTH, GROUND_HEIGHT});
    SDL_RenderCopy(renderer, tex_ground, NULL, new SDL_Rect{ground2, HEIGHT - GROUND_HEIGHT, WIDTH, GROUND_HEIGHT});

    // player
    bird->render();

    SDL_RenderPresent(renderer);
}


void Game::loadTextures()
{
    tex_background = IMG_LoadTexture(renderer, "../sprites/background-day.png");
    tex_pipe = IMG_LoadTexture(renderer, "../sprites/pipe.png");
    tex_playerMid = IMG_LoadTexture(renderer, "../sprites/yellowbird-midflap.png");
    tex_playerUp = IMG_LoadTexture(renderer, "../sprites/yellowbird-upflap.png");
    tex_playerDown = IMG_LoadTexture(renderer, "../sprites/yellowbird-downflap.png");
    tex_ground = IMG_LoadTexture(renderer, "../sprites/base.png");
    tex_gameover = IMG_LoadTexture(renderer, "../sprites/gameover.png");
    

    for(int i = 0; i < 10; i++)
    {
        std::string path = "../sprites/" + std::to_string(i) + ".png";
        tex_numbers[i] = IMG_LoadTexture(renderer, path.c_str());
    }
}

void Game::Close()
{
    SDL_Quit();
}