#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <random>

#define OFFSET_WIDTH 20
#define OFFSET_HEIGTH 120
#define CELL_SIZE 40
#define CELL_LINE 16
#define SCREEN_WIDTH CELL_LINE *CELL_SIZE + OFFSET_WIDTH * 2
#define SCREEN_HEIGHT CELL_LINE *CELL_SIZE + OFFSET_WIDTH + OFFSET_HEIGTH
#define TOTAL_CELLS CELL_LINE *CELL_LINE
#define TOTAL_BOMBS 40
#define NUMBER_WIDTH 35
#define NUMBER_HEIGTH 60
#define FLAGS_OFFSET_WIDTH 30
#define FLAGS_OFFSET_HEIGTH 30
#define TIME_OFFSET_WIDTH 545
#define TIME_OFFSET_HEIGTH 30
#define SMILEY_OFFSET_WIDTH 310
#define SMILEY_OFFSET_HEIGTH 30
#define SMILEY_SIZE 60

enum GameState
{
    in_game,
    victory,
    defeat,
};

enum CellType
{
    no_pressed,
    flag,
    empty,
    bomb_pressed,
    bomb_no_pressed,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    total,
};

class Texture
{
public:
    Texture();
    ~Texture();
    bool load_from_file(std::string path, SDL_Renderer *renderer);
    void free();
    virtual void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip);

protected:
    SDL_Texture *mTexture;
    int mWidth;
    int mHeight;
};

class CellTexture : public Texture
{
public:
    CellTexture();
    ~CellTexture();
    SDL_Rect *get_state_rect(CellType state);

private:
    SDL_Rect m_cell_states[CELL_LINE];
    void set_states();
};

class Cell
{
public:
    void init(int x, int y, bool is_bomb);
    void handle_event(SDL_Event *e, GameState *game_state, int cell, bool bombs[TOTAL_CELLS], Cell cells[TOTAL_CELLS], int *flags);
    void render(CellTexture *texture, SDL_Renderer *renderer);
    int count_neighbours(int cell, bool bombs[TOTAL_CELLS]);
    CellType get_state();
    void open(int cell, bool bombs[TOTAL_CELLS], Cell cells[TOTAL_CELLS]);

private:
    SDL_Point m_position;
    CellType m_state;
    bool m_is_bomb;
    void open_neighbours(int cell, bool bombs[TOTAL_CELLS], Cell cells[TOTAL_CELLS]);
};

class Cells
{
public:
    void init();
    void reset();
    void handle_event(SDL_Event *e, GameState *game_state);
    void render(CellTexture *texture, SDL_Renderer *renderer);
    int get_flags();

private:
    Cell m_cells[TOTAL_CELLS];
    bool m_bombs[TOTAL_CELLS];
    void spawn_cells();
    void spawn_bombs();
    bool check_victory();
    int m_flags;
};

class Numbers
{
public:
    Numbers(int m_x, int m_y, Texture *texture);
    virtual void render(SDL_Renderer* renderer);
    void update_number(int number);

private:
    int m_number;
    Texture *m_texture;
    int m_x;
    int m_y;
    void set_numbers();
    SDL_Rect m_numbers[10];
};

class Time: public Numbers
{
public:
    Time(int m_x, int m_y, Texture *texture);
    void update();
    void start();

private:
    Uint32 m_start_ticks;
};

class Smiley: public Texture
{
public:
    Smiley();
    virtual void render(SDL_Renderer* renderer, GameState game_state);
    bool handle_event(SDL_Event *e);
private:
    SDL_Rect m_states[3];
    void set_states();
};

#endif