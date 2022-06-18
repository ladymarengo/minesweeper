#include "minesweeper.h"

// class SpriteSheet
// {
// 	public:
// 		SpriteSheet();
// 		~SpriteSheet();
// 		bool loadFromFile( std::string path );
// 		void free();
// 		void render( int x, int y, SDL_Rect* clip;
		
//         int getWidth();
// 		int getHeight();
//         SDL_Rect *SpriteSheet::getState(CellType state);

// 	private:
// 		SDL_Texture* mTexture;
// 		int mWidth;
// 		int mHeight;
//         SDL_Rect m_cell_states[CELL_LINE];
// };

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

bool SpriteSheet::loadFromFile( std::string path, SDL_Renderer* renderer)
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

    m_cell_states[0].x = 0;
	m_cell_states[0].y = 0;
	m_cell_states[0].w = CELL_SIZE;
	m_cell_states[0].h = CELL_SIZE;

    m_cell_states[2].x = CELL_SIZE * 2;
	m_cell_states[2].y = 0;
	m_cell_states[2].w = CELL_SIZE;
	m_cell_states[2].h = CELL_SIZE;

	return (true);
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

int SpriteSheet::getWidth()
{
	return mWidth;
}

int SpriteSheet::getHeight()
{
	return mHeight;
}

SDL_Rect *SpriteSheet::getState(CellType state)
{
	return &m_cell_states[state];
}