#include"EnemyTankObject.h"

EnemyTankObject::EnemyTankObject()
{
	x_location = 0.0;
	y_location = 0.0;
	width_frame_ = 60;
	height_frame_ = 64;
	x_change = 0.0;
	y_change = 0.0;
	direction = 0;
	previous_x_location = 0;
	previous_y_location = 0;
	turningLimit = 0;
	check_dir = -1;
	frame_.x = 0;
	frame_.y = 0;
	frame_.w = width_frame_;
	frame_.h = height_frame_;
}

EnemyTankObject::~EnemyTankObject()
{

}

bool EnemyTankObject::LoadImage(std::string path, SDL_Renderer* screen)
{
	bool ret = BasicObject::LoadImage(path, screen);
	return ret;
}

void EnemyTankObject::Show(SDL_Renderer* des)
{
	if (direction == 1)
	{
		LoadImage("enemytankleft.png", des);
		check_dir = 1;
	}
	else if (direction == 2)
	{
		LoadImage("enemytankright.png", des);
		check_dir = 2;
	}
	else if (direction == 3)
	{
		LoadImage("enemytankup.png", des);
		check_dir = 3;
	}
	else if (direction == 4)
	{
		LoadImage("enemytankdown.png", des);
		check_dir = 4;
	}

		rect_.x = x_location;
		rect_.y = y_location;
		SDL_Rect* rect_e_tank = &frame_;
		SDL_Rect render_region = { rect_.x, rect_.y, width_frame_, height_frame_ };
		SDL_RenderCopy(des, fact_screen, rect_e_tank, &render_region);

}

void EnemyTankObject::MoveTank(Map& map_data)
{
	srand(time(0) + rand());

	if (turningLimit <= 0)				// để có 1 khoảng thời gian chờ sauu khi đổi hướng 
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

	srand(time(0) + rand());
	while (!okay)
	{
		if (direction == 1)
		{
			x_change = -(rand() % (7)+1);
			y_change = 0;
			check_dir = 1;
		}
		else if (direction == 2)
		{
			x_change = rand() % (7)+1;
			y_change = 0;
			check_dir = 2;
		}
		else if (direction == 3)
		{
			x_change = 0;
			y_change = -(rand() % (7)+1);
			check_dir = 3;
		}
		else if (direction == 4)
		{
			x_change = 0;
			y_change = rand() % (7)+1;
			check_dir = 4;
		}

		CheckMap(map_data);


		if (previous_x_location == x_location && previous_y_location == y_location)
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
	previous_x_location = x_location;
	previous_y_location = y_location;
}



void EnemyTankObject::CheckMap(Map& map_data)
{
	int x1 = 0;		//toa do ben trai
	int x2 = 0;

	int y1 = 0;		//toa do ben phai
	int y2 = 0;

	//check theo chieu ngang
	int height_min = height_frame_ - 10;  

	x1 = (x_location + x_change) / TILE_SIZE;
	x2 = (x_location + x_change + width_frame_ - 1) / TILE_SIZE;

	y1 = y_location / TILE_SIZE;
	y2 = (y_location + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < (MAX_MAP_X) && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_change > 0)
		{
			if (map_data.tile[y1][x2] == 1 || map_data.tile[y2][x2] == 1)
			{
				x_location = x2 * TILE_SIZE;
				x_location -= (width_frame_ + 1);
				x_change = 0;
			}
		}
		else if (x_change < 0)
		{
			if (map_data.tile[y1][x1] == 1 || map_data.tile[y2][x1] == 1)
			{
				x_location = (x1 + 1)* TILE_SIZE;
				x_change = 0;

			}
		}
	}
	//check theo chieu doc

	int width_min = width_frame_ - 10;
	x1 = (x_location) / TILE_SIZE;
	x2 = (x_location + width_min) / TILE_SIZE;
	y1 = (y_location + y_change) / TILE_SIZE;
	y2 = (y_location + y_change + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_change > 0)
		{
			if (map_data.tile[y2][x1] == 1 || map_data.tile[y2][x2] == 1)
			{
				y_location = y2 * TILE_SIZE;
				y_location -= (height_frame_ + 1);
				y_change = 0;
			}
		}
		else if (y_change < 0)
		{
			if (map_data.tile[y1][x1] == 1 || map_data.tile[y1][x2] == 1)
			{
				y_location = (y1 + 1)*TILE_SIZE;
				y_change = 0;
			}
		}
	}

	x_location += x_change;
	y_location += y_change;

	if (x_location < 0 || x_location + width_frame_ > SCREEN_WIDTH)
	{
		x_location -= x_change;
	}
	if (y_location < 0 || y_location + 64 > SCREEN_HEIGHT)
	{
		y_location -= y_change;
	}
	
}



void EnemyTankObject::InitBullet(BulletObject* pBullet, SDL_Renderer* screen)
{
	if (pBullet != NULL)
	{
		
		pBullet->set_is_move(true);
		pBullet->SetRect(x_location + 22, y_location + 25);
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
				pBullet->LoadImage("EnemyBulletLeft.png", gScreen);
				pBullet->set_bullet_direction(BulletObject::DIR_LEFT);
				pBullet->set_x_change(20);
				bullet_distance = rect_.x - pBullet->GetRect().x;
				
			}
			else if (check_dir == 2)
			{
				pBullet->LoadImage("EnemyBulletRight.png", screen);
				pBullet->set_bullet_direction(BulletObject::DIR_RIGHT);
				pBullet->set_x_change(20);
				bullet_distance = -(rect_.x, pBullet->GetRect().x);

			}
			else if (check_dir == 3)
			{
				pBullet->LoadImage("EnemyBulletUp.png", screen);
				pBullet->set_bullet_direction(BulletObject::DIR_UP);
				pBullet->set_y_change(20);
				bullet_distance = rect_.y - pBullet->GetRect().y;
			}
			else if (check_dir == 4)
			{
				pBullet->LoadImage("EnemyBulletDown.png", screen); 
				pBullet->set_bullet_direction(BulletObject::DIR_DOWN);
				pBullet->set_y_change(20);
				bullet_distance = -(rect_.y - pBullet->GetRect().y);

			}
			if (pBullet->get_is_move() == true)
			{
				if (bullet_distance <= 300)
				{
					pBullet->Move(x_limit, y_limit);
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
				pBullet->SetRect(x_location + 15, y_location + 20 );
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

SDL_Rect EnemyTankObject::GetRectEnemyTank()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = 64;
	rect.h = 64;
	return rect;
}