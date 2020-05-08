#pragma once
#ifndef GAME_MAP_H
#define GAME_MAP_H
#define MAP_TILES 10

#include"BasicObject.h";

class TileMap : public BasicObject
{
public:
	TileMap() { ; }
	~TileMap() { ; }
};

class GameMapObject
{
public: 
	GameMapObject() { ; }
	~GameMapObject() { ; }

	void LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	Map  getMap() const { return game_map; };
private:
	Map game_map;
	TileMap tile_map[MAP_TILES];
};


#endif // !
