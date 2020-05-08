#pragma once
#ifndef MOUSE_BUTTON_H
#define MOUSE_BUTTON_H

#include"BasicObject.h"
class MouseButton : public BasicObject
{
public:
		MouseButton();
		~MouseButton();

		bool HandleEvent(SDL_Event* e);

private:

	SDL_Point mLocation;
};


#endif // !MOUSE_BUTTON_H
