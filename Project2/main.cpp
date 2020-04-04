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
	for (int i = 0; i < 1; i++)
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

		for (int i = 0; i < 1; i++)
		{
			EnemyTankObject* pEnemy = list_enemy.at(i);
			if (pEnemy != NULL)
			{
				pEnemy->SetMapXY(map_data.start_x_, map_data.start_y_);
				pEnemy->MoveTank(map_data);
				pEnemy->MakeBullet(gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);
				pEnemy->Show(gScreen);
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
	close();
	return 0;
} 