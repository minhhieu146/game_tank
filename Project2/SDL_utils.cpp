
#include"BasicObject.h"
#include"SDL_utils.h"

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

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	
		gSoundBullet = Mix_LoadWAV("sound gun.wav");
		if (gSoundBullet == NULL)
		{
			printf( "Failed to load sound bullet effect"); 
		}
		gSoundBoom = Mix_LoadWAV("sound boom.wav");
		if (gSoundBoom == NULL)
		{
			printf("Failed to load sound  boom effect");
		}
	

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);
	int imgFlats = IMG_INIT_PNG;
	SDL_RenderSetLogicalSize(gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void WaitUnikeyPressed()
{
	SDL_Event e;
	while (true)
	{
		if (SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN) || (e.type == SDL_QUIT))
		{
			return;
			SDL_Delay(100);
		}
	}
}


