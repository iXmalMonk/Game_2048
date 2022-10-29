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

		logicField(game);

		drawBackground(game);

		drawFieldBackground(game);
		drawField(game);

		//printField(game);

		SDL_RenderPresent(game.renderer);
		SDL_Delay(CLOCKS_PER_SEC / game.fps);
	}
}

#undef main
int main()
{
	system("chcp 1251");
	system("cls");

	//int time_seed = time(NULL);
	//printf("Time seed = %i", time_seed);
	//srand(time_seed);
	srand(time(NULL));
	//srand(0);

	hideConsole(false);

	Game game;

	init(game);

	game.font = TTF_OpenFont("font.ttf", FONT_SIZE);

	//createField(game);

	gameLoop(game);

	deInit(game, 0);

	return 0;
}