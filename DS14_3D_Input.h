#ifndef DS14_3D_INPUT_H
#define DS14_3D_INPUT_H

#include "SDL/SDL.h"
#include "DS14_3D_DataStructure.h"
class DS14_3D_Input
{
public:
	DS14_3D_Input(){}
	~DS14_3D_Input(){}

	void GetEvent(DS14_3D_Message& DS_Message);
	void DealEvent(DS14_3D_Message& DS_Message);
protected:
private:
};

#endif