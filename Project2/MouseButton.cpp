#include"MouseButton.h"

MouseButton::MouseButton()
{
	
	mLocation.x = 480;
	mLocation.y = 400;
}

MouseButton::~MouseButton()
{

}


void MouseButton::setLocation(int x, int y)
{
	mLocation.x = x;
	mLocation.y = y;
}

bool MouseButton::HandleEvent(SDL_Event* e)
{
		bool inside = false;
	//If mouse event happened
	if ( e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
			//Get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);
		
			
			if (x > mLocation.x && x < (mLocation.x + 310) && y > mLocation.y && y < (mLocation.y + 50)) {
				inside = true;
			}
	}
	return inside;
}

