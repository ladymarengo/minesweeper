#include "minesweeper.h"

Smiley::Smiley()
{
	set_states();
}

void Smiley::render(SDL_Renderer* renderer, GameState game_state)
{
	Texture::render(SMILEY_OFFSET_WIDTH, SMILEY_OFFSET_HEIGTH, renderer, &m_states[game_state]);
}

void Smiley::set_states()
{
	for (int state = 0; state < 3; state++)
        {
            m_states[state].x = SMILEY_SIZE * state;
            m_states[state].y = 0;
            m_states[state].w = SMILEY_SIZE;
            m_states[state].h = SMILEY_SIZE;
        }
}

bool Smiley::handle_event(SDL_Event *e)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	if (e->type == SDL_MOUSEBUTTONDOWN
		&& x >= SMILEY_OFFSET_WIDTH && x <= SMILEY_OFFSET_WIDTH + SMILEY_SIZE
		&& y >= SMILEY_OFFSET_HEIGTH && y <= SMILEY_OFFSET_HEIGTH + SMILEY_SIZE)
		return (true);
	return (false);
}