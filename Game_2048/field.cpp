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
			if (rand() % 3 == 0) game.field[i][j] = 4;
			else game.field[i][j] = 2;
			counter++;
		}
	}
}

void createNewField(Game& game)
{
	if (game.flag.flag_create)
	{
		bool flag = true;

		while (flag)
		{
			int i = rand() % FIELD_SIZE;
			int j = rand() % FIELD_SIZE;
			if (game.field[i][j] == 0)
			{
				if (rand() % 3 == 0) game.field[i][j] = 4;
				else game.field[i][j] = 2;
				flag = false;
			}
		}

		game.flag.flag_create = false;
	}
}

void printField(const Game& game)
{
	system("cls");

	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
			printf("%4i ", game.field[i][j]);
		printf("\n");
	}
}

void logicWin(Game& game)
{
	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			if (game.field[i][j] == 2048) game.flag.flag_win = true;
}

void drawWin(const Game& game)
{
	SDL_SetRenderDrawColor(game.renderer, 0, 255, 0, 25);

	SDL_SetRenderDrawBlendMode(game.renderer, SDL_BLENDMODE_BLEND);

	SDL_Rect rect = { 0, 0, WIDTH, HEIGHT };

	SDL_RenderFillRect(game.renderer, &rect);

	printText(game, "WIN", WIDTH / 25, HEIGHT - WIDTH + WIDTH / 2 - game.field_background.wh / 2, FONT_SIZE * 4, 100);
}

void logicLose(Game& game)
{
	bool first_flag = true;
	bool second_flag = false;

	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			if (game.field[i][j] == 0) first_flag = false;

	if (first_flag)
	{
		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
			{
				if (game.field[i - 1][j] == game.field[i][j] and
					game.field[i][j] != 0 and i != 0)
				{
					second_flag = true;
				}

				if (game.field[i][j - 1] == game.field[i][j] and
					game.field[i][j] != 0 and j != 0)
				{
					second_flag = true;
				}

				if (game.field[i + 1][j] == game.field[i][j] and
					game.field[i][j] != 0 and i != 3)
				{
					second_flag = true;
				}

				if (game.field[i][j + 1] == game.field[i][j] and
					game.field[i][j] != 0 and j != 3)
				{
					second_flag = true;
				}
			}

		if (!second_flag) game.flag.flag_lose = true;
	}
}

void drawLose(const Game& game)
{
	SDL_SetRenderDrawColor(game.renderer, 255, 0, 0, 25);

	SDL_SetRenderDrawBlendMode(game.renderer, SDL_BLENDMODE_BLEND);

	SDL_Rect rect = { 0, 0, WIDTH, HEIGHT };

	SDL_RenderFillRect(game.renderer, &rect);

	printText(game, "LOSE", WIDTH / 25, HEIGHT - WIDTH + WIDTH / 2 - game.field_background.wh / 2, FONT_SIZE * 4, 100);
}

void newGameLogic(Game& game)
{
	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			game.field[i][j] = 0;

	game.flag.flag_win = false;
	game.flag.flag_lose = false;
	game.flag.flag_newgame = false;

	game.score.current_score = 0;

	createField(game);
}

void newGameDraw(const Game& game)
{
	SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, COLOR_ALPHA);

	SDL_RenderDrawRect(game.renderer, &game.rect_newgame);

	printText(game, "NEW GAME", FONT_SIZE * 12, FONT_SIZE * 5, FONT_SIZE, 255);
}

void logicFieldMoveUp(Game& game)
{
	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			if (game.field[i - 1][j] == 0 and
				game.field[i][j] != 0 and i != 0)
			{
				game.field[i - 1][j] = game.field[i][j];
				game.field[i][j] = 0;
				i = -1;
				game.flag.flag_create = true;
				break;
			}
}

void logicFieldMoveLeft(Game& game)
{
	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			if (game.field[i][j - 1] == 0 and
				game.field[i][j] != 0 and j != 0)
			{
				game.field[i][j - 1] = game.field[i][j];
				game.field[i][j] = 0;
				i = -1;
				game.flag.flag_create = true;
				break;
			}
}

void logicFieldMoveDown(Game& game)
{
	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			if (game.field[i + 1][j] == 0 and
				game.field[i][j] != 0 and i != 3)
			{
				game.field[i + 1][j] = game.field[i][j];
				game.field[i][j] = 0;
				i = -1;
				game.flag.flag_create = true;
				break;
			}
}

void logicFieldMoveRight(Game& game)
{
	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			if (game.field[i][j + 1] == 0 and
				game.field[i][j] != 0 and j != 3)
			{
				game.field[i][j + 1] = game.field[i][j];
				game.field[i][j] = 0;
				i = -1;
				game.flag.flag_create = true;
				break;
			}
}

void logicFieldMoveUpAndMerged(Game& game)
{
	if (game.direction == up)
	{
		logicFieldMoveUp(game);

		for(int i = 0; i < FIELD_SIZE; i++)
			for(int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i - 1][j] == game.field[i][j] and
					game.field[i][j] != 0 and i != 0)
				{
					game.field[i - 1][j] = game.field[i][j] * 2;
					game.score.current_score += game.field[i][j] * 2;
					game.field[i][j] = 0;
					game.flag.flag_create = true;
				}

		logicFieldMoveUp(game);

		game.direction = nothing;
	}
}

void logicFieldMoveLeftAndMerged(Game& game)
{
	if (game.direction == left)
	{
		logicFieldMoveLeft(game);

		for(int i = 0; i < FIELD_SIZE; i++)
			for(int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i][j - 1] == game.field[i][j] and
					game.field[i][j] != 0 and j != 0)
				{
					game.field[i][j - 1] = game.field[i][j] * 2;
					game.score.current_score += game.field[i][j] * 2;
					game.field[i][j] = 0;
					game.flag.flag_create = true;
				}

		logicFieldMoveLeft(game);

		game.direction = nothing;
	}
}

void logicFieldMoveDownAndMerged(Game& game)
{
	if (game.direction == down)
	{
		logicFieldMoveDown(game);

		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i + 1][j] == game.field[i][j] and
					game.field[i][j] != 0 and i != 3)
				{
					game.field[i + 1][j] = game.field[i][j] * 2;
					game.score.current_score += game.field[i][j] * 2;
					game.field[i][j] = 0;
					game.flag.flag_create = true;
				}

		logicFieldMoveDown(game);

		game.direction = nothing;
	}
}

void logicFieldMoveRightAndMerged(Game& game)
{
	if (game.direction == right)
	{
		logicFieldMoveRight(game);

		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (game.field[i][j + 1] == game.field[i][j] and
					game.field[i][j] != 0 and j != 3)
				{
					game.field[i][j + 1] = game.field[i][j] * 2;
					game.score.current_score += game.field[i][j] * 2;
					game.field[i][j] = 0;
					game.flag.flag_create = true;
				}

		logicFieldMoveRight(game);

		game.direction = nothing;
	}
}

void logicField(Game& game)
{
	logicFieldMoveUpAndMerged(game);
	logicFieldMoveLeftAndMerged(game);
	logicFieldMoveDownAndMerged(game);
	logicFieldMoveRightAndMerged(game);

	logicWin(game);
	logicLose(game);

	if (game.flag.flag_newgame) newGameLogic(game);

	createNewField(game);
}

void setColorField(Game& game, int value)
{
	if (value == 2) SDL_SetRenderDrawColor(game.renderer,
		game.color_2.red,
		game.color_2.green,
		game.color_2.blue,
		COLOR_ALPHA);
	if (value == 4)
		SDL_SetRenderDrawColor(game.renderer,
			game.color_4.red,
			game.color_4.green,
			game.color_4.blue,
			COLOR_ALPHA);
	if (value == 8)
		SDL_SetRenderDrawColor(game.renderer,
			game.color_8.red,
			game.color_8.green,
			game.color_8.blue,
			COLOR_ALPHA);
	if (value == 16)
		SDL_SetRenderDrawColor(game.renderer,
			game.color_16.red,
			game.color_16.green,
			game.color_16.blue,
			COLOR_ALPHA);
	if (value == 32)
		SDL_SetRenderDrawColor(game.renderer,
			game.color_32.red,
			game.color_32.green,
			game.color_32.blue,
			COLOR_ALPHA);
	if (value == 64)
		SDL_SetRenderDrawColor(game.renderer,
			game.color_64.red,
			game.color_64.green,
			game.color_64.blue,
			COLOR_ALPHA);
	if (value == 128)
		SDL_SetRenderDrawColor(game.renderer,
			game.color_128.red,
			game.color_128.green,
			game.color_128.blue,
			COLOR_ALPHA);
	if (value == 256)
		SDL_SetRenderDrawColor(game.renderer,
			game.color_256.red,
			game.color_256.green,
			game.color_256.blue,
			COLOR_ALPHA);
	if (value == 512)
		SDL_SetRenderDrawColor(game.renderer,
			game.color_512.red,
			game.color_512.green,
			game.color_512.blue,
			COLOR_ALPHA);
	if (value == 1024)
		SDL_SetRenderDrawColor(game.renderer,
			game.color_1024.red,
			game.color_1024.green,
			game.color_1024.blue,
			COLOR_ALPHA);
	if (value == 2048)
		SDL_SetRenderDrawColor(game.renderer,
			game.color_2048.red,
			game.color_2048.green,
			game.color_2048.blue,
			COLOR_ALPHA);
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
				setColorField(game, game.field[i][j]);

				SDL_RenderFillRect(game.renderer,
					&game.field_background.rect_field);

				printValue(game,
					game.field[i][j],
					game.field_background.rect_field.x,
					game.field_background.rect_field.y,
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

void logicScore(Game& game)
{
	if (game.score.current_score >= game.score.best_score) game.score.best_score = game.score.current_score;
}

void drawScore(Game& game)
{
	logicScore(game);

	printText(game, "SCORE", 2, FONT_SIZE * 5, FONT_SIZE, 255);
	printValue(game, game.score.current_score, 2, FONT_SIZE * 6, FONT_SIZE);

	printText(game, "BEST", FONT_SIZE * 6, FONT_SIZE * 5, FONT_SIZE, 255);
	printValue(game, game.score.best_score, FONT_SIZE * 6, FONT_SIZE * 6, FONT_SIZE);
}

void loadBestScore(Game& game)
{
	FILE* file;

	if (fopen_s(&file, "score.bin", "rt") != 0) exit(1);

	fread(&game.score.best_score, sizeof(int), 1, file);

	fclose(file);
}

void saveBestScore(Game& game)
{
	FILE* file;

	if (fopen_s(&file, "score.bin", "wt") != 0) exit(1);

	if (game.score.current_score >= game.score.best_score) fwrite(&game.score.current_score, sizeof(int), 1, file);
	else fwrite(&game.score.best_score, sizeof(int), 1, file);

	fclose(file);
}