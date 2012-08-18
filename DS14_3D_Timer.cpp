#include "DS14_3D_Timer.h"

#include <iostream>

void DS14_3D_Timer::Start()
{
	boStarted = true;
	boPaused = false;

	iStartTicks = SDL_GetTicks();
}

void DS14_3D_Timer::Pause()
{
	iPauseTicks = SDL_GetTicks();

	boStarted = false;
	boPaused = true;
}

void DS14_3D_Timer::Continue()
{
	boStarted = true;
	boPaused = false;
}

int DS14_3D_Timer::iGetTime()
{
	if ( boStarted )
	{
		std::cout << "ERROR: Timer is running" << std::endl;
		return -1;
	}
	return iPauseTicks - iStartTicks;
}