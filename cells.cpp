#include "minesweeper.h"

void Cell::init(int x, int y, bool is_bomb)
{
	m_position.x = x;
    m_position.y = y;
    m_is_bomb = is_bomb;
    m_state = no_pressed;
}

void Cell::handle_event( SDL_Event* e, GameState *game_state)
{
    int x, y;
	SDL_GetMouseState( &x, &y );

	if(e->type == SDL_MOUSEBUTTONDOWN && x >= m_position.x && x <= m_position.x + CELL_SIZE && y >= m_position.y && y <= m_position.y + CELL_SIZE)
	{
		switch(e->button.button)
		{
			case SDL_BUTTON_LEFT:
				switch(m_state)
				{
					case no_pressed:
					case flag:
						if (m_is_bomb)
						{
							m_state = bomb_pressed;
							*game_state = defeat;
						}
						else
							m_state = empty;
						break;
					default:
						break;
				}
			case SDL_BUTTON_RIGHT:
				switch(m_state)
				{
					case no_pressed:
						m_state = flag;
						break;
					default:
						break;
				}
			default:
				break;
		}
        
	}
}
	
void Cell::render(SpriteSheet *texture, SDL_Renderer* renderer)
{
	texture->render( m_position.x, m_position.y, texture->get_state_rect(m_state), renderer);
}
