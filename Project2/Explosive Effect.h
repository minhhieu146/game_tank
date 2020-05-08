#pragma once
#ifndef EXPLOSIVE_EFFECT
#define EXPLOSIVE_EFFECT

#include "BasicObject.h"

class ExplosiveEffectObject : public BasicObject
{
public:
	ExplosiveEffectObject();
	~ExplosiveEffectObject();

	void set_clip();
	void set_frame_number(const int& fr_number) { frame_number = fr_number; }
	void Show(SDL_Renderer* des);
	bool LoadImage(std::string path, SDL_Renderer* screen);

private:
	int frame_number;
	SDL_Rect frame_clip[8];
};
#endif // !EXPLOSIVE_EFECT
