#include "minesweeper.h"

Time::Time(int x, int y, Texture *texture) : Numbers{x, y, texture}
{
	start();
}

void Time::update()
{
	Numbers::update_number((SDL_GetTicks() - m_start_ticks) / 1000);
}

void Time::start()
{
	m_start_ticks = SDL_GetTicks();
}
