#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <random>


#define OFFSET_WIDTH 20
#define OFFSET_HEIGTH 120
#define CELL_SIZE 40
#define CELL_LINE 16
#define SCREEN_WIDTH CELL_LINE * CELL_SIZE + OFFSET_WIDTH * 2
#define SCREEN_HEIGHT CELL_LINE * CELL_SIZE + OFFSET_WIDTH + OFFSET_HEIGTH
#define TOTAL_CELLS CELL_LINE * CELL_LINE
#define TOTAL_BOMBS 40

enum GameState
{
    in_game,
    victory,
    defeat,
};

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
		bool load_from_file( std::string path, SDL_Renderer* renderer);
		void free();
		void render( int x, int y, SDL_Rect* clip, SDL_Renderer* renderer);
        SDL_Rect *get_state_rect(CellType state);

	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
        SDL_Rect m_cell_states[CELL_LINE];
        void set_states();
};

class Cell
{
	public:
        void init(int x, int y, bool is_bomb);
		void handle_event( SDL_Event* e, GameState *game_state, int cell, bool bombs[TOTAL_CELLS], Cell cells[TOTAL_CELLS]);
		void render(SpriteSheet *texture, SDL_Renderer* renderer);
        int count_neighbours(int cell, bool bombs[TOTAL_CELLS]);
        CellType get_state();
        void open(int cell, bool bombs[TOTAL_CELLS], Cell cells[TOTAL_CELLS]);

	private:
		SDL_Point m_position;
		CellType m_state;
        bool m_is_bomb;
        void open_neighbours(int cell, bool bombs[TOTAL_CELLS], Cell cells[TOTAL_CELLS]);
};

class Cells
{
    public:
        void init();
        void reset();
        void handle_event( SDL_Event* e, GameState *game_state);
		void render(SpriteSheet *texture, SDL_Renderer* renderer);

    private:
        Cell m_cells[TOTAL_CELLS];
        bool m_bombs[TOTAL_CELLS];
        void spawn_cells();
        void spawn_bombs();
        bool check_victory();
};

#endif