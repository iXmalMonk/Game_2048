#ifndef _VARIABLES_H
#define _VARIABLES_H

#define WIDTH 500
#define HEIGHT 700

#define COLOR_ALPHA 255

#define FIELD_SIZE 4

#define TEXT_SIZE 8

#define FONT_SIZE 25

struct Color
{
	int red = 0;
	int green = 0;
	int blue = 0;
};

enum Direction { up, left, down, right, nothing};

struct Loop
{
	bool launched = true;
};

struct Position
{
	int x = 0;
	int y = 0;
};

struct FieldBackground
{
	int wh = WIDTH / 5;

	Position position_field = { WIDTH / 25, HEIGHT - WIDTH + WIDTH / 25 }; // 20 220
	SDL_Rect rect_field = { position_field.x, position_field.y, wh, wh }; // 100 100
	Color color_field = { 205, 193, 180 };

	SDL_Rect rect_field_background = { 0, HEIGHT - WIDTH, WIDTH, WIDTH }; // 0 200 500 500
	Color color_field_background = { 187, 173, 160 };
};

struct Game
{
	bool flag_move = true;
	bool flag_create = false;
	const int fps = 60;

	Color color_background = { 250, 248, 239 };
	Direction direction = nothing;
	Loop loop;
	//int field[FIELD_SIZE][FIELD_SIZE] = { 0 };
	int field[FIELD_SIZE][FIELD_SIZE] = { {0, 0, 0, 0},
										  {0, 0, 0, 0},
										  {0, 2, 0, 0},
										  {0, 2, 0, 0} };
	FieldBackground field_background;

	SDL_Event event;
	SDL_Renderer* renderer = NULL;
	SDL_Window* window = NULL;

	TTF_Font* font = NULL;
};

#endif