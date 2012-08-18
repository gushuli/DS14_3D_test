#include "DS14_3D_Input.h"
#include <iostream>

void DS14_3D_Input::GetEvent(DS14_3D_Message& DS_Message)
{
	SDL_PollEvent(&DS_Message.DS_Event);
}

void DS14_3D_Input::DealEvent(DS14_3D_Message& DS_Message)
{

}