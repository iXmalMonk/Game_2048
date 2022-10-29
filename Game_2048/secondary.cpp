#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<Windows.h>

#include"variables.h"
#include"secondary.h"

void deInit(Game& game, int error)
{
	if (game.renderer != NULL) SDL_DestroyRenderer(game.renderer);

	if (game.window != NULL) SDL_DestroyWindow(game.window);

	TTF_Quit();

	IMG_Quit();

	SDL_Quit();

	exit(error);
}

void init(Game& game)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Error: %s\n", SDL_GetError());
		system("pause");
		deInit(game, 1);
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		printf("Error: %s\n", SDL_GetError());
		system("pause");
		deInit(game, 1);
	}

	if (TTF_Init() != 0)
	{
		printf("Error: %s\n", SDL_GetError());
		system("pause");
		deInit(game, 1);
	}

	game.window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if (game.window == NULL)
	{
		printf("Error: %s\n", SDL_GetError());
		system("pause");
		deInit(game, 1);
	}

	game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);

	if (game.renderer == NULL)
	{
		printf("Error: %s\n", SDL_GetError());
		system("pause");
		deInit(game, 1);
	}
}

void hideConsole(bool flag)
{
	HWND hide_console;

	AllocConsole();

	hide_console = FindWindowA("ConsoleWindowClass", NULL);

	ShowWindow(hide_console, !flag);
}

void printValue(const Game& game, int value, int x, int y, int size)
{
	char text[TEXT_SIZE];

	_itoa_s(value, text, TEXT_SIZE, 10);

	int counter = 0;

	while (text[counter] != '\0') counter++;

	SDL_Surface* text_surface = TTF_RenderText_Blended(game.font, text, { 0, 0, 0, 255 });

	SDL_Rect rect = { x, y, 0.825 * counter * size, size };

	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(game.renderer, text_surface);

	SDL_RenderCopy(game.renderer, text_texture, NULL, &rect);

	SDL_FreeSurface(text_surface);

	SDL_DestroyTexture(text_texture);
}

void printText(const Game& game, const char* text, int x, int y, int size, int alpha)
{
	int counter = 0;

	while (text[counter] != '\0') counter++;

	SDL_Surface* text_surface = TTF_RenderText_Blended(game.font, text, { 0, 0, 0, Uint8(alpha) });

	SDL_Rect rect = { x, y, 0.825 * counter * size, size };

	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(game.renderer, text_surface);

	SDL_RenderCopy(game.renderer, text_texture, NULL, &rect);

	SDL_FreeSurface(text_surface);

	SDL_DestroyTexture(text_texture);
}