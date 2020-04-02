#ifndef BULLET_OBJECT_
#define BULLET_OBJECT_

#include"BaseObject.h"
#include"CommonFuntion.h"

class BulletObject : public BaseObject
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

	void set_x_val_(const int& xVal) { x_val_ = xVal; }
	void set_y_val_(const int& yVal) { y_val_ = yVal; } 
	int get_x_val_() const { return x_val_ ; }
	int get_y_val_() const { return y_val_ ; }

	void set_bullet_direction(const int& bulletDirection) { bullet_direction = bulletDirection; }
	int get_bullet_direction() const { return bullet_direction; }

	void set_is_move(const bool& isMove) { is_move_ = isMove; }
	bool get_is_move() const { return is_move_; }
	void HandleMove(const int& x_boder_, const int& y_boder_);

private:
	int x_val_;
	int y_val_;
	bool is_move_;
	int bullet_direction; 
};

#endif // !BULLEt_OBJECT_
