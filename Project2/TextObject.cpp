#include"TextObject.h"

TextObject::TextObject()
{
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
	show_text = NULL;
}

TextObject::~TextObject()
{
	Free();
}

bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
	SDL_Surface* text_surface = TTF_RenderText_Blended(font, str.c_str(), text_color);
	if (text_surface  )
	{
		show_text = SDL_CreateTextureFromSurface(screen, text_surface);
		width = text_surface->w;
		height = text_surface->h;
		SDL_FreeSurface(text_surface);
	}

	return show_text != NULL;
}

void TextObject::Free()
{
	if (show_text != NULL)
	{
		SDL_DestroyTexture(show_text);
		show_text = NULL;
	}
}

void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	text_color.r = red;
	text_color.g = green;
	text_color.b = blue;
}

void TextObject::RenderText(SDL_Renderer* des, int x_location_, int y_location_, SDL_Rect* clip)
{
	
	SDL_Rect render_region = { x_location_, y_location_, width, height };
	if (clip != NULL)
	{
		render_region.w = clip->w;
		render_region.h = clip->h; 
	}
	SDL_RenderCopy(des, show_text, clip, &render_region);
}
