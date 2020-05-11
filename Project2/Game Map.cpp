#include"Game Map.h"


void GameMapObject::LoadTiles(SDL_Renderer* screen)  //  hàm này là e coppy từ phát triển phần mềm 123az
{
	char tile_type[10]; 
	FILE* fp = NULL;

	for (int i = 0; i < MAP_TILES; i++)
	{
		sprintf_s(tile_type, "map/%d.png", i);
		fopen_s(&fp, tile_type, "rb");
		if (fp == NULL)
		{
			continue;
		}
		fclose(fp);
		tile_map[i].LoadImage(tile_type, screen);
	}
}


void GameMapObject::DrawMap(SDL_Renderer* screen)  //vẽ map lên màn hình
{
	int x1 = 0;
	int x2 = SCREEN_WIDTH;
	 
	int y1 = 0;
	int y2 = SCREEN_HEIGHT;

	int map_x_ = 0;  // đang là ở ô thứ bao nhiêu
	int map_y_ = 0;	 

	game_map.start_x_ = 0;
	game_map.start_y_ = 0;

	map_x_ = game_map.start_x_ / TILE_SIZE;
	map_y_ = game_map.start_y_ / TILE_SIZE;

	for (int i = y1; i < y2; i += TILE_SIZE)
	{
		map_x_ = game_map.start_x_ / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			int value = game_map.tile[map_y_][map_x_];
			if (value > 0)
			{
				tile_map[value].SetRect(j, i);
				tile_map[value].Render(screen);
			}
			map_x_++;
		} 
		map_y_++;
	}
}

