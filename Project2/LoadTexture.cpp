#include"LoadTexture.h"

Gallery::Gallery(SDL_Renderer* renderer_)
	: renderer(renderer_)
{
	loadGamePictures();
}

Gallery::~Gallery()
{
	for (SDL_Texture* texture : pictures)
		SDL_DestroyTexture(texture);
}

SDL_Texture* Gallery::loadTexture(std::string path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != NULL)
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture != NULL)
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

void Gallery::loadGamePictures()
{
	pictures[PICK_TANK_RIGHT] = loadTexture("tankright.png");
	pictures[PIC_TANK_LEFT] = loadTexture("tankleft.png");
	pictures[PIC_TANK_UP] = loadTexture("tankup.png");
	pictures[PIC_TANK_DOWN] = loadTexture("tankdown.png");
	pictures[PIC_BULLET_DOWN] = loadTexture("BulletDown.png");
	pictures[PIC_BULLET_UP] = loadTexture("BulletUp.png");
	pictures[PIC_BULLET_LEFT] = loadTexture("BulletLeft.png");
	pictures[PIC_BULLET_RIGHT] = loadTexture("BulletRight.png");
}