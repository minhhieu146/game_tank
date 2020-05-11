#include"TankObject.h"
#include"Time.h"
#include"EnemyTankObject.h"
#include"BulletObject.h"
#include"Explosive Effect.h"
#include"MouseButton.h"


bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b)			//hàm check va chạm giữa 2 object
{
	int left_a = a.x + 5;
	int right_a = a.x + a.w - 5;
	int top_a = a.y + 5;
	int bottom_a = a.y + a.h - 5;

	int left_b = b.x + 5;
	int right_b = b.x + b.w - 5;
	int top_b = b.y + 5;
	int bottom_b = b.y + b.h - 5;

	// Case 1: size object 1 < size object 2
	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (bottom_a < top_b && bottom_a > bottom_b)
	{
		if (right_a > left_b && right_a < right_b)
		{
			return true;
		}
	}

	if (bottom_a < top_b && bottom_a > bottom_b)
	{
		if (left_a > left_b && left_a < right_b)
		{
			return true;
		}
	}

	if (top_a > top_b && top_a < bottom_b)
	{
		if (right_a > left_b && right_a < right_b)
		{
			return true;
		}
	}


	if (top_a > top_b && top_a < bottom_b)
	{
		if (left_a > left_b && left_a < right_b)
		{
			return true;
		}
	}
	// Case 2: size object 1 > size object 2
	if (left_b > left_a && left_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (left_b > left_a && left_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	if (bottom_a > top_b && bottom_a < bottom_b)
	{
		if (right_a > left_b && right_a < right_b)
		{
			return true;
		}
	}

	if (bottom_a > top_b && bottom_a < bottom_b)
	{
		if (left_a > left_b && left_a < right_b)
		{
			return true;
		}
	}

	if (top_a < bottom_b && top_a > bottom_b)
	{
		if (right_a > left_b && right_a < right_b)
		{
			return true;
		}
	}

	if (top_a < bottom_b && top_a > bottom_b)
	{
		if (left_a > left_b && left_a < right_b)
		{
			return true;
		}
	}

	// Case 3: size object 1 = size object 2
	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
	{
		return true;
	}

	return false;
}


BasicObject gBackground;
bool LoadBackground()													//load background
{
	bool ret = gBackground.LoadImage("maptank.png", gScreen);
	if (ret == FALSE)return false;
	return true;
}
BasicObject game_over;
bool LoadGameOver()														//load game over khi thua
{
	bool ret = game_over.LoadImage("GameOver.png", gScreen);
	if (ret == FALSE) return false;
	return true;
}

BasicObject game_menu;
bool Load_Menu()													// load menu để vào game
{
	bool ret = game_menu.LoadImage("menu game.png", gScreen);
	if (ret == FALSE) return false;
	return true;
}

BasicObject game_victory;
bool Load_victory()														//load ảnh chiến thắng
{
	bool ret = game_victory.LoadImage("victory.png", gScreen);
	if (ret == FALSE) return false;
	return true;
}

BasicObject game_tutorial;												//load ảnh hướng dẫn chơi
bool Load_Tutorial()
{
	bool ret = game_tutorial.LoadImage("game_tutorial.png", gScreen);
	if (ret == FALSE) return false;
	return true;
}

  
std::vector<EnemyTankObject*> MakeEnemyList()					//tạo vector chứa bot
{
	std::vector<EnemyTankObject*> list_enemy;					//vector chứa bot
	EnemyTankObject* enemy_obj = new EnemyTankObject[5];			//khởi tạo có 5 con
	for (int i = 0; i < 5; i++)
	{
		EnemyTankObject* pEnemy = (enemy_obj + i);
		if (pEnemy != NULL)
		{
			pEnemy->LoadImage("enemytankup.png", gScreen);		//load bot lên
			pEnemy->set_x_location(1100.0);						// set vị trí cho bot
			pEnemy->set_y_location(100.0 + 100.0 * i); 
			BulletObject* pBullet = new BulletObject();			// tạo đạn cho bot
			pEnemy->InitBullet(pBullet, gScreen);				//set cho đạn di chuyển và thêm vào vector chứa đạn
			list_enemy.push_back(pEnemy);						//thêm vào vector chứa đạn
		}
	}
	return list_enemy;
}

void close()
{
	gBackground.Free();
	SDL_DestroyRenderer(gScreen);
	gScreen = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

MouseButton gButton;				

int main(int agrc, char* agrv[])
{
	TimeObject fps_time;

	InitSDL(gWindow, gScreen);
	
	if (LoadBackground() == FALSE)
	{
		return -1;
	}
	if (LoadGameOver() == FALSE)
	{
		return -1;
	}
	if (Load_Menu() == FALSE)
	{
		return -1;
	}
	if (Load_victory() == FALSE)
	{
		return -1;
	}
	if (Load_Tutorial() == FALSE)
	{
		return -1;
	}

	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&gEvent) != 0)
		{
			if (gEvent.type == SDL_QUIT)
			{
				SDL_Quit();
				close();
				return 0;
			}
			else
			{
				bool check = gButton.HandleEvent(&gEvent);
				if (check == TRUE)
				{
					SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);
					SDL_RenderClear(gScreen);
					quit = true;
				}
				else if (check == FALSE)
				{
					game_menu.Render(gScreen);

				}
			}
		}

		SDL_RenderPresent(gScreen);
	}
// cái trên là load menu và chờ cho chuột nhấn vào PLAY GAME mới cho chạy game
	game_tutorial.Render(gScreen);			//sau khi nhấn vào play game thì cho render ảnh hướng dẫn
	SDL_RenderPresent(gScreen);
	SDL_Delay(5000);				//render trong 5s
	

	// load map
	GameMapObject game_map;
	game_map.LoadTiles(gScreen);			
	
	//load tank
	TankObject tank;
	tank.LoadImage("tankrdown.png", gScreen);			//load ảnh tank khi mới xuất hiện

	std::vector<EnemyTankObject*> list_enemy = MakeEnemyList();
	
	ExplosiveEffectObject ex_enemy;			//hiệu ứng nổ
	bool rec = ex_enemy.LoadImage("Explosion.png", gScreen);		//load ảnh nổ(có 8 ảnh)
	if (rec != NULL)
	{
		ex_enemy.set_clip();
	}
	
	int check_game_over = 0;   //biến logic kiểm tra game over
	bool is_quit = false;
	while(!is_quit)
	{
		fps_time.start();
		while (SDL_PollEvent(&gEvent) != 0)
		{
			if (gEvent.type == SDL_QUIT)
			{
				is_quit = true;
			}
			tank.InputKeyboard(gEvent, gScreen);		// xử lý sự kiện
		}
		SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);
		SDL_RenderClear(gScreen);

		gBackground.Render(gScreen, NULL);		//load background lên
		game_map.DrawMap(gScreen);				// vẽ các vật cản lên

		Map map_data = game_map.getMap();		//lấy dữ liệu các vật cản

		
		tank.MoveTank(map_data);		//hàm di chuyển
		tank.Show(gScreen);				// vẽ tank lên
		tank.BulletMove(gScreen);		//cho đạn di chuyển

		for (int i = 0; i < list_enemy.size(); i++)		
		{
			EnemyTankObject* pEnemy = list_enemy.at(i);
			if (pEnemy != NULL)
			{
				pEnemy->SetMapXY(map_data.start_x_, map_data.start_y_);			//set cho bot di chuyển trong phạm vi màn hình
				pEnemy->MakeBullet(gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);		//cho bot bắn đạn
				pEnemy->MoveTank(map_data);										//bot di chuyển
				pEnemy->Show(gScreen);											// vẽ bot lên màn hình

				SDL_Rect rect_main_tank = tank.GetRectTank();		// lấy tọa độ của tank chính
				bool colli = false;		//check  va chạm giữa đạn của bot và tank chính
				std::vector<BulletObject*> eBullet_list = pEnemy->get_bullet_list();		//lấy ra vetor chứa đạn của bot
				for (int j = 0; j < eBullet_list.size(); j++)								//vector này đã được khai báo
				{
					BulletObject* eBullet = eBullet_list.at(j);
					if (eBullet != NULL)
					{
						colli = CheckCollision(eBullet->GetRect(), rect_main_tank);		//check va chạm của đạn bot với tank chính
						if (colli == true)
						{
							pEnemy->RemoveBullet(j);			//xóa đạn nếu như va chạm
							break;
						}
		
					}
				}

				SDL_Rect rect_enemy = pEnemy->GetRectEnemyTank();		//lấy tọa độ bot
				bool COLL = false;				//biên check va chạm giữa 2 tank
				COLL = CheckCollision(rect_main_tank, rect_enemy);		//check va chạm giữa bot và tank
				if ( COLL == true ||colli == true)
				{
						check_game_over = 1;	
				}

			}
		}

		std::vector<BulletObject*> bullet_arr = tank.get_bullet_list_();		//lấy ra vector đạn của tank chính đã đc khai báo
		for (int i = 0; i < bullet_arr.size(); i++)
		{
			BulletObject* p_bullet = bullet_arr.at(i);
			if (p_bullet != NULL)
			{
				for (int j = 0; j < list_enemy.size(); j++)
				{
					EnemyTankObject* EnemyTank = list_enemy.at(j);
					if (EnemyTank != NULL)
					{
						SDL_Rect eRect = EnemyTank->GetRectEnemyTank();			

						SDL_Rect bRect;
						bRect.x = p_bullet->GetRect().x;
						bRect.y = p_bullet->GetRect().y;

						bool coll = CheckCollision(bRect, eRect);						//check va chạm giữa đạn của main với bot
						bool coll_1 = p_bullet->CheckMapForBullet(map_data, bRect);		// check va chạm giữa đạn main với vật cản

						if (coll == true)
						{
							for (int ex = 0; ex < 8; ex++)						//load hiệu ứng nổ
							{
								int x_location = bRect.x - 50;
								int y_location = bRect.y - 50;
								ex_enemy.set_frame_number(ex);
								ex_enemy.SetRect(x_location, y_location);
								ex_enemy.Show(gScreen);
								
							}
							
							tank.RemoveBullet(i);			//xóa đạn đã bắn trúng
							EnemyTank->Free();				//free tank bị bắn
							list_enemy.erase(list_enemy.begin() + j);		// xóa tank bị bắn ra khỏi vector
						}

						if (coll_1 == true)
						{
							tank.RemoveBullet(i);		// nếu mà bắn trúng vật cản thì chỉ xóa đạn đi
						}
					}
				}
			}
		}
		if (check_game_over == 1)
		{
			
			game_over.Render(gScreen, NULL);
		}
		if (list_enemy.empty() == true)
		{
			game_victory.Render(gScreen, NULL);
		}
		SDL_RenderPresent(gScreen);
		

		int real_imp_time = fps_time.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;
		if (real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			if(delay_time >= 0)
			SDL_Delay(delay_time);
		}
	}

	for (int i = 0; i < list_enemy.size(); i++)				//giải phóng vector
	{
		EnemyTankObject* pEnemy = list_enemy.at(i);
		if (pEnemy != NULL)
		{
			pEnemy->Free();
			pEnemy = NULL;
		}
	}

	list_enemy.clear();

	close();
	return 0;
} 