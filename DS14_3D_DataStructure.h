#ifndef DS14_3D_DataStruct_H
#define DS14_3D_DataStruct_H
#include <SDL/SDL.h>
#include <string>
struct ScreenData
{
	int iScreenWidth;
	int iScreenHeight;
	int iScreenDepth;
	std::string strWindowName;
};

struct DS14_3D_Mode
{
	unsigned int SDL_Mode;
	unsigned int Mix_Mode;
	unsigned int SDL_WindowMode;
};
struct DS14_3D_Message
{
	ScreenData DS_Screen;
	SDL_Event DS_Event;
	DS14_3D_Mode DS_Mode;
	SDL_Surface *MainWindow;
};
#endif