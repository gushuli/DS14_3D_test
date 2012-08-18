#ifndef DS14_3D_H
#define DS14_3D_H


#include "DS14_3D_Audio.h"
#include "DS14_3D_Config.h"
#include "DS14_3D_DataStructure.h"
#include "DS14_3D_Graph.h"
#include "DS14_3D_Input.h"
#include "DS14_3D_Timer.h"

class DS14_3D
{
public:
	DS14_3D(){}
	~DS14_3D(){}

	void DS14_3D_Init();
	void DS14_3D_Quit();



	DS14_3D_Audio DS_Audio;
	DS14_3D_Config DS_Config;
	DS14_3D_Input DS_Input;
	DS14_3D_Timer DS_Timer;
	DS14_3D_Graph DS_Graph;

	DS14_3D_Message DS_Message;



protected:
private:
};


#endif
