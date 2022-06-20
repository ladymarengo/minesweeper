#include "minesweeper.h"

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

bool init()
{
    try
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
            throw "SDL could not initialize!";

        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            throw "Warning: Linear texture filtering not enabled!";

        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
            throw "Window could not be created!";

        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (gRenderer == NULL)
            throw "Renderer could not be created!";

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
            throw "SDL_image could not initialize!";
    }
    catch (const char *exception)
    {
        std::cerr << "Error: " << exception << '\n';
        return false;
    }
    return true;
}

void close()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[])
{
    CellTexture texture;

    try
    {
        if (!init())
            throw "Failed to initialize!\n";

        texture.load_from_file("./assets/cells.png", gRenderer);
    }
    catch (const char *exception)
    {
        std::cerr << "Error: " << exception << '\n';
        close();
        return 0;
    }

    Cells cells{};
    cells.init();

    GameState game_state{in_game};
    SDL_Event e;

    while (true)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                close();
                return 0;
            }

            if (game_state == in_game)
                cells.handle_event(&e, &game_state);

            if (game_state != in_game && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
            {
                cells.reset();
                game_state = in_game;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
        SDL_RenderClear(gRenderer);

        cells.render(&texture, gRenderer);

        SDL_RenderPresent(gRenderer);
    }
    close();
    return 0;
}