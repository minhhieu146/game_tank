#ifndef TANK_OBJECT_
#define TANK_OBJECT_

#include"CommonFuntion.h";
#include"BaseObject.h";
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
	void Set_clipsLR();
	void Set_clipsDU();

	void DoTank(Map& map_data);
	void CheckToMap(Map& map_dada);
private:
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
	bool on_ground_;
};

#endif 
