#include"SDL_utils.h"

#include<iostream>
void InitSDL(SDL_Window *gWindow, SDL_Renderer* &gScreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		gWindow = SDL_CreateWindow("Game Battle Tank", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		

	}

	if (gWindow != NULL)
	{
		gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);
	int imgFlats = IMG_INIT_PNG;
	SDL_RenderSetLogicalSize(gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);
}



