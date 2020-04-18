#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<Windows.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<vector>
#include<time.h>

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent;
static SDL_Texture* gTexture = NULL;


//SCREEN
const int FRAME_PER_SECOND = 25; //fps
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;



#define TILE_SIZE 64
#define MAX_MAP_X 20
#define MAX_MAP_Y 10
#define LEFT 0
#define RIGHT 1
#define DOWN 2 
#define UP 3

typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
}; 

typedef struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
    const char* file_name;

};

namespace SDL_CommonFunc
{
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}



#endif
