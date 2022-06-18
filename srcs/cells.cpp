#include "minesweeper.h"

void Cells::init()
{
    spawn_bombs();
	spawn_cells();
}

void Cells::reset()
{
    for( int i = 0; i < TOTAL_CELLS; ++i )
        m_bombs[i] = false;

    init();
}

void Cells::handle_event( SDL_Event* e, GameState *game_state)
{
    for( int i = 0; i < TOTAL_CELLS; ++i )
        m_cells[i].handle_event(e, game_state, i, m_bombs, m_cells);
    if (check_victory())
        *game_state = victory;
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
            m_cells[cell].init(OFFSET_WIDTH + col * CELL_SIZE, OFFSET_HEIGTH + row * CELL_SIZE, m_bombs[cell]);
        }
    }
}

void Cells::spawn_bombs()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> rand_gen(0, TOTAL_CELLS);
    int bomb{};

    for (int count = 0; count < TOTAL_BOMBS; count++)
    {
        do
        {
            bomb = rand_gen(rng);
        }
        while (m_bombs[bomb]);

        m_bombs[bomb] = true;
    }
}

bool Cells::check_victory()
{
    for( int i = 0; i < TOTAL_CELLS; ++i )
    {
        if (m_cells[i].get_state() == no_pressed)
            return (false);
    }
    return (true);
}

// void    Cells::open_neighbours(int cell)
// {
//     if (cell - CELL_LINE >= 0)
//     {
//         m_cells[cell - CELL_LINE].open(cell, m_bombs);
//         if (m_cells[cell - CELL_LINE].get_state() == empty)
//             open_neighbours(cell - CELL_LINE);
//     }

    
// 	// 		+ (cell + CELL_LINE < TOTAL_CELLS && bombs[cell + CELL_LINE]);

// 	// if (cell % CELL_LINE != 0)
// 	// {
// 	// 	count += bombs[cell - 1] \
// 	// 		+ (cell - CELL_LINE - 1 >= 0 && bombs[cell - CELL_LINE - 1]) \
// 	// 		+ (cell + CELL_LINE - 1 < TOTAL_CELLS && bombs[cell + CELL_LINE - 1]);
// 	// }

// 	// if (cell % CELL_LINE != CELL_LINE - 1)
// 	// {
// 	// 	count += bombs[cell + 1] \
// 	// 		+ (cell - CELL_LINE + 1 >= 0 && bombs[cell - CELL_LINE + 1]) \
// 	// 		+ (cell + CELL_LINE + 1 < TOTAL_CELLS && bombs[cell + CELL_LINE + 1]);
// 	// }
// }