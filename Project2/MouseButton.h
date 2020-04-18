#ifndef MOUSE_BUTTON_H
#define MOUSE_BUTTON_H

#include"CommonFuntion.h"
#include"BasicObject.h"
class MouseButton : public BasicObject
{
public:
		MouseButton();
		~MouseButton();

		
		bool HandleEvent(SDL_Event* e);

		void setLocation(int x, int y);


private:
	int x_location;
	int y_location;
	SDL_Point mLocation;
};


#endif // !MOUSE_BUTTON_H
