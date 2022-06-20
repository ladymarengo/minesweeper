#include "minesweeper.h"

void Cells::init()
{
    spawn_bombs();
    spawn_cells();
    m_flags = TOTAL_BOMBS;
}

void Cells::reset()
{
    for (int i = 0; i < TOTAL_CELLS; ++i)
        m_bombs[i] = false;

    init();
}

int Cells::get_flags()
{
    return (m_flags);
}

void Cells::handle_event(SDL_Event *e, GameState *game_state)
{
    for (int i = 0; i < TOTAL_CELLS; ++i)
        m_cells[i].handle_event(e, game_state, i, m_bombs, m_cells, &m_flags);
    if (check_victory())
        *game_state = victory;
    if (*game_state == defeat)
        highlight_bombs();
}

void Cells::render(CellTexture *texture, SDL_Renderer *renderer)
{
    for (int i = 0; i < TOTAL_CELLS; ++i)
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
        } while (m_bombs[bomb]);

        m_bombs[bomb] = true;
    }
}

bool Cells::check_victory()
{
    for (int i = 0; i < TOTAL_CELLS; ++i)
    {
        if (m_cells[i].get_state() == no_pressed)
            return (false);
    }
    return (true);
}

void Cells::highlight_bombs()
{
    for (int i = 0; i < TOTAL_CELLS; ++i)
    {
        if (m_cells[i].m_is_bomb && (m_cells[i].m_state == no_pressed || m_cells[i].m_state == flag))
            m_cells[i].m_state = bomb_no_pressed;
    }
}