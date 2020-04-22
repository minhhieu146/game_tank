
#include"BasicObject.h"

BasicObject::BasicObject()
{
	fact_screen = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}

BasicObject::~BasicObject()
{
	Free();
}

bool BasicObject::LoadImage(std::string path, SDL_Renderer* screen)
{
	SDL_Texture* new_surface = NULL;
	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 255, 255, 255));		//xóa nền 
		new_surface = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_surface != NULL)
		{
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;
		}

		SDL_FreeSurface(load_surface);
	}
	fact_screen = new_surface;
	return  fact_screen != NULL;
	
}

void BasicObject::Render(SDL_Renderer* des, const SDL_Rect* clip)			//render lên màn hình
{
	SDL_Rect render_region = { rect_.x, rect_.y, rect_.w, rect_.h };		// tọa độ, chiều rộng , chiều cao ảnh

	SDL_RenderCopy(des, fact_screen, clip, &render_region);
}

void BasicObject::Free()
{
	if (fact_screen != NULL)
	{
		SDL_DestroyTexture(fact_screen);
		fact_screen = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
	
}

