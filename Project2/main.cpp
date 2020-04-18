#include"CommonFuntion.h"
#include"BasicObject.h"
#include"Game Map.h"
#include"TankObject.h"
#include"Time.h"
#include"EnemyTankObject.h"
#include"BulletObject.h"
#include"Explosive Effect.h"
#include"TextObject.h"
#include"LoadTexture.h"
#include"MouseButton.h"

BasicObject gBackground;
TTF_Font* font_text = NULL;

bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_EVERYTHING);
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
		if (TTF_Init() == -1)
		{
			success = false; 
		}
		
		font_text = TTF_OpenFont("font text//dlxfont_.ttf", 12);

	}
	return success;
}

bool LoadBackground()
{
	bool ret = gBackground.LoadImage("maptank.png", gScreen);
	if (ret == FALSE)return false;
	return true;
}
BasicObject game_over;
bool LoadGameOver()
{
	bool ret = game_over.LoadImage("GameOver.png", gScreen);
	if (ret == FALSE) return false;
	return true;
}

BasicObject game_menu;
bool Load_Menu()
{
	bool ret = game_menu.LoadImage("map-game.png", gScreen);
	if (ret == FALSE) return false;
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
	EnemyTankObject* enemy_obj = new EnemyTankObject[5];
	for (int i = 0; i < 5; i++)
	{
		EnemyTankObject* pEnemy = (enemy_obj + i);
		if (pEnemy != NULL)
		{
			pEnemy->LoadImage("tankup.png", gScreen);
			pEnemy->set_x_location(1100.0);
			pEnemy->set_y_location(100.0 + 100.0 * i); 
			BulletObject* pBullet = new BulletObject();
			pEnemy->InitBullet(pBullet, gScreen);
			list_enemy.push_back(pEnemy);
		}
	}
	return list_enemy;
}

Gallery* gallery = nullptr; // global picture manager
MouseButton gButton;

int main(int agrc, char* agrv[])
{
	TimeObject fps_time;

	if (InitData() == FALSE)
	{
		return -1;
	}
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
			}
		}

		game_menu.Render(gScreen);
		SDL_RenderPresent(gScreen);
	}
	


	GameMapObject game_map;
	game_map.LoadMap("map/maptank.txt");
	game_map.LoadTiles(gScreen);
	
	TankObject tank;
	tank.LoadImage("tankrdown.png", gScreen);

	std::vector<EnemyTankObject*> list_enemy = MakeEnemyList();
	
	ExplosiveEffectObject ex_enemy;
	bool rec = ex_enemy.LoadImage("Explosion.png", gScreen);
	if (rec != NULL)
	{
		ex_enemy.set_clip();
	}
	
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
			tank.InputKeyboard(gEvent, gScreen);
		}
		SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);
		SDL_RenderClear(gScreen);

		gBackground.Render(gScreen, NULL);
		game_map.DrawMap(gScreen); 
		Map map_data = game_map.getMap();

		
		tank.MoveTank(map_data);
		tank.Show(gScreen);
		tank.BulletMove(gScreen);

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

				SDL_Rect rect_enemy = pEnemy->GetRectEnemyTank();
				bool COLL = false;
				COLL = SDL_CommonFunc::CheckCollision(rect_main_tank, rect_enemy);
				if ( COLL == true ||colli == true)
				{
					
					
						pEnemy->Free();
						game_over.Render(gScreen, NULL);
							//SDL_Quit();
							//close();
						//	return 0;
						
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
							
							for (int ex = 0; ex < 8; ex++)
							{
								int x_location = bRect.x - 50;
								int y_location = bRect.y - 50;
								ex_enemy.set_frame_number(ex);
								ex_enemy.SetRect(x_location, y_location);
								ex_enemy.Show(gScreen);
								
							}
							
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
		

		int real_imp_time = fps_time.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;
		if (real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			if(delay_time >= 0)
			SDL_Delay(delay_time);
		}
	}

	for (int i = 0; i < list_enemy.size(); i++)
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