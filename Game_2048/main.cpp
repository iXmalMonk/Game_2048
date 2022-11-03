#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<Windows.h>

#include"variables.h"
#include"secondary.h"
#include"events.h"
#include"field.h"

void drawBackground(const Game& game)
{
	SDL_SetRenderDrawColor(game.renderer,
		game.color_background.red,
		game.color_background.green,
		game.color_background.blue,
		COLOR_ALPHA);

	SDL_RenderClear(game.renderer);
}

void gameLoop(Game& game)
{
	while (game.loop.launched)
	{
		events(game);

		if (game.loop.play)
		{
			logicField(game);

			//printField(game);

			drawBackground(game);

			drawFieldBackground(game);
			drawField(game);

			printValue(game, 2048, 2, 2, FONT_SIZE * 4);

			drawScore(game);

			newGameDraw(game);

			infoDraw(game);

			if (game.flag.flag_win) drawWin(game);
			if (game.flag.flag_lose) drawLose(game);
		}

		if (game.loop.info) moreInfoDraw(game);

		SDL_RenderPresent(game.renderer);
		SDL_Delay(CLOCKS_PER_SEC / game.fps);
	}
}

#undef main
int main()
{
	system("chcp 1251");
	system("cls");

	srand(time(NULL));

	hideConsole(true);

	Game game;

	init(game);

	game.font = TTF_OpenFont("font.ttf", FONT_SIZE);

	loadBestScore(game);

	createField(game);

	gameLoop(game);

	saveBestScore(game);

	deInit(game, 0);

	return 0;
}