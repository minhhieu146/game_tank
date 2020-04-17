#include "Explosive Effect.h"

ExplosiveEffectObject::ExplosiveEffectObject()
{
	frame_number = 0;
}

ExplosiveEffectObject::~ExplosiveEffectObject()
{

}

void ExplosiveEffectObject::set_clip()
{
	frame_clip[0].x = 0;
	frame_clip[0].y = 0;
	frame_clip[0].w = 100;
	frame_clip[0].h = 100;

	frame_clip[1].x = 100;
	frame_clip[1].y = 0;
	frame_clip[1].w = 100;
	frame_clip[1].h = 100;

	frame_clip[2].x = 100*2;
	frame_clip[2].y = 0;
	frame_clip[2].w = 100;
	frame_clip[2].h = 100;

	frame_clip[3].x = 100*3;
	frame_clip[3].y = 0;
	frame_clip[3].w = 100;
	frame_clip[3].h = 100;

	frame_clip[4].x = 400;
	frame_clip[4].y = 0;
	frame_clip[4].w = 100;
	frame_clip[4].h = 100;

	frame_clip[5].x = 500;
	frame_clip[5].y = 0;
	frame_clip[5].w = 100;
	frame_clip[5].h = 100;
	
	frame_clip[6].x = 600;
	frame_clip[6].y = 0;
	frame_clip[6].w = 100;
	frame_clip[6].h = 100;

	frame_clip[7].x = 700;
	frame_clip[7].y = 0;
	frame_clip[7].w = 100;
	frame_clip[7].h = 100;

}


bool ExplosiveEffectObject::LoadImage(std::string path, SDL_Renderer* screen)
{
	bool rec = BasicObject::LoadImage(path, screen);
	return rec;
}

void ExplosiveEffectObject::Show(SDL_Renderer* des)
{
	SDL_Rect* current_clip = &frame_clip[frame_number];
	SDL_Rect renderQuad = { rect_.x, rect_.y, 100, 100 };

	SDL_RenderCopy(des, fact_screen, current_clip, &renderQuad);
}