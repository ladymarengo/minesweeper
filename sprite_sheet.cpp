#include "minesweeper.h"

SpriteSheet::SpriteSheet()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

SpriteSheet::~SpriteSheet()
{
	free();
}

bool SpriteSheet::load_from_file( std::string path, SDL_Renderer* renderer)
{
	free();

	SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
        throw "Unable to load image!";

    newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
    if( newTexture == NULL )
        throw "Unable to create texture!";
    
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    SDL_FreeSurface( loadedSurface );
    mTexture = newTexture;

    set_states();

	return (true);
}

void  SpriteSheet::set_states()
{
    int state{0};

    for (int row = 0; row < 4; row++)
    {
        for (int cell = 0; cell < 4, state < (int) total; cell++, state++)
        {
            m_cell_states[state].x = CELL_SIZE * cell;
            m_cell_states[state].y = CELL_SIZE * row;
            m_cell_states[state].w = CELL_SIZE;
            m_cell_states[state].h = CELL_SIZE;
        }
    }
}

void SpriteSheet::free()
{
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void SpriteSheet::render( int x, int y, SDL_Rect* clip, SDL_Renderer* renderer)
{
	SDL_Rect renderQuad = { x, y, clip->w, clip->h };
	SDL_RenderCopy( renderer, mTexture, clip, &renderQuad );
}

SDL_Rect *SpriteSheet::get_state_rect(CellType state)
{
	return &m_cell_states[state];
}