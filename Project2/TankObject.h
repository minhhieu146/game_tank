#pragma once
#ifndef TANK_OBJECT_
#define TANK_OBJECT_

#include"BasicObject.h";
#include<vector>
#include"BulletObject.h"
#include"Game Map.h"
#include"Gallery.h"
#define TANK_SPEED 5

class TankObject : public BasicObject
{
public:
	TankObject();
	~TankObject();

	enum MoveType
	{
		MOVE_RIGHT = 0,
		MOVE_LEFT = 1,
		MOVE_UP = 2,
		MOVE_DOWN = 3,
	};
	
	bool LoadImage(std::string path, SDL_Renderer* screen);			// load ảnh tank
	void InputKeyboard(SDL_Event events, SDL_Renderer* screen);		// xử lý sự kiện bàn phím
	void Show(SDL_Renderer* des);									// render lên màn hình

	void MoveTank(Map& map_data);
	void CheckMap(Map& map_dada);


	void set_bullet_list_(std::vector<BulletObject*> bullet_list)
	{
		p_bullet_list_ = bullet_list;
	}
	std::vector<BulletObject*> get_bullet_list_() const { return p_bullet_list_; }
	void BulletMove(SDL_Renderer* des);
	void RemoveBullet(const int& idx);

	SDL_Rect GetRectTank();

private:

	std::vector<BulletObject*> p_bullet_list_;  // tạo vectoe chứa đạn
	float x_change;
	float y_change;

	float x_location;
	float y_location;

	int width_frame_;
	int	height_frame_;

	SDL_Rect frame_;
	Input input_type_;
	int status_;
};

#endif 
