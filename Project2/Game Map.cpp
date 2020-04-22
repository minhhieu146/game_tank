#include"Game Map.h"
void GameMapObject::LoadMap(const char* name)  // ddùng để đọc dữ liệu từ file
{
	FILE* fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL) {
		return;
	}
	game_map.max_x_ = 0; game_map.max_y_ = 0;

	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			fscanf_s(fp, "%d", &game_map.tile[i][j]);
			int val = game_map.tile[i][j];
			if (val > 0) {
				if (j > game_map.max_x_) {
					game_map.max_x_ = j;
				}

				if (i > game_map.max_y_) {
					game_map.max_y_ = i;
				}
			}
		}
	}

	game_map.max_x_ = (game_map.max_x_ + 1) * TILE_SIZE;
	game_map.max_y_ = (game_map.max_y_ + 1) * TILE_SIZE;
	game_map.start_x_ = 0;
	game_map.start_y_ = 0;

	game_map.file_name = name;
	fclose(fp);
}

void GameMapObject::LoadTiles(SDL_Renderer* screen)  // 
{
	char tile_type[10]; // số lượng vật thể có thể có trong map
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
	int x2 = 0;
	 
	int y1 = 0;
	int y2 = 0;

	int map_x_ = 0;
	int map_y_ = 0;

	map_x_ = game_map.start_x_ / TILE_SIZE;
	x1 = (game_map.start_x_%TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	map_y_ = game_map.start_y_ / TILE_SIZE;
	y1 = (game_map.start_y_%TILE_SIZE)*-1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	for (int i = y1; i < y2; i += TILE_SIZE)
	{
		map_x_ = game_map.start_x_ / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			int change = game_map.tile[map_y_][map_x_];
			if (change > 0)
			{
				tile_map[change].SetRect(j, i);
				tile_map[change].Render(screen);
			}
			map_x_++;
		}
		map_y_++;
	}
}