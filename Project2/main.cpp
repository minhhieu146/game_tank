#include"CommonFuntion.h"
#include"BaseObject.h"
#include"Game_map.h"
#include"TankObject.h"
#include"ImpTimer.h"
#include"EnemyTankObject.h"
#include"BulletObject.h"

BaseObject gBackground;
bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
	{
		return false;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	gWindow = SDL_CreateWindow("Game Battle Tank", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		success = false;
	}
	else
	{
		gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gScreen == NULL)
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);
			int imgFlats = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlats) && imgFlats))
				success = false;

		}
	}
	return success;
}

bool LoadBackground()
{
	bool ret = gBackground.LoadImage("maptank.png", gScreen);
	if (ret == FALSE)return false;
	return true;
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
  
std::vector<EnemyTankObject*> MakeEnemyList()
{
	std::vector<EnemyTankObject*> list_enemy;
	EnemyTankObject* enemy_obj = new EnemyTankObject[3];
	for (int i = 0; i < 2; i++)
	{
		EnemyTankObject* pEnemy = (enemy_obj + i);
		if (pEnemy != NULL)
		{
			pEnemy->LoadImage("tankup.png", gScreen);
			pEnemy->set_x_pos_(1100.0);
			pEnemy->set_y_pos_(100.0 + 200.0 * i);

			BulletObject* pBullet = new BulletObject();
			pEnemy->InitBullet(pBullet, gScreen);

			list_enemy.push_back(pEnemy);
		}
	}
	return list_enemy;
}

int main(int agrc, char* agrv[])
{
	ImpTimer fps_timer;

	if (InitData() == FALSE)
	{
		return -1;
	}
	if (LoadBackground() == FALSE)
	{
		return -1;
	}

	GameMap game_map;
	game_map.LoadMap("map/maptank.txt");
	game_map.LoadTiles(gScreen);
	
	MainObject tank;
	tank.LoadImage("tankrdown.png", gScreen);

	std::vector<EnemyTankObject*> list_enemy = MakeEnemyList();
	

	bool is_quit = false;
	while(!is_quit)
	{
		fps_timer.start();
		while (SDL_PollEvent(&gEvent) != 0)
		{
			if (gEvent.type == SDL_QUIT)
			{
				is_quit = true;
			}
			tank.HandelInput(gEvent, gScreen);
		}
		SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);
		SDL_RenderClear(gScreen);

		gBackground.Render(gScreen, NULL);
		game_map.DrawMap(gScreen); 
		Map map_data = game_map.getMap();

		
		tank.DoTank(map_data);
		tank.Show(gScreen);
		tank.HandleBullet(gScreen);

		for (int i = 0; i < list_enemy.size(); i++)
		{
			EnemyTankObject* pEnemy = list_enemy.at(i);
			if (pEnemy != NULL)
			{
				pEnemy->SetMapXY(map_data.start_x_, map_data.start_y_);
				pEnemy->MakeBullet(gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);
				pEnemy->MoveTank(map_data);
				pEnemy->Show(gScreen);

				SDL_Rect rect_main_tank = tank.GetRectTank();
				bool colli = false;
				std::vector<BulletObject*> eBullet_list = pEnemy->get_bullet_list();
				for (int j = 0; j < eBullet_list.size(); j++)
				{
					BulletObject* eBullet = eBullet_list.at(j);
					if (eBullet != NULL)
					{
						colli = SDL_CommonFunc::CheckCollision(eBullet->GetRect(), rect_main_tank);
						if (colli == true)
						{
							pEnemy->RemoveBullet(j);
							break;
						}
		
					}
				}

				SDL_Rect rect_enemy = pEnemy->GetRectTank();
				bool COLL = false;
				COLL = SDL_CommonFunc::CheckCollision(rect_main_tank, rect_enemy);
				if ( COLL == true ||colli == true)
				{
						pEnemy->Free();
						close();
						SDL_Quit();
						return 0;
				}

			}
		}

		std::vector<BulletObject*> bullet_arr = tank.get_bullet_list_();
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
						SDL_Rect eRect;
						eRect.x = EnemyTank->GetRect().x;
						eRect.y = EnemyTank->GetRect().y;
						eRect.w = EnemyTank->get_width_frame();
						eRect.h = EnemyTank->get_height_frame();

						SDL_Rect bRect;
						bRect.x = p_bullet->GetRect().x;
						bRect.y = p_bullet->GetRect().y;

						bool coll = SDL_CommonFunc::CheckCollision(bRect, eRect);
						bool coll_1 = p_bullet->CheckMapForBullet(map_data, bRect);	

						if (coll == true)
						{
							tank.RemoveBullet(i); 
							EnemyTank->Free();
							list_enemy.erase(list_enemy.begin() + j);
						}

						if (coll_1 == true)
						{
							tank.RemoveBullet(i);
						}
					}
				}
			}
		}

		SDL_RenderPresent(gScreen);

		int real_imp_time = fps_timer.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;
		if (real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			if(delay_time >= 0)
			SDL_Delay(delay_time);
		}
	}

	for (int i = 0; i < 2; i++)
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