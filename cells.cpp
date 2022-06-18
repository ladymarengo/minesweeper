#include "minesweeper.h"

void Cells::init()
{
	spawn_cells();
}

void Cells::handle_event( SDL_Event* e, GameState *game_state)
{
    for( int i = 0; i < TOTAL_CELLS; ++i )
        m_cells[i].handle_event(e, game_state);
}
	
void Cells::render(SpriteSheet *texture, SDL_Renderer* renderer)
{
    for( int i = 0; i < TOTAL_CELLS; ++i )
        m_cells[i].render(texture, renderer);
}

void Cells::spawn_cells()
{
    int cell{0};

    for (int row = 0; row < CELL_LINE; row++)
    {
        for (int col = 0; col < CELL_LINE; col++, cell++)
        {
            m_cells[cell].init(OFFSET_WIDTH + col * CELL_SIZE, OFFSET_HEIGTH + row * CELL_SIZE, false);
        }
    }
}