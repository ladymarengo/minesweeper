#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 760
#define CELL_SIZE 40
#define CELL_LINE 16

enum CellType
{
    no_pressed,
    flag,
    empty,
    bomb_pressed,
    bomb_no_pressed,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    total,
};

class SpriteSheet
{
	public:
		SpriteSheet();
		~SpriteSheet();
		bool loadFromFile( std::string path, SDL_Renderer* renderer);
		void free();
		void render( int x, int y, SDL_Rect* clip, SDL_Renderer* renderer);
		
        int getWidth();
		int getHeight();
        SDL_Rect *getState(CellType state);

	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
        SDL_Rect m_cell_states[CELL_LINE];
};

class Cell
{
	public:
		Cell(int x, int y, bool is_bomb);
		void handleEvent( SDL_Event* e );
		void render(SpriteSheet *texture, SDL_Renderer* renderer);

	private:
		SDL_Point m_position;
		CellType m_state;
        bool m_is_bomb;
};

#endif