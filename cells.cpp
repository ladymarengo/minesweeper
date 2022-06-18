#include "minesweeper.h"

// enum CellType
// {
//     no_pressed,
//     flag,
//     empty,
//     bomb_pressed,
//     bomb_no_pressed,
//     one,
//     two,
//     three,
//     four,
//     five,
//     six,
//     seven,
//     eight,
//     total,
// };

// class Cell
// {
// 	public:
// 		Cell(int x, int y, bool is_bomb);
// 		void handleEvent( SDL_Event* e );
// 		void render();

// 	private:
// 		SDL_Point m_position;
// 		CellType m_state;
//         bool m_is_bomb;
// };

Cell::Cell(int x, int y, bool is_bomb)
{
	m_position.x = x;
    m_position.y = y;
    m_is_bomb = is_bomb;
    m_state = no_pressed;
}

void Cell::handleEvent( SDL_Event* e )
{
    int x, y;
	SDL_GetMouseState( &x, &y );

	if(e->type == SDL_MOUSEBUTTONDOWN && x >= m_position.x && x <= m_position.x + CELL_SIZE && y >= m_position.y && y <= m_position.y + CELL_SIZE)
	{
        switch(m_state)
			{
				case no_pressed:
				    m_state = empty;
				    break;
				case empty:
				    m_state = no_pressed;
				    break;
                default:
                    break;
			}
	}
}
	
void Cell::render(SpriteSheet *texture, SDL_Renderer* renderer)
{
	texture->render( m_position.x, m_position.y, texture->getState(m_state), renderer);
}
