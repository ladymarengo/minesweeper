#include "minesweeper.h"

void Cell::init(int x, int y, bool is_bomb)
{
	m_position.x = x;
	m_position.y = y;
	m_is_bomb = is_bomb;
	// if (m_is_bomb)
	// 	m_state = bomb_no_pressed;
	// else
	m_state = no_pressed;
}

void Cell::handle_event(SDL_Event *e, GameState *game_state, int cell, bool bombs[TOTAL_CELLS], Cell cells[TOTAL_CELLS])
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	if (e->type == SDL_MOUSEBUTTONDOWN && x >= m_position.x && x <= m_position.x + CELL_SIZE && y >= m_position.y && y <= m_position.y + CELL_SIZE)
	{
		switch (e->button.button)
		{
		case SDL_BUTTON_LEFT:
			switch (m_state)
			{
			case no_pressed:
			case flag:
				if (m_is_bomb)
				{
					m_state = bomb_pressed;
					*game_state = defeat;
				}
				else
				{
					open(cell, bombs, cells);
				}
				break;
			default:
				break;
			}
		case SDL_BUTTON_RIGHT:
			switch (m_state)
			{
			case no_pressed:
				m_state = flag;
				break;
			case flag:
				m_state = no_pressed;
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

void Cell::render(CellTexture *texture, SDL_Renderer *renderer)
{
	texture->render(m_position.x, m_position.y, texture->get_state_rect(m_state), renderer);
}

int Cell::count_neighbours(int cell, bool bombs[TOTAL_CELLS])
{
	int count{0};

	count += (cell - CELL_LINE >= 0 && bombs[cell - CELL_LINE]) + (cell + CELL_LINE < TOTAL_CELLS && bombs[cell + CELL_LINE]);

	if (cell % CELL_LINE != 0)
	{
		count += bombs[cell - 1] + (cell - CELL_LINE - 1 >= 0 && bombs[cell - CELL_LINE - 1]) + (cell + CELL_LINE - 1 < TOTAL_CELLS && bombs[cell + CELL_LINE - 1]);
	}

	if (cell % CELL_LINE != CELL_LINE - 1)
	{
		count += bombs[cell + 1] + (cell - CELL_LINE + 1 >= 0 && bombs[cell - CELL_LINE + 1]) + (cell + CELL_LINE + 1 < TOTAL_CELLS && bombs[cell + CELL_LINE + 1]);
	}

	return (count);
}

CellType Cell::get_state()
{
	return (m_state);
}

void Cell::open(int cell, bool bombs[TOTAL_CELLS], Cell cells[TOTAL_CELLS])
{
	int neighbours = count_neighbours(cell, bombs);

	if (!neighbours)
	{
		m_state = empty;
		open_neighbours(cell, bombs, cells);
	}
	else
		m_state = static_cast<CellType>(one - 1 + neighbours);
}

void Cell::open_neighbours(int cell, bool bombs[TOTAL_CELLS], Cell cells[TOTAL_CELLS])
{
	if (cell - CELL_LINE >= 0 && cells[cell - CELL_LINE].get_state() == no_pressed)
		cells[cell - CELL_LINE].open(cell - CELL_LINE, bombs, cells);

	if (cell + CELL_LINE < TOTAL_CELLS && cells[cell + CELL_LINE].get_state() == no_pressed)
		cells[cell + CELL_LINE].open(cell + CELL_LINE, bombs, cells);

	if (cell % CELL_LINE != 0)
	{
		if (cells[cell - 1].get_state() == no_pressed)
			cells[cell - 1].open(cell - 1, bombs, cells);
		if (cell - CELL_LINE - 1 >= 0 && cells[cell - CELL_LINE - 1].get_state() == no_pressed)
			cells[cell - CELL_LINE - 1].open(cell - CELL_LINE - 1, bombs, cells);
		if (cell + CELL_LINE - 1 < TOTAL_CELLS && cells[cell + CELL_LINE - 1].get_state() == no_pressed)
			cells[cell + CELL_LINE - 1].open(cell + CELL_LINE - 1, bombs, cells);
	}

	if (cell % CELL_LINE != CELL_LINE - 1)
	{
		if (cells[cell + 1].get_state() == no_pressed)
			cells[cell + 1].open(cell + 1, bombs, cells);
		if (cell - CELL_LINE + 1 >= 0 && cells[cell - CELL_LINE + 1].get_state() == no_pressed)
			cells[cell - CELL_LINE + 1].open(cell - CELL_LINE + 1, bombs, cells);
		if (cell + CELL_LINE + 1 < TOTAL_CELLS && cells[cell + CELL_LINE + 1].get_state() == no_pressed)
			cells[cell + CELL_LINE + 1].open(cell + CELL_LINE + 1, bombs, cells);
	}
}