#ifndef GALLERY_H
#define GALLERY_H

#include"SDL_utils.h"

class Gallery
{
	enum PictureID {
		 PIC_TANK_LEFT =0, PICK_TANK_RIGHT =1, PIC_TANK_UP =2,
		 PIC_TANK_DOWN =3, PIC_BULLET_LEFT =4, PIC_BULLET_RIGHT =5,
		 PIC_BULLET_DOWN =6, PIC_BULLET_UP =7, PIC_COUNT
	};


	SDL_Texture* pictures[PIC_COUNT];
	SDL_Renderer* renderer;
	SDL_Texture* loadTexture(std::string path);
public:
	Gallery(SDL_Renderer* renderer_);
	~Gallery();

	void loadGamePictures();
	SDL_Texture* getImage(PictureID id) const { return pictures[id]; }
};

#endif // !LOAD_TEXTURE_H
