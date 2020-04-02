#include"BaseObject.h"
#include"BulletObject.h"

BulletObject::BulletObject()
{
	rect_.x = 0;
	rect_.y = 0;
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
}

BulletObject::~BulletObject()
{

}

void BulletObject::HandleMove(const int& x_boder_, const int& y_boder_)
{
	if (bullet_direction == DIR_RIGHT)
	{
		rect_.x += x_val_;
		if (rect_.x > x_boder_)
		{
			is_move_ = false;
		}
	}
	else if (bullet_direction == DIR_LEFT)
	{
		rect_.x -= x_val_;
		if (rect_.x < 0)
		{
			is_move_ = false;
		}
	}
	else if (bullet_direction == DIR_UP)
	{
		rect_.y -= y_val_;
		if (rect_.y < 0)
		{
			is_move_ = false;
		}
	}
	else if (bullet_direction == DIR_DOWN)
	{
		rect_.y += y_val_;
		if (rect_.y > y_boder_)
		{
			is_move_ = false;
		}
	}
}

