#pragma once
#ifndef BULLET_OBJECT_
#define BULLET_OBJECT_

#include"BasicObject.h"
#include"Gallery.h"

class BulletObject : public BasicObject
{
public:
	BulletObject();
	~BulletObject();

	enum BULLET_DIRECTION
	{
		DIR_RIGHT = 0,
		DIR_LEFT = 1,
		DIR_DOWN = 2,
		DIR_UP = 3,

	};

	void set_x_change(const int& xChange) { x_change = xChange; }						//set lượng thay đổi cho x
	void set_y_change(const int& yChange) { y_change = yChange; }						//set lượng thay đổi cho y
	int get_x_change() const { return x_change ; }										
	int get_y_change() const { return y_change ; }

	void set_bullet_direction(const int& bulletDirection) { bullet_direction = bulletDirection; }
	int get_bullet_direction() const { return bullet_direction; }

	void set_is_move(const bool& isMove) { is_move_ = isMove; }
	bool get_is_move() const { return is_move_; }
	void Move(const int& x_max_, const int& y_max_);						//hàm di chuyển cho đạn
	bool CheckMapForBullet(Map& map_data, const SDL_Rect& object1);				// hàm check đạn với tường
private:
	int x_change;
	int y_change;
	bool is_move_;
	int bullet_direction; 
};

#endif // !BULLEt_OBJECT_
