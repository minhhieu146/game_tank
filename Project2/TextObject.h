#ifndef TEXT_OBJ_
#define TEXT_OBJ_

#include"CommonFuntion.h"
#include"BasicObject.h"

class TextObject : public BasicObject
{
public:
	TextObject();
	~TextObject();


	void SetText(const std::string& str_) { str = str_; };
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* des);
	void Free();
	void RenderText(SDL_Renderer* des, int x_location_, int y_location_, SDL_Rect* clip);
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	

private:
	std::string str;
	SDL_Color text_color;
	SDL_Texture* show_text;
	int width;
	int height;
};

#endif // !TEXT_OBJ_
