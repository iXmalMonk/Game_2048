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

struct Flag
{
	bool flag_move = true;
	bool flag_create = false;
	bool flag_newgame = false;

	bool flag_win = false;
	bool flag_lose = false;
};

struct Loop
{
	bool launched = true;
	bool play = true;
	bool info = false;
};

struct Mouse
{
	int x = 0;
	int y = 0;
};

struct Position
{
	int x = 0;
	int y = 0;
};

struct Score
{
	int best_score = 0;
	int current_score = 0;
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
	const int fps = 60;

	Color color_2 = { 238, 228, 218 };
	Color color_4 = { 237, 224, 200 };
	Color color_8 = { 242, 177, 121 };
	Color color_16 = { 246, 150, 100 };
	Color color_32 = { 246, 124, 95 };
	Color color_64 = { 246, 94, 59 };
	Color color_128 = { 237, 207, 114 };
	Color color_256 = { 237, 204, 97 };
	Color color_512 = { 237, 200, 80 };
	Color color_1024 = { 237, 197, 63 };
	Color color_2048 = { 237, 194, 46 };

	Color color_background = { 250, 248, 239 };
	Direction direction = nothing;
	Flag flag;
	Loop loop;
	Mouse mouse;
	Score score;
	//int field[FIELD_SIZE][FIELD_SIZE] = { 0 };
	int field[FIELD_SIZE][FIELD_SIZE] = { {0, 0, 0, 1024},
										  {0, 0, 0, 0},
										  {0, 0, 0, 0},
										  {1024, 0, 0, 0} };
	FieldBackground field_background;

	SDL_Event event;
	SDL_Rect rect_newgame = { FONT_SIZE * 12 - 1 - 1, FONT_SIZE * 5 - 1, int(0.825 * 8 * FONT_SIZE), FONT_SIZE };
	SDL_Renderer* renderer = NULL;
	SDL_Window* window = NULL;

	TTF_Font* font = NULL;
};

#endif