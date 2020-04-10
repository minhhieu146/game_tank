#ifndef ENEMY_TANK_OBJECT_
#define ENEMY_TANK_OBJECT_


#include"CommonFuntion.h"
#include"BaseObject.h"
#include"BulletObject.h"


class EnemyTankObject : public BaseObject
{
public:
	EnemyTankObject();
	~EnemyTankObject();


	void set_x_val_(const float& xVal) { x_val_ = xVal; }
	void set_y_val(const float& yVal) { y_val_ = yVal; }
	
	void set_x_pos_(const float& xPos) { x_pos_ = xPos; }
	void set_y_pos_(const float& yPos) { y_pos_ = yPos; }

	int get_x_val_() const { return x_val_; }
	int get_y_val_() const { return y_val_; }

	float get_x_pos_() const { return x_pos_; }
	float get_y_pos_() const { return y_pos_; }

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

	SDL_Rect GetRectTank();
	

private:
	
	int map_x_;
	int map_y_;
	float x_pos_, previous_x_pos_;
	float y_pos_, previous_y_pos_;
	SDL_Rect frame_clip[8];
	float x_val_;
	float y_val_;
	int width_frame_;
	int height_frame_;
	int frame_, frame_stay_still =0;
	int direction;
	int turningLimit;
	std::vector<BulletObject*> bullet_list_;
	int check_dir;
};

#endif // 
