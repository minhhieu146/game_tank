#include"BaseObject.h"
#include"BulletObject.h"
#include"EnemyTankObject.h"

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

bool BulletObject::CheckMapForBullet(Map& map_data)
{
	int x1 = 0;		//diem trai cua anh
	int x2 = 0;

	int y1 = 0;		//diem phai cua anh
	int y2 = 0;

	//check theo chieu ngang
	int height_min = 60 - 10;

	x1 = (rect_.x + x_val_) / TILE_SIZE;
	x2 = (rect_.x + x_val_ + 64 - 1) / TILE_SIZE;

	y1 =  rect_.y / TILE_SIZE;
	y2 = (rect_.y + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < (MAX_MAP_X) && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ > 0)
		{
			if (map_data.tile[y1][x2] == 1 || map_data.tile[y2][x2] == 1)
			{
				rect_.x = x2 * TILE_SIZE;
				rect_.x -= (64 + 1);
				x_val_ = 0;
				return true;
			}
		}
		else if (x_val_ < 0)
		{
			if (map_data.tile[y1][x1] == 1 || map_data.tile[y2][x1] == 1)
			{
				rect_.x = (x1 + 1)* TILE_SIZE;
				x_val_ = 0;
				return true;

			}
		}
	}
	//check theo chieu doc

	int width_min = 64 - 10;
	x1 = (rect_.x) / TILE_SIZE;
	x2 = (rect_.x + width_min) / TILE_SIZE;
	y1 = (rect_.y + y_val_) / TILE_SIZE;
	y2 = (rect_.y + y_val_ + 60 - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0)
		{
			if (map_data.tile[y2][x1] == 1 || map_data.tile[y2][x2] == 1)
			{
				rect_.y = y2 * TILE_SIZE;
				rect_.y -= (60 + 1);
				y_val_ = 0;
				return true;
			}
		}
		else if (y_val_ < 0)
		{
			if (map_data.tile[y1][x1] == 1 || map_data.tile[y1][x2] == 1)
			{
				rect_.y = (y1 + 1)*TILE_SIZE;
				y_val_ = 0;
				return true;
			}
		}
	}

	rect_.x += x_val_;
	rect_.y += y_val_;

	return false;
}