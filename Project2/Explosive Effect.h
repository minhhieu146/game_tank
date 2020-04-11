#ifndef EXPLOSIVE_EFFECT
#define EXPLOSIVE_EFFECT

#include "BaseObject.h"
#include "CommonFuntion.h"

class ExplosiveEffectObject : public BaseObject
{
public:
	ExplosiveEffectObject();
	~ExplosiveEffectObject();

	void set_clip();
	void set_frame_number(int fr_number) { frame_number = fr_number; }
	void Show(SDL_Renderer* des);
	bool LoadImage(std::string path, SDL_Renderer* screen);

private:
	int frame_number;
	SDL_Rect frame_clip[8];
};
#endif // !EXPLOSIVE_EFECT
