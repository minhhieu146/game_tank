#ifndef ENEMY_TANK_OBJECT_
#define ENEMY_TANK_OBJECT_


#include"CommonFuntion.h"
#include"BasicObject.h"
#include"BulletObject.h"


class EnemyTankObject : public BasicObject
{
public:
	EnemyTankObject();
	~EnemyTankObject();


	void set_x_change(const float& xChange) { x_change = xChange; }
	void set_y_change(const float& yChange) { y_change = yChange; }
	
	void set_x_location(const float& xLocation) { x_location = xLocation; }
	void set_y_location(const float& yLocation) { y_location = yLocation; }

	int get_x_change() const { return x_change; }
	int get_y_change() const { return y_change; }

	float get_x_location() const { return x_location; }
	float get_y_location() const { return y_location; }

	void set_check_dir( int& checkDir) { check_dir = checkDir; }
	int get_check_dir()  { return check_dir; }
	
	bool LoadImage(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	int get_width_frame() const { return width_frame_; }
	int get_height_frame() const { return height_frame_; }
	void MoveTank(Map& map_data);
	void CheckMap(Map& map_data);
	void SetMapXY(const int& mp_x, const int& mp_y) { map_x_ = mp_x; map_y_ = mp_y; };


	std::vector<BulletObject*> get_bullet_list() const { return bullet_list_; };
	void set_bullet_list(const std::vector<BulletObject*> &bl_list) { bullet_list_ = bl_list; };

	void InitBullet(BulletObject* pBullet, SDL_Renderer* screen);
	void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);

	void RemoveBullet(const int& idx);

	SDL_Rect GetRectEnemyTank();
	

private:
	
	int map_x_;
	int map_y_;
	float x_location, previous_x_location;
	float y_location, previous_y_location;
	SDL_Rect frame_clip[8];
	float x_change;
	float y_change;
	int width_frame_;
	int height_frame_;
	int frame_, frame_stay_still =0;
	int direction;
	int turningLimit;
	std::vector<BulletObject*> bullet_list_;
	int check_dir;
};

#endif // 
