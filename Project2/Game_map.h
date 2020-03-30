#ifndef GAME_MAP_H
#define GAME_MAP_H
#define MAP_TILES 10

#include"CommonFuntion.h";
#include"BaseObject.h";

class TileMap : public BaseObject
{
public:
	TileMap() { ; }
	~TileMap() { ; }
};

class GameMap
{
public: 
	GameMap() { ; }
	~GameMap() { ; }

	void LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	Map  getMap() const { return game_map_; };
private:
	Map game_map_;
	TileMap tile_map[MAP_TILES];
};
#endif // !
