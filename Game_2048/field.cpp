#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<Windows.h>

#include"field.h"

#include"secondary.h"
#include"variables.h"

void createField(Game& game)
{
	int counter = 0;

	while (counter != 2)
	{
		int i = rand() % FIELD_SIZE;
		int j = rand() % FIELD_SIZE;
		if (game.field[i][j] == 0)
		{
			game.field[i][j] = 2;
			counter++;
		}
	}
}

void createNewField(Game& game)
{
	bool flag = true;

	while (flag)
	{
		int i = rand() % FIELD_SIZE;
		int j = rand() % FIELD_SIZE;
		if (game.field[i][j] == 0)
		{
			game.field[i][j] = 2;
			flag = false;
		}
	}
}

void printField(const Game& game)
{
	system("cls");

	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
			printf("%i ", game.field[i][j]);
		printf("\n");
	}
}

void logicFieldMoveUp(Game& game)
{
	if (game.direction == up)
	{
		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i - 1][j] == 0 and
					game.field[i][j] != 0 and i != 0)
				{
					game.field[i - 1][j] = game.field[i][j];
					game.field[i][j] = 0;
					i = -1;
					game.flag_create = true;
					break;
				}

		for(int i = 0; i < FIELD_SIZE; i++)
			for(int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i - 1][j] == game.field[i][j] and
					game.field[i][j] != 0 and i != 0)
				{
					game.field[i - 1][j] = game.field[i][j] * 2;
					game.field[i][j] = 0;
					game.flag_create = true;
				}

		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i - 1][j] == 0 and
					game.field[i][j] != 0 and i != 0)
				{
					game.field[i - 1][j] = game.field[i][j];
					game.field[i][j] = 0;
					i = -1;
					game.flag_create = true;
					break;
				}

		game.direction = nothing;
	}
}

void logicFieldMoveLeft(Game& game)
{
	if (game.direction == left)
	{
		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i][j - 1] == 0 and
					game.field[i][j] != 0 and j != 0)
				{
					game.field[i][j - 1] = game.field[i][j];
					game.field[i][j] = 0;
					i = -1;
					game.flag_create = true;
					break;
				}

		for(int i = 0; i < FIELD_SIZE; i++)
			for(int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i][j - 1] == game.field[i][j] and
					game.field[i][j] != 0 and j != 0)
				{
					game.field[i][j - 1] = game.field[i][j] * 2;
					game.field[i][j] = 0;
					game.flag_create = true;
				}

		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i][j - 1] == 0 and
					game.field[i][j] != 0 and j != 0)
				{
					game.field[i][j - 1] = game.field[i][j];
					game.field[i][j] = 0;
					i = -1;
					game.flag_create = true;
					break;
				}

		game.direction = nothing;
	}
}

void logicFieldMoveDown(Game& game)
{
	if (game.direction == down)
	{
		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i + 1][j] == 0 and
					game.field[i][j] != 0 and i != 3)
				{
					game.field[i + 1][j] = game.field[i][j];
					game.field[i][j] = 0;
					i = -1;
					game.flag_create = true;
					break;
				}

		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i + 1][j] == game.field[i][j] and
					game.field[i][j] != 0 and i != 3)
				{
					game.field[i + 1][j] = game.field[i][j] * 2;
					game.field[i][j] = 0;
					game.flag_create = true;
				}

		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i + 1][j] == 0 and
					game.field[i][j] != 0 and i != 3)
				{
					game.field[i + 1][j] = game.field[i][j];
					game.field[i][j] = 0;
					i = -1;
					game.flag_create = true;
					break;
				}

		game.direction = nothing;
	}
}

void logicFieldMoveRight(Game& game)
{
	if (game.direction == right)
	{
		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i][j + 1] == 0 and
					game.field[i][j] != 0 and j != 3)
				{
					game.field[i][j + 1] = game.field[i][j];
					game.field[i][j] = 0;
					i = -1;
					game.flag_create = true;
					break;
				}

		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i][j + 1] == game.field[i][j] and
					game.field[i][j] != 0 and j != 3)
				{
					game.field[i][j + 1] = game.field[i][j] * 2;
					game.field[i][j] = 0;
					game.flag_create = true;
				}

		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i][j + 1] == 0 and
					game.field[i][j] != 0 and j != 3)
				{
					game.field[i][j + 1] = game.field[i][j];
					game.field[i][j] = 0;
					i = -1;
					game.flag_create = true;
					break;
				}

		game.direction = nothing;
	}
}

void logicFieldMerged(Game& game)
{
	
}

void logicField(Game& game)
{
	logicFieldMoveUp(game);
	logicFieldMoveLeft(game);
	logicFieldMoveDown(game);
	logicFieldMoveRight(game);

	/*if (game.direction == up)
		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i - 1][j] == game.field[i][j] and
					game.field[i][j] != 0 and i != 0)
				{
					game.field[i - 1][j] = game.field[i][j] * 2;
					game.field[i][j] = 0;
					break;
				}
	
	if (game.direction == left)
		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i][j - 1] == game.field[i][j] and
					game.field[i][j] != 0 and j != 0)
				{
					game.field[i][j - 1] = game.field[i][j] * 2;
					game.field[i][j] = 0;
					break;
				}
	
	if (game.direction == down)
		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i + 1][j] == game.field[i][j] and
					game.field[i][j] != 0 and i != 3)
				{
					game.field[i + 1][j] = game.field[i][j] * 2;
					game.field[i][j] = 0;
					break;
				}
	
	if (game.direction == right)
		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i][j + 1] == game.field[i][j] and
					game.field[i][j] != 0 and j != 3)
				{
					game.field[i][j + 1] = game.field[i][j] * 2;
					game.field[i][j] = 0;
					break;
				}*/

	if (game.flag_create)
	{
		createNewField(game);
		game.flag_create = false;
	}
}

void drawField(Game& game)
{
	game.field_background.rect_field.x = game.field_background.position_field.x;
	game.field_background.rect_field.y = game.field_background.position_field.y;

	SDL_SetRenderDrawColor(game.renderer, 155, 155, 155, COLOR_ALPHA);

	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			if (game.field[i][j] != 0)
			{
				SDL_RenderFillRect(game.renderer,
					&game.field_background.rect_field);

				printValue(game,
					game.field[i][j],
					game.field_background.rect_field.x,
					game.field_background.rect_field.y/* + FONT_SIZE*/,
					FONT_SIZE);
			}
			game.field_background.rect_field.x += game.field_background.wh + game.field_background.position_field.x;
		}
		game.field_background.rect_field.x = game.field_background.position_field.x;
		game.field_background.rect_field.y += game.field_background.wh + game.field_background.position_field.x;
	}
}

void drawFieldBackground(Game& game)
{
	game.field_background.rect_field.x = game.field_background.position_field.x;
	game.field_background.rect_field.y = game.field_background.position_field.y;

	SDL_SetRenderDrawColor(game.renderer,
		game.field_background.color_field_background.red,
		game.field_background.color_field_background.green,
		game.field_background.color_field_background.blue,
		COLOR_ALPHA);

	SDL_RenderFillRect(game.renderer,
		&game.field_background.rect_field_background);

	SDL_SetRenderDrawColor(game.renderer,
		game.field_background.color_field.red,
		game.field_background.color_field.green,
		game.field_background.color_field.blue,
		COLOR_ALPHA);

	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			SDL_RenderFillRect(game.renderer,
				&game.field_background.rect_field);

			game.field_background.rect_field.x += game.field_background.wh + game.field_background.position_field.x;
		}
		game.field_background.rect_field.x = game.field_background.position_field.x;
		game.field_background.rect_field.y += game.field_background.wh + game.field_background.position_field.x;
	}
}