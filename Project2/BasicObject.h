#ifndef BASIC_OBJECT_H_
#define BASIC_OBJECT_H_

#include"SDL_utils.h"

class BasicObject		//lớp cơ bản
{
public:
	BasicObject();
	~BasicObject();
	
	SDL_Texture* fact_screen;
	
	void SetRect(const int& x, const int& y) {						//set tọa độ 
		rect_.x = x;
		rect_.y = y;
	}
	SDL_Rect GetRect() const { return rect_; }						//lấy ra tọa độ
	SDL_Texture* GetScreen() { return fact_screen; }				//lấy ra texture

	virtual bool LoadImage(std::string path, SDL_Renderer* screen);			//hàm load ảnh 
	void Render(SDL_Renderer* des, const  SDL_Rect* clip = NULL);			//hàm render ảnh lên màn hình
	void Free();

protected:
	SDL_Rect rect_;

};


#endif // !BASIC_OBJECT_H_
