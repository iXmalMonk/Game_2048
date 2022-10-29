#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<Windows.h>

#include"events.h"

#include"secondary.h"
#include"variables.h"

void events(Game& game)
{
	while (SDL_PollEvent(&game.event))
	{
		switch (game.event.type)
		{
		case SDL_QUIT:
			game.loop.launched = false;
			break;
		case SDL_KEYUP:
			switch (game.event.key.keysym.scancode)
			{
			case SDL_SCANCODE_W:
			case SDL_SCANCODE_A:
			case SDL_SCANCODE_S:
			case SDL_SCANCODE_D:
				game.flag_move = true;
				break;
			}
			break;
		case SDL_KEYDOWN:
			switch (game.event.key.keysym.scancode)
			{
			case SDL_SCANCODE_W:
				if (game.flag_move) 
				{
					game.direction = up;
					game.flag_move = false;
				}
				break;
			case SDL_SCANCODE_A:
				if (game.flag_move)
				{
					game.direction = left;
					game.flag_move = false;
				}
				break;
			case SDL_SCANCODE_S:
				if (game.flag_move)
				{
					game.direction = down;
					game.flag_move = false;
				}
				break;
			case SDL_SCANCODE_D:
				if (game.flag_move)
				{
					game.direction = right;
					game.flag_move = false;
				}
				break;
			}
			break;
		}
	}
}