#include"EnemyTankObject.h"

EnemyTankObject::EnemyTankObject()
{
	x_location = 0.0;			//tọa độ ban đầu cho là  0
	y_location = 0.0;
	width_frame_ = 60;			// chiều rộng và cao của ảnh tank
	height_frame_ = 64;
	x_change = 0.0;				//ban đầu thì chưa di chuyển nên lượng thay đổi bằng 0
	y_change = 0.0;
	direction = 0;				// hướng cx đặt là 0
	previous_x_location = 0;			// vị trí cũ trước khi bot thực hiện di chuyển
	previous_y_location = 0;
	turningLimit = 0;						// thời gian chờ giữa 2 lần bot thực hiện di chuyển	
	check_dir = -1;						// check hướng của bot để bắn đạn theo hướng đấy
	frame_.x = 0;					
	frame_.y = 0;
	frame_.w = width_frame_;
	frame_.h = height_frame_;
}

EnemyTankObject::~EnemyTankObject()
{

}

bool EnemyTankObject::LoadImage(std::string path, SDL_Renderer* screen)		//viết hàm load ảnh
{
	bool ret = BasicObject::LoadImage(path, screen);
	return ret;
}

void EnemyTankObject::Show(SDL_Renderer* des)					//load ảnh và render lên màn hình
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

void EnemyTankObject::MoveTank(Map& map_data)					// hàm di chuyển của bot
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
		if (direction == 1)				// hướng được random từ 1 đến 4 
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

		CheckMap(map_data);				// check va chạm với các vật cản


		if (previous_x_location == x_location && previous_y_location == y_location)			// nếu vị trí cũ bằng vị trí mới
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
	int x2 = 0;		//tọa độ phải

	int y1 = 0;		//tọa độ trên
	int y2 = 0;		//tọa độ dưới

	//check theo chieu ngang
	int height_min = height_frame_ - 5;									// trừ đi lượng xung quanh ko có tank của ảnh

	x1 = (x_location + x_change + 2 ) / TILE_SIZE;							//tính cả lượng di chuyển
	x2 = (x_location + x_change + width_frame_ - 1) / TILE_SIZE;		// chia TILE_SIZE để ra ô thứ bao nhiêu 
																		//vì bản đồ có chia ô
	y1 = y_location / TILE_SIZE;
	y2 = (y_location + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)			//kiểm tra xem có ở trong màn hình ko
	{
		if (x_change > 0)														//check khi vật di chuyển sang phải
		{
			if (map_data.tile[y1][x2] == 1 || map_data.tile[y2][x2] == 1)		// check xem ô đó co phait là vật cản ko
			{
				x_location = x2 * TILE_SIZE;								//nếu đúng thì ko cho đi 
				x_location -= (width_frame_ + 1);
				x_change = 0;
			}
		}
		else if (x_change < 0)												//tương tự thì check khi tank di chuyển sang trái
		{
			if (map_data.tile[y1][x1] == 1 || map_data.tile[y2][x1] == 1)
			{
				x_location = (x1 + 1)* TILE_SIZE;
				x_change = 0;

			}
		}
	}
	//check theo chieu doc  tương tự như check với chiều ngang

	int width_min = width_frame_ - 5;
	x1 = (x_location) / TILE_SIZE;
	x2 = (x_location + width_min) / TILE_SIZE;
	y1 = (y_location + y_change + 2) / TILE_SIZE;
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

	x_location += x_change;				//nếu nó ko va chạm gì thi cho di chuyển
	y_location += y_change;

	if (x_location < 0 || x_location + width_frame_ > SCREEN_WIDTH)			//check xem nó có đi ra ngoài màn hình ko
	{
		x_location -= x_change;
	}
	if (y_location < 0 || y_location + 64 > SCREEN_HEIGHT)
	{
		y_location -= y_change;
	}
	
}



void EnemyTankObject::InitBullet(BulletObject* pBullet, SDL_Renderer* screen)		//set di chuyển và thêm đạn vào danh sách chứa
{
	if (pBullet != NULL)
	{
		
		pBullet->set_is_move(true);
		pBullet->SetRect(x_location + 22, y_location + 25);
		bullet_list_.push_back(pBullet);
	}
}

void EnemyTankObject::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)		
{																				//hàm này load ảnh đạn
	for (int i = 0; i < bullet_list_.size(); i++)								//kiểm tra đạn có trong màn hình ko
	{																			//render đạn lên màn hình
		BulletObject* pBullet = bullet_list_.at(i);
		if (pBullet != NULL)
		{
			int bullet_distance = 0;		//tạo biến khoảng  cách để đạn của bot chỉ có thể bắn trong 1 đoạn nhất định
			if (check_dir == 1)
			{
				pBullet->LoadImage("EnemyBulletLeft.png", gScreen);
				pBullet->set_bullet_direction(BulletObject::DIR_LEFT);
				pBullet->set_x_change(18);
				bullet_distance = rect_.x - pBullet->GetRect().x;
				
			}
			else if (check_dir == 2)
			{
				pBullet->LoadImage("EnemyBulletRight.png", screen);
				pBullet->set_bullet_direction(BulletObject::DIR_RIGHT);
				pBullet->set_x_change(18);
				bullet_distance = -(rect_.x, pBullet->GetRect().x);

			}
			else if (check_dir == 3)
			{
				pBullet->LoadImage("EnemyBulletUp.png", screen);
				pBullet->set_bullet_direction(BulletObject::DIR_UP);
				pBullet->set_y_change(18);
				bullet_distance = rect_.y - pBullet->GetRect().y;
			}
			else if (check_dir == 4)
			{
				pBullet->LoadImage("EnemyBulletDown.png", screen); 
				pBullet->set_bullet_direction(BulletObject::DIR_DOWN);
				pBullet->set_y_change(18);
				bullet_distance = -(rect_.y - pBullet->GetRect().y);

			}
			if (pBullet->get_is_move() == true)
			{
				if (bullet_distance <= 300)
				{
					pBullet->Move(x_limit, y_limit);		//do hàm move dùng chung 
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

void EnemyTankObject::RemoveBullet(const int& idx)			//hàm xóa đạn 
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

SDL_Rect EnemyTankObject::GetRectEnemyTank()			//trả về tọa độ của bot
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = 64;
	rect.h = 64;
	return rect;
}