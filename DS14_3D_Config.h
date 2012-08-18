#ifndef DS14_3D_CONFIG_H
#define DS14_3D_CONFIG_H

#include <SDL/SDL.h>
#include <string>
#include "DS14_3D_DataStructure.h"
class DS14_3D_Config
{
public:
	DS14_3D_Config(){}
	~DS14_3D_Config(){}

	void ReplayLoadIn();
	void ConfigLoadIn(DS14_3D_Message& DS_Message);

	std::string strReplayFileName;

protected:
private:
};

#endif