#include "DS14_3D_Config.h"

#include <iostream>
#include <fstream>
void DS14_3D_Config::ReplayLoadIn()
{
	std::ifstream infile;
	infile.open("ReplayName.txt",std::ios::in);
	if (infile.fail())
	{
		std::cout << "ERROR: ReplayName.txt is missing." << std::endl;
		return ;
	}
	infile >> strReplayFileName;
	infile.close();
	infile.open(strReplayFileName.c_str(),std::ios::in);
	if (infile.fail())
	{
		std::cout << "ERROR: ReplayFile is missing." << std::endl;
		return ;
	}
	infile.close();
}

void DS14_3D_Config::ConfigLoadIn(DS14_3D_Message& DS_Message)
{
	std::ifstream infile;
	infile.open("DS14_3D.cfg",std::ios::in);
	if (infile.fail())
	{
		std::cout << "Configuration File lost." << std::endl;
		return ;
	}
	infile >> DS_Message.DS_Mode.SDL_Mode
			>> DS_Message.DS_Mode.Mix_Mode
			>> DS_Message.DS_Mode.SDL_WindowMode
			>> DS_Message.DS_Screen.iScreenWidth
			>> DS_Message.DS_Screen.iScreenHeight
			>> DS_Message.DS_Screen.iScreenDepth
			>> DS_Message.DS_Screen.strWindowName;
}