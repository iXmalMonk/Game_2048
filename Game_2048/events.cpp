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
		case SDL_MOUSEMOTION:
			game.mouse.x = game.event.motion.x;
			game.mouse.y = game.event.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if ((game.rect_newgame.x + game.rect_newgame.w) >= game.mouse.x and game.mouse.x >= game.rect_newgame.x and
				(game.rect_newgame.y + game.rect_newgame.h) >= game.mouse.y and game.mouse.y >= game.rect_newgame.y and game.loop.play) game.flag.flag_newgame = true;

			if ((game.rect_info.x + game.rect_info.w) >= game.mouse.x and game.mouse.x >= game.rect_info.x and
				(game.rect_info.y + game.rect_info.h) >= game.mouse.y and game.mouse.y >= game.rect_info.y and game.loop.play)
			{
				game.loop.info = true;
				game.loop.play = false;
			}
			break;
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
			case SDL_SCANCODE_UP:
			case SDL_SCANCODE_LEFT:
			case SDL_SCANCODE_DOWN:
			case SDL_SCANCODE_RIGHT:
				game.flag.flag_move = true;
				break;
			}
			break;
		case SDL_KEYDOWN:
			switch (game.event.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				if (game.loop.play) game.loop.launched = false;
				if (game.loop.info)
				{
					game.loop.play = true;
					game.loop.info = false;
				}
				break;
			case SDL_SCANCODE_R:
				if (game.loop.play) game.flag.flag_newgame = true;
				break;
			case SDL_SCANCODE_W:
			case SDL_SCANCODE_UP:
				if (game.flag.flag_move and !game.flag.flag_win and !game.flag.flag_lose and game.loop.play)
				{
					game.direction = up;
					game.flag.flag_move = false;
				}
				break;
			case SDL_SCANCODE_A:
			case SDL_SCANCODE_LEFT:
				if (game.flag.flag_move and !game.flag.flag_win and !game.flag.flag_lose and game.loop.play)
				{
					game.direction = left;
					game.flag.flag_move = false;
				}
				break;
			case SDL_SCANCODE_S:
			case SDL_SCANCODE_DOWN:
				if (game.flag.flag_move and !game.flag.flag_win and !game.flag.flag_lose and game.loop.play)
				{
					game.direction = down;
					game.flag.flag_move = false;
				}
				break;
			case SDL_SCANCODE_D:
			case SDL_SCANCODE_RIGHT:
				if (game.flag.flag_move and !game.flag.flag_win and !game.flag.flag_lose and game.loop.play)
				{
					game.direction = right;
					game.flag.flag_move = false;
				}
				break;
			}
			break;
		}
	}
}