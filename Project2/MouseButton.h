#ifndef MOUSE_BUTTON_H
#define MOUSE_BUTTON_H

#include"SDL_utils.h"
#include"BasicObject.h"
class MouseButton : public BasicObject
{
public:
		MouseButton();
		~MouseButton();

		
		bool HandleEvent(SDL_Event* e);

		void setLocation(int x, int y);


private:

	SDL_Point mLocation;
};


#endif // !MOUSE_BUTTON_H
