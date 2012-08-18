#include "DS14_3D.h"
#include <iostream>
#include <GLTools.h>
void DS14_3D::DS14_3D_Init()
{
	putenv("SDL_VIDEODRIVER=directx");
	DS_Config.ConfigLoadIn(DS_Message);
	if (SDL_Init(DS_Message.DS_Mode.SDL_Mode) < 0)
	{
		std::cout << "ERROR: " << SDL_GetError() << std::endl;
	}
	if (Mix_Init(DS_Message.DS_Mode.Mix_Mode) < 0)
	{
		std::cout << "ERROR: " << Mix_GetError() << std::endl;
	}
	DS_Graph.OpenWindow(DS_Message);
	if (GLEW_OK != glewInit())
	{
		std::cout << "ERROR" << glGetError() << std::endl;
	}
}

void DS14_3D::DS14_3D_Quit()
{
	Mix_Quit();
	SDL_Quit();
}