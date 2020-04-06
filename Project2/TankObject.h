#ifndef TANK_OBJECT_
#define TANK_OBJECT_

#include"CommonFuntion.h";
#include"BaseObject.h";
#include<vector>
#include"BulletObject.h"

#define TANK_SPEED 5

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	enum MoveType
	{
		MOVE_RIGHT = 0,
		MOVE_LEFT = 1,
		MOVE_UP = 2,
		MOVE_DOWN = 3,
	};
	
	bool LoadImage(std::string path, SDL_Renderer* screen);
	void HandelInput(SDL_Event events, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);

	void DoTank(Map& map_data);
	void CheckMap(Map& map_dada);


	void set_bullet_list_(std::vector<BulletObject*> bullet_list)
	{
		p_bullet_list_ = bullet_list;
	}
	std::vector<BulletObject*> get_bullet_list_() const { return p_bullet_list_; }
	void HandleBullet(SDL_Renderer* des);
	void RemoveBullet(const int& idx);

private:

	std::vector<BulletObject*> p_bullet_list_;
	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int	height_frame_;

	SDL_Rect frame_clip_[8];
	Input input_type_;
	int frame_;
	int status_;
};

#endif 
