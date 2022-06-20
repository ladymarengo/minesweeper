#include "minesweeper.h"

CellTexture::CellTexture()
{
    set_states();
}

CellTexture::~CellTexture()
{
    free();
}

void CellTexture::set_states()
{
    int state{0};

    for (int row = 0; row < 4; row++)
    {
        for (int cell = 0; cell < 4 && state < (int)total; cell++, state++)
        {
            m_cell_states[state].x = CELL_SIZE * cell;
            m_cell_states[state].y = CELL_SIZE * row;
            m_cell_states[state].w = CELL_SIZE;
            m_cell_states[state].h = CELL_SIZE;
        }
    }
}

SDL_Rect *CellTexture::get_state_rect(CellType state)
{
    return &m_cell_states[state];
}