#include"TankObject.h"
#include"BulletObject.h"
#include"Game Map.h"

TankObject::TankObject()
{
	frame_ = 0;
	x_location = 100;
	y_location = 300;
	x_change = 0;
	y_change = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = -1;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;
}

TankObject::~TankObject()
{
	
}

bool TankObject::LoadImage(std::string path, SDL_Renderer* screen)
{
	bool ret = BasicObject::LoadImage(path, screen);
	return ret;
}



SDL_Rect TankObject::GetRectTank()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = 64;
	rect.h = 64;
	return rect;
}


void TankObject::Show(SDL_Renderer* des)
{
	if (status_ == MOVE_LEFT)
	{
		LoadImage("tankleft.png", des);	
		
		width_frame_ = rect_.w / 8;
		height_frame_ = rect_.h;
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;
	}
	else
		if(status_ == MOVE_RIGHT)
	{
		LoadImage("tankright.png", des);
		
		width_frame_ = rect_.w / 8;
		height_frame_ = rect_.h;
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;
	}
		else if (status_ == MOVE_UP)
		{
			LoadImage("tankup.png", des);
			
			width_frame_ = rect_.w;
			height_frame_ = rect_.h / 8;
			frame_clip_[0].x = 0;
			frame_clip_[0].y = 0;
			frame_clip_[0].w = width_frame_;
			frame_clip_[0].h = height_frame_;

		}
		else if (status_ = MOVE_DOWN)
		{
	
			LoadImage("tankdown.png", des);
			
			width_frame_ = rect_.w;
			height_frame_ = rect_.h / 8;
			frame_clip_[0].x = 0;
			frame_clip_[0].y = 0;
			frame_clip_[0].w = width_frame_;
			frame_clip_[0].h = height_frame_;
		}

	rect_.x = x_location;	//toa do tank
	rect_.y = y_location;

	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect render_region = { rect_.x, rect_.y, width_frame_, height_frame_ };

	SDL_RenderCopy(des, fact_screen, current_clip, &render_region );
}

void TankObject::InputKeyboard(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			status_ = MOVE_RIGHT;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			input_type_.up_ = 0;
			input_type_.down_ = 0;
		}
		break;
		case SDLK_LEFT:
		{
			status_ = MOVE_LEFT;
			input_type_.left_ = 1;
			input_type_.right_ = 0;
			input_type_.down_ = 0;
			input_type_.up_ = 0;
		}
		break;
		case SDLK_UP:
		{
			status_ = MOVE_UP;
			input_type_.up_ = 1;
			input_type_.down_ = 0;
			input_type_.right_ = 0;
			input_type_.left_ = 0;
		}
		break;
		case SDLK_DOWN:
		{
			status_ = MOVE_DOWN;
			input_type_.down_ = 1;
			input_type_.up_ = 0;
			input_type_.left_ = 0;
			input_type_.right_ = 0;
		}
		break;
		}
	} 
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			status_ = MOVE_RIGHT;
			input_type_.right_ = 0;
			input_type_.left_ = 0;
			input_type_.down_ = 0;
			input_type_.up_ = 0;
		}
		break;
		case SDLK_LEFT:
		{
			status_ = MOVE_LEFT;
			input_type_.right_ = 0;
			input_type_.left_ = 0;
			input_type_.down_ = 0;
			input_type_.up_ = 0;
		}
		break;
		case SDLK_UP:
		{
			status_ = MOVE_UP;
			input_type_.right_ = 0;
			input_type_.left_ = 0;
			input_type_.down_ = 0;
			input_type_.up_ = 0;
		}
		break;
		case SDLK_DOWN:
		{
			status_ = MOVE_DOWN;
			input_type_.right_ = 0;
			input_type_.left_ = 0;
			input_type_.down_ = 0;
			input_type_.up_ = 0;
		}
		break;
		}
	}
	
	if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			BulletObject* bullet = new BulletObject();
			if (status_ == MOVE_RIGHT)
			{
				bullet->LoadImage("BulletRight.png", screen);
				bullet->set_bullet_direction(BulletObject::DIR_RIGHT);
			bullet->set_x_change(20);
			}
			else if (status_ == MOVE_LEFT)
			{
				bullet->LoadImage("BulletLeft.png", screen);
				bullet->set_bullet_direction(BulletObject::DIR_LEFT);
				bullet->set_x_change(20);
			}
			else if (status_ == MOVE_UP)
			{
				bullet->LoadImage("BulletUp.png", screen);
				bullet->set_bullet_direction(BulletObject::DIR_UP);
				bullet->set_y_change(20);
			}
			else if (status_ == MOVE_DOWN)
			{
				bullet->LoadImage("BulletDown.png", screen);
				bullet->set_bullet_direction(BulletObject::DIR_DOWN);
				bullet->set_y_change(20);
			}
			bullet->SetRect(this->rect_.x + width_frame_ - 65, this->rect_.y + height_frame_ * 0.5 - 20);
			bullet->set_is_move(true);

			p_bullet_list_.push_back(bullet);

		}
	}
}
GameMapObject game_map;
Map map_data = game_map.getMap();

void TankObject::BulletMove(SDL_Renderer* des)
{
	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		BulletObject* bullet = p_bullet_list_.at(i);
		if (bullet != NULL)
		{
			if (bullet->get_is_move() == true)
			{
				bullet->Move(SCREEN_WIDTH, SCREEN_HEIGHT);
				bullet->Render(des);
			}
			else
			{
				p_bullet_list_.erase(p_bullet_list_.begin() + i);
				if (bullet != NULL)
				{
					delete bullet;
					bullet = NULL;
				}
			}
		}
	}
}

void TankObject::RemoveBullet(const int& idx)
{
	int size = p_bullet_list_.size();
	if (size > 0 && idx < size)
	{
		BulletObject* pBullet = p_bullet_list_.at(idx);
		p_bullet_list_.erase(p_bullet_list_.begin() + idx);
		if (pBullet != NULL)
		{
			delete pBullet;
			pBullet = NULL;
		}
	}
}


void TankObject::MoveTank(Map& map_data)
{
	x_change = 0;		//buoc di cua tank
	y_change =0;

	

	if (input_type_.left_ == 1)
	{
		x_change -= TANK_SPEED; 
	}
	else if (input_type_.right_ == 1)
	{
		x_change += TANK_SPEED;
	}
	else if (input_type_.up_ == 1)
	{
		y_change -= TANK_SPEED;
	}
	else if (input_type_.down_ == 1)
	{
		y_change += TANK_SPEED;
	}

	CheckMap(map_data);
}

void TankObject::CheckMap(Map& map_data)
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
			if (map_data.tile[y1][x2] == 1 || map_data.tile[y2][x2] == 1 )
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
		else if (y_change< 0)
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

