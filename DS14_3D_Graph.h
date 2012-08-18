#ifndef DS14_3D_GRAPH_H
#define DS14_3D_GRAPH_H

#include <SDL/SDL.h>
#include "DS14_3D_DataStructure.h"
class DS14_3D_Graph
{
public:
	DS14_3D_Graph(){}
	~DS14_3D_Graph(){}

	void OpenWindow(DS14_3D_Message& DS_Message);
	void SetupRC(DS14_3D_Message& DS_Message);
	void RenderSence(DS14_3D_Message& DS_Message);


	
protected:
private:
};


#endif