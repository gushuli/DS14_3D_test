#include <SDL/SDL.h>
#include "DS14_3D.h"

int main(int argc, char * argv[])
{
	DS14_3D DS_3D;
	DS_3D.DS14_3D_Init();
	SDL_Delay(10000);
	DS_3D.DS14_3D_Quit();
	return 0;
}