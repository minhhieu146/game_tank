#include "Music.h"

void Music::loadMusic(string path)
{
	this->gMusic = Mix_LoadMUS(path.c_str());
}

void Music::loadChunk(string path)
{
	this->gChunk = Mix_LoadWAV(path.c_str());
}
void Music::playMusic() {
	if (gChunk) {
		Mix_PlayChannel(-1, gChunk, 0);
	};
	if (gMusic) {
		Mix_PlayMusic(gMusic, -1);
	}
}