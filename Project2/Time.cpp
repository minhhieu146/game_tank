#include"Time.h"

TimeObject::TimeObject()
{
	start_tick_ = 0;
	paused_tick_ = 0;
	is_paused_ = false;
	is_started_ = false;

}

TimeObject::~TimeObject()
{

}

void TimeObject::start()
{
	is_started_ = true;
	is_paused_ = false;
	start_tick_ = SDL_GetTicks();
}

void TimeObject::stop()
{
	is_paused_ = false;
	is_started_ = false;
}

void TimeObject::paused()
{
	if (is_started_ == true && is_paused_ == false)
	{
		is_paused_ = true;
		paused_tick_ = SDL_GetTicks() - start_tick_;
	}
}

void TimeObject::unpaused()
{
	if (is_paused_ == true)
	{
		is_paused_ == false;
		start_tick_ = SDL_GetTicks() - paused_tick_;
		paused_tick_ = 0;
	}
}

int TimeObject::get_ticks()
{
	if (is_started_ == true)
	{
		if (is_paused_ == true)
		{
			return paused_tick_;
		}
		else
		{
			return SDL_GetTicks() - start_tick_;
		}
	}
	return 0;
}

bool TimeObject::is_started()
{
	return is_started_;
}

bool TimeObject::is_paused()
{
	return is_paused_;
}