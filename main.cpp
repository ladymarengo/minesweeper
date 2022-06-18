#include "minesweeper.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool init()
{
    try
    {
        if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
            throw "SDL could not initialize!";
        
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
            throw "Warning: Linear texture filtering not enabled!";

        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
            throw "Window could not be created!";

        gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        if( gRenderer == NULL )
            throw "Renderer could not be created!";

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
            throw "SDL_image could not initialize!";
    }
    catch (const char* exception)
    {
        std::cerr << "Error: " << exception << '\n';
        return false;
    }
    return true;
}

void close()
{	
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}

void spawn_cells(Cell cells[TOTAL_CELLS])
{
    int cell{0};
    for (int row = 0; row < CELL_LINE; row++)
    {
        for (int col = 0; col < CELL_LINE; col++, cell++)
        {
            cells[cell].init(OFFSET_WIDTH + col * CELL_SIZE, OFFSET_HEIGTH + row * CELL_SIZE, false);
        }
    }
}

int main(int argc, char* args[])
{
    SpriteSheet texture;

    try
    {
        if( !init() )
            throw "Failed to initialize!\n";
        
        texture.load_from_file("cells.png", gRenderer);    
    }
    catch (const char* exception)
    {
        std::cerr << "Error: " << exception << '\n';
        close();
        return 0;
    }

    Cell cells[TOTAL_CELLS];
    spawn_cells(cells);

    SDL_Event e;

    while(true)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                close();
                return 0;
            }

            for( int i = 0; i < TOTAL_CELLS; ++i )
                cells[i].handle_event(&e);
        }

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
        SDL_RenderClear( gRenderer );

        for( int i = 0; i < TOTAL_CELLS; ++i )
                cells[i].render(&texture, gRenderer);

        SDL_RenderPresent( gRenderer );
    }
	close();
	return 0;
}