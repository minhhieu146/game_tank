#include"MouseButton.h"

MouseButton::MouseButton()
{
	x_location = 620;
	y_location = 400;
	mLocation.x = 620;
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
		bool inside = true;
	//If mouse event happened
	if ( e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
			//Get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);
		if (e->button.button == SDL_BUTTON_LEFT)
		{
			//Mouse is left of the button
			if (x < mLocation.x)
			{
				inside = false;
			}
			//Mouse is right of the button
			else if (x > mLocation.x + 300)
			{
				inside = false;
			}
			//Mouse above the button
			else if (y < mLocation.y)
			{
				inside = false;
			}
			//Mouse below the button
			else if (y > mLocation.y + 150)
			{
				inside = false;
			}
		}
	}
	return inside;
}

