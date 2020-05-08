#pragma once
#include <SDL_mixer.h>
#include <iostream>
using namespace std;
class Music
{
public:
	Mix_Chunk* gChunk = NULL;
	Mix_Music* gMusic = NULL;
	Music();
	void loadMusic(string path);
	void loadChunk(string path);
	void playMusic();
};

