#include"EnemyTankObject.h"
#include"BaseObject.h"
#include"CommonFuntion.h"
#include"BulletObject.h"

EnemyTankObject::EnemyTankObject()
{
	x_pos_ = 00.0;
	y_pos_ = 00.0;
	width_frame_ = 60;
	height_frame_ = 60;
	x_val_ = 0.0;
	y_val_ = 0.0;
	frame_ = 0;
	direction = 0;
	previous_x_pos_ = 0;
	previous_y_pos_ = 0;
	turningLimit = 0;
	check_dir = -1;
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
		check_dir = 1;
	}
	else if (direction == 2)
	{
		LoadImage("tankright.png", des);
		check_dir = 2;
	}
	else if (direction == 3)
	{
		LoadImage("tankup.png", des);
		check_dir = 3;
	}
	else if (direction == 4)
	{
		LoadImage("tankdown.png", des);
		check_dir = 4;
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

	if (turningLimit <= 0)
	{
		direction = rand() % 4 + 1;
		turningLimit = 50;
		if (direction == 1)
		{
			check_dir = 1;
		}
		else if (direction == 2)
		{
			check_dir = 2;
		}
		else if (direction == 3)
		{
			check_dir = 3;
		}
		else if (direction == 4)
		{
			check_dir = 4;
		}
	}

	bool okay = false;

	turningLimit--;

	srand((int)time(0) + rand());
	while (!okay)
	{
		if (direction == 1)
		{
			x_val_ = -(rand() % (7)+1);
			y_val_ = 0;
			check_dir = 1;
		}
		else if (direction == 2)
		{
			x_val_ = rand() % (7)+1;
			y_val_ = 0;
			check_dir = 2;
		}
		else if (direction == 3)
		{
			x_val_ = 0;
			y_val_  = -(rand() % (7)+1);
			check_dir = 3;
		}
		else if (direction == 4)
		{
			x_val_ = 0;
			y_val_ = rand() % (7)+1;
			check_dir = 4;
		}

		CheckMap(map_data);


		if (previous_x_pos_ == x_pos_ && previous_y_pos_ == y_pos_)
		{
			frame_stay_still++;
			CheckMap(map_data);

		}



		if (frame_stay_still >= 3 && turningLimit <=0)
		{

			int tempDir = direction + 1;
			if (tempDir > 4)
				tempDir = 0;
			direction = tempDir;
			/*
			int tempDir = rand() % 4 + 1;
			while (tempDir==direction)
			{
				tempDir = rand() % 4 + 1;
			}
			direction = tempDir;*/
			frame_stay_still = 0;
			turningLimit = 50;

		}
		else
		{
			okay = true;
		}
	}
	previous_x_pos_ = x_pos_;
	previous_y_pos_ = y_pos_;
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



void EnemyTankObject::InitBullet(BulletObject* pBullet, SDL_Renderer* screen)
{
	if (pBullet != NULL)
	{
		
		pBullet->set_is_move(true);
		pBullet->SetRect(x_pos_ + 5, y_pos_ + 10);
		bullet_list_.push_back(pBullet);
	}
}

void EnemyTankObject::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < bullet_list_.size(); i++)
	{
		BulletObject* pBullet = bullet_list_.at(i);
		if (pBullet != NULL)
		{
			int bullet_distance = 0;
			if (check_dir == 1)
			{
				pBullet->LoadImage("BulletLeft.png", screen);
				pBullet->set_bullet_direction(BulletObject::DIR_LEFT);
				pBullet->set_x_val_(20);
				bullet_distance = rect_.x - pBullet->GetRect().x;
				
			}
			else if (check_dir == 2)
			{
				pBullet->LoadImage("BulletRight.png", screen);
				pBullet->set_bullet_direction(BulletObject::DIR_RIGHT);
				pBullet->set_x_val_(20);
				bullet_distance = -(rect_.x, pBullet->GetRect().x);

			}
			else if (check_dir == 3)
			{
				pBullet->LoadImage("BulletUp.png", screen);
				pBullet->set_bullet_direction(BulletObject::DIR_UP);
				pBullet->set_y_val_(20);
				bullet_distance = rect_.y - pBullet->GetRect().y;
			}
			else if (check_dir == 4)
			{
				pBullet->LoadImage("BulletDown.png", screen);
				pBullet->set_bullet_direction(BulletObject::DIR_DOWN);
				pBullet->set_y_val_(20);
				bullet_distance = -(rect_.y - pBullet->GetRect().y);

			}
			if (pBullet->get_is_move() == true)
			{
				if (bullet_distance <= 300)
				{
					pBullet->HandleMove(x_limit, y_limit);
					pBullet->Render(screen);
				}
				else
				{
					pBullet->set_is_move(false);
				}
				
			}
			else
			{
				pBullet->set_is_move(true);
				pBullet->SetRect(x_pos_ + 10, y_pos_);
			}
		}
	}
}

void EnemyTankObject::RemoveBullet(const int& idx)
{
	int size = bullet_list_.size();
	if (size > 0 && idx < size)
	{
		BulletObject* pBullet = bullet_list_.at(idx);
		bullet_list_.erase(bullet_list_.begin() + idx);
		if (pBullet != NULL)
		{
			delete pBullet;
			pBullet = NULL;
		}
	}
}

SDL_Rect EnemyTankObject::GetRectTank()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = 64;
	rect.h = 64;
	return rect;
}