#include "DS14_3D_Graph.h"

#include <iostream>

void DS14_3D_Graph::OpenWindow(DS14_3D_Message& DS_Message)
{
	DS_Message.MainWindow = SDL_SetVideoMode(DS_Message.DS_Screen.iScreenWidth,
								  DS_Message.DS_Screen.iScreenHeight,
								  DS_Message.DS_Screen.iScreenDepth,
								  DS_Message.DS_Mode.SDL_WindowMode);
	if (DS_Message.MainWindow == NULL)
	{
		std::cout << "ERROR: " << SDL_GetError() << std::endl;
		return ;
	}

	SDL_WM_SetCaption(DS_Message.DS_Screen.strWindowName.c_str(),NULL);
}

void DS14_3D_Graph::SetupRC(DS14_3D_Message& DS_Message)
{

}

void DS14_3D_Graph::RenderSence(DS14_3D_Message& DS_Message)
{

}