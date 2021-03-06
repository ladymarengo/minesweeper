#include "minesweeper.h"

Texture::Texture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture()
{
	free();
}

bool Texture::load_from_file( std::string path, SDL_Renderer* renderer)
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

	return (true);
}

void Texture::free()
{
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture::render( int x, int y, SDL_Renderer* renderer, SDL_Rect* clip)
{
	SDL_Rect renderQuad{x, y, mWidth, mHeight};
	if (clip)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	
	SDL_RenderCopy( renderer, mTexture, clip, &renderQuad );
}
