#include "minesweeper.h"

Numbers::Numbers(int x, int y, Texture *texture) : m_x{x}, m_y{y}, m_texture{texture}
{
	set_numbers();
}

void Numbers::render(SDL_Renderer* renderer)
{
	if (m_number < 1000)
	{
		m_texture->render(m_x, m_y, renderer, &m_numbers[m_number / 100 % 10]);
		m_texture->render(m_x + NUMBER_WIDTH, m_y, renderer, &m_numbers[m_number / 10 % 10]);
		m_texture->render(m_x + NUMBER_WIDTH * 2, m_y, renderer, &m_numbers[m_number % 10]);
	}
}

void Numbers::set_numbers()
{
	int number{0};

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 4 && number < 10; col++, number++)
        {
            m_numbers[number].x = NUMBER_WIDTH * col;
            m_numbers[number].y = NUMBER_HEIGTH * row;
            m_numbers[number].w = NUMBER_WIDTH;
            m_numbers[number].h = NUMBER_HEIGTH;
        }
    }
}

void Numbers::update_number(int number)
{
	m_number = number;
}