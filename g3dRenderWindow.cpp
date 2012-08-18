#include "g3dRenderWindow.h"

//------------------------------------------------------------------------------------------------
g3dRenderWindow::g3dRenderWindow(unsigned int width,unsigned int height,HWND hwnd,bool helptoInitGLwindow)
	:m_Width(width)
	,m_Height(height)
	,hWnd(hwnd)
	,m_HelpToInitGLWindow(helptoInitGLwindow)
{
}

//------------------------------------------------------------------------------------------------
g3dRenderWindow::~g3dRenderWindow(void)
{
	removeAllViewports();

	//如果是引擎辅助初始化的窗口则引擎负责销毁上下文
	if(m_HelpToInitGLWindow)
		destroyWindow();

}

//------------------------------------------------------------------------------------------------
bool g3dRenderWindow::initGLWindow(void)
{
	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		32,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		destroyWindow();								// Reset The Display
		MessageBox(NULL,TEXT("Can't Create A GL Device Context."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}
	int indexPixelFormat=0;
	if (!(indexPixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		destroyWindow();								// Reset The Display
		MessageBox(NULL,TEXT("Can't Find A Suitable PixelFormat."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,indexPixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		destroyWindow();								// Reset The Display
		MessageBox(NULL,TEXT("Can't Set The PixelFormat."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		destroyWindow();								// Reset The Display
		MessageBox(NULL,TEXT("Can't Create A GL Rendering Context."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		destroyWindow();								// Reset The Display
		MessageBox(NULL,TEXT("Can't Activate The GL Rendering Context."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}
	return true;
}

//------------------------------------------------------------------------------------------------
void g3dRenderWindow::destroyWindow(void)
{
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,TEXT("Release Of DC And RC Failed."),TEXT("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,TEXT("Release Rendering Context Failed."),TEXT("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}
	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,TEXT("Release Device Context Failed."),TEXT("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}
}

//------------------------------------------------------------------------------------------------
void g3dRenderWindow::swapBuffer(void)
{
	if(hDC)
		SwapBuffers(hDC);
	else
	{
		MessageBox(NULL,TEXT("Release Device Context Failed."),TEXT("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
	}
}

//------------------------------------------------------------------------------------------------
unsigned int g3dRenderWindow::getHeight(void)
{
	return m_Height;
}

//------------------------------------------------------------------------------------------------
unsigned int g3dRenderWindow::getWidth(void)
{
	return m_Width;
}

//------------------------------------------------------------------------------------------------
g3dViewport* g3dRenderWindow::addViewport(g3dCamera* cam, int ZOrder , float left , float top ,float width, float height)
{
	// Check no existing viewport with this Z-order
	std::map<int,g3dViewport*>::iterator it=m_ViewportList.find(ZOrder);
	if(it!=m_ViewportList.end())//exist
	{
		return NULL;
	}
	g3dViewport* viewport=new g3dViewport(cam,this,left,top,width,height,ZOrder);
	m_ViewportList[ZOrder]=viewport;
	return viewport;
}

//------------------------------------------------------------------------------------------------
void g3dRenderWindow::removeViewport(int ZOrder)
{
	std::map<int,g3dViewport*>::iterator it = m_ViewportList.find(ZOrder);

	if (it != m_ViewportList.end())
	{
		delete (*it).second;
		m_ViewportList.erase(ZOrder);
	}
}

//------------------------------------------------------------------------------------------------
void g3dRenderWindow::removeAllViewports(void)
{

	for (map<int,g3dViewport*>::iterator it = m_ViewportList.begin(); it != m_ViewportList.end(); ++it)
	{
		delete (*it).second;
	}
	m_ViewportList.clear();

}

//------------------------------------------------------------------------------------------------
unsigned int g3dRenderWindow::getNumViewports(void) const
{
	return m_ViewportList.size();
}

//-----------------------------------------------------------------------
g3dViewport* g3dRenderWindow::getViewport(int index)
{
	assert (index < m_ViewportList.size() && "Index out of bounds");

	std::map<int,g3dViewport*>::iterator i = m_ViewportList.begin();
	while (index--)
		++i;
	return i->second;
}

//-----------------------------------------------------------------------
g3dViewport* g3dRenderWindow::getViewportByZOrder(int ZOrder)
{
	std::map<int,g3dViewport*>::iterator i = m_ViewportList.find(ZOrder);
	//检查
	if(i == m_ViewportList.end())
	{
		return NULL;
	}
	return i->second;
}

//------------------------------------------------------------------------------------------------
void g3dRenderWindow::windowResized(void)
{
	RECT windowrect;

	//根据窗口句柄取得窗口矩形
	if(hWnd)
		GetWindowRect(hWnd,&windowrect);

	m_Width=abs(windowrect.right-windowrect.left);
	m_Height=abs(windowrect.bottom-windowrect.top);

	//遍历所有的viewport，通知更新，使其在下一次渲染时自动更新大小
	for(std::map<int,g3dViewport*>::iterator it=m_ViewportList.begin();it!=m_ViewportList.end();it++)
	{
		if(it->second)
			it->second->setNeedUpdate(true);
	}

}