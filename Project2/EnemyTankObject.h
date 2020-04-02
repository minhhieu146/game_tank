#ifndef ENEMY_TANK_OBJECT_
#define ENEMY_TANK_OBJECT_


#include"CommonFuntion.h"
#include"BaseObject.h"


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
	
	bool LoadImage(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	int get_width_frame() const { return width_frame_; }
	int get_height_frame() const { return height_frame_; }
	void MoveTank(Map& map_data);
	void CheckMap(Map& map_data);
	void SetMapXY(const int& mp_x, const int& mp_y) { map_x_ = mp_x; map_y_ = mp_y; }

private:
	
	int map_x_;
	int map_y_;
	float x_pos_;
	float y_pos_;
	SDL_Rect frame_clip[8];
	float x_val_;
	float y_val_;
	int width_frame_;
	int height_frame_;
	int frame_;
	int direction;
	

};

#endif // 
