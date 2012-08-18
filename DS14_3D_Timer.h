#ifndef DS14_3D_TIMER_H
#define DS14_3D_TIMER_H

#include <SDL/SDL.h>

class DS14_3D_Timer
{
public:
	DS14_3D_Timer(){}
	~DS14_3D_Timer(){}

	void Start();
	void Pause();
	void Continue();
	int iGetTime();

	int iStartTicks;
	int iPauseTicks;

	bool boStarted;
	bool boPaused;

protected:
private:
};

#endif

