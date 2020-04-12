#ifndef BASIC_OBJECT_H_
#define BASIC_OBJECT_H_

#include"CommonFuntion.h"

class BasicObject
{
public:
	BasicObject();
	~BasicObject();
	void SetRect(const int& x, const int& y) {
		rect_.x = x;
		rect_.y = y;
	}
	SDL_Rect GetRect() const { return rect_; }
	SDL_Texture* GetScreen() { return fact_screen; }

	virtual bool LoadImage(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const  SDL_Rect* clip = NULL);
	void Free();

protected:
	SDL_Texture* fact_screen;
	SDL_Rect rect_;

};


#endif // !BASIC_OBJECT_H_
