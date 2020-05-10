#include"BulletObject.h"
BulletObject::BulletObject()
{
	rect_.x = 0;
	rect_.y = 0;
	x_change = 0;
	y_change = 0;
	is_move_ = false;
}

BulletObject::~BulletObject()
{

}

void BulletObject::Move(const int& x_max_, const int& y_max_)   //di chuyển trong phạm vi map
{
	if (bullet_direction == DIR_RIGHT)
	{
		rect_.x += x_change;
		if (rect_.x > SCREEN_WIDTH)
		{
			is_move_ = false;
		}
	}
	else if (bullet_direction == DIR_LEFT)
	{
		rect_.x -= x_change;
		if (rect_.x < 0)
		{
			is_move_ = false;
		}
	}
	else if (bullet_direction == DIR_UP)
	{
		rect_.y -= y_change;
		if (rect_.y < 0)
		{
			is_move_ = false;
		}
	}
	else if (bullet_direction == DIR_DOWN)
	{
		rect_.y += y_change;
		if (rect_.y > SCREEN_HEIGHT)
		{
			is_move_ = false;
		}
	}
}

bool BulletObject::CheckMapForBullet(Map& map_data, const SDL_Rect& object1)
{
	int left = 0;		
	int right = 0;

	int top = 0;		
	int down = 0;


	//check theo chieu ngang

	left = (object1.x + x_change) / TILE_SIZE;
	right = (object1.x + x_change + 30 - 1) / TILE_SIZE;

	top =  object1.y / TILE_SIZE;
	down = (object1.y + 30 - 1) / TILE_SIZE;

	if (left >= 0 && right < (MAX_MAP_X) && top >= 0 && down < MAX_MAP_Y)
	{
		if (is_move_ == true)
		{
			if (map_data.tile[top][right] == 1 || map_data.tile[down][right] == 1)
			{
				return true;
			}

			if (map_data.tile[top][left] == 1 || map_data.tile[down][left] == 1)
			{
				return true;
			}
		}
	}
	//check theo chieu doc

	left = (object1.x) / TILE_SIZE;
	right = (object1.x + 30) / TILE_SIZE;
	top = (object1.y + y_change) / TILE_SIZE;
	down = (object1.y + y_change + 30 - 1) / TILE_SIZE;

	if (left >= 0 && right < MAX_MAP_X && top >= 0 && down < MAX_MAP_Y)
	{
		if (is_move_ == true)
		{
			if (map_data.tile[down][left] == 1 || map_data.tile[down][right] == 1)
			{
				return true;
			}
	
			if (map_data.tile[top][left] == 1 || map_data.tile[top][right] == 1)
			{
				return true;
			}
		}
	}

	return false;
}