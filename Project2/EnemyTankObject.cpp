#include"EnemyTankObject.h"
#include"BaseObject.h"
#include"CommonFuntion.h"

EnemyTankObject::EnemyTankObject()
{
	x_pos_ = 1100.0;
	y_pos_ = 300.0;
	width_frame_ = 60;
	height_frame_ = 60;
	x_val_ = 0.0;
	y_val_ = 0.0;
	frame_ = 0;
	direction = 0;
}

EnemyTankObject::~EnemyTankObject()
{


}

bool EnemyTankObject::LoadImage(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImage(path, screen);
	return ret;
}

void EnemyTankObject::Show(SDL_Renderer* des)
{
	if (direction == 1)
	{
		LoadImage("tankleft.png", des);
	}
	else if (direction == 2)
	{
		LoadImage("tankright.png", des);
	}
	else if (direction == 3)
	{
		LoadImage("tankup.png", des);
	}
	else if (direction == 4)
	{
		LoadImage("tankdown.png", des);
	}
		frame_clip[0].x = 0;
		frame_clip[0].y = 0;
		frame_clip[0].w = width_frame_;
		frame_clip[0].h = height_frame_;
		rect_.x = x_pos_;
		rect_.y = y_pos_;
		SDL_Rect* currenClip = &frame_clip[frame_];
		SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
		SDL_RenderCopy(des, p_object_, currenClip, &renderQuad);

}

void EnemyTankObject::MoveTank(Map& map_data)
{
		srand((int)time(0));		
		direction = rand() % 4 + 1;
		if (direction == 1)
		{
			srand((int)time(0));
			x_val_ -= rand() % (3);
			y_val_ = 0;
		}
		else if (direction == 2)
		{
			srand((int)time(0));
			x_val_ += rand() % (3);
			y_val_ = 0;
		}
		else if (direction == 3)
		{
			srand((int)time(0));
			x_val_ = 0;
			y_val_ -= rand() % (3);
		}
		else if (direction == 4)
		{
			srand((int)time(0));
			x_val_ = 0;
			y_val_ += rand() % (3);
		}

		CheckMap(map_data);

}


void EnemyTankObject::CheckMap(Map& map_data)
{
	int x1 = 0;		//toa do ban dau
	int x2 = 0;

	int y1 = 0;		//toa do sau khi bam phim
	int y2 = 0;

	//check theo chieu ngang
	int height_min = height_frame_ - 10;  

	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = y_pos_ / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < (MAX_MAP_X) && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ > 0)
		{
			if (map_data.tile[y1][x2] == 1 || map_data.tile[y2][x2] == 1)
			{
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= (width_frame_ + 1);
				x_val_ = 0;
			}
		}
		else if (x_val_ < 0)
		{
			if (map_data.tile[y1][x1] == 1 || map_data.tile[y2][x1] == 1)
			{
				x_pos_ = (x1 + 1)* TILE_SIZE;
				x_val_ = 0;

			}
		}
	}
	//check theo chieu doc

	int width_min = width_frame_ - 10;
	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;
	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0)
		{
			if (map_data.tile[y2][x1] == 1 || map_data.tile[y2][x2] == 1)
			{
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= (height_frame_ + 1);
				y_val_ = 0;
			}
		}
		else if (y_val_ < 0)
		{
			if (map_data.tile[y1][x1] == 1 || map_data.tile[y1][x2] == 1)
			{
				y_pos_ = (y1 + 1)*TILE_SIZE;
				y_val_ = 0;
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0 || x_pos_ + width_frame_ > SCREEN_WIDTH)
	{
		x_pos_ -= x_val_;
	}
	if (y_pos_ < 0 || y_pos_ + 64 > SCREEN_HEIGHT)
	{
		y_pos_ -= y_val_;
	}
	
}