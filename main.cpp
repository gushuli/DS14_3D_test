#include <SDL/SDL.h>
#include "DS14_3D.h"
#include "g3dRenderSystem.h"
#include <iostream>
int main(int argc, char * argv[])
{
	DS14_3D DS_3D;
	g3dRenderSystem RenderSystem;
	g3dSceneManager SceneManager;
	g3dModel*  Model;
	g3dRenderWindow* RenderWindow;
	g3dSceneNode* m_SceneNode;
	DS_3D.DS14_3D_Init();
	RenderWindow = RenderSystem.CreateRenderWindow("test",1024,768,NULL,false);
	RenderSystem.setSceneManager(&SceneManager);

	g3dLight * light0 = SceneManager.CreateLight("light0");
	light0->setType(g3dLight::LT_POINT);
	light0->setPosition(0,0,10);
	light0->setDiffuseColour(1.0,1.0,1.0);
	light0->setSpecularColour(1.0,1.0,1.0);
	RenderSystem.initRenderSystem();
	g3dModel* model=SceneManager.CreateModel("Face.3ds");
	g3dCamera* cam1=SceneManager.CreateCamera("cam1");
	g3dCamera* cam2=SceneManager.CreateCamera("cam2");
	RenderWindow->addViewport(cam1,0,0,0,0.5,1.0);
	RenderWindow->addViewport(cam2,1,0.5,0,0.5,1.0);
	m_SceneNode=SceneManager.CreateSceneNode("node1");
	SceneManager.getRootNode()->addChild(m_SceneNode);
	m_SceneNode->addModel(model);

	RenderSystem.renderOneFrame();
	SDL_GL_SwapBuffers();
	
	std::cin.get();

	DS_3D.DS14_3D_Quit();
	return 0;
}