#include "g3dViewport.h"


//---------------------------------------------------------------------
g3dViewport::g3dViewport(void)
{
}

//---------------------------------------------------------------------
g3dViewport::~g3dViewport(void)
{
}

//---------------------------------------------------------------------
g3dViewport::g3dViewport(g3dCamera* cam, g3dRenderWindow* target, float left, float top, float width, float height, int ZOrder)
	: m_LinkedCamera(cam)
	, m_Window(target)
	, m_RelLeft(left)
	, m_RelTop(top)
	, m_RelWidth(width)
	, m_RelHeight(height)
	// Actual dimensions will update later
	, m_ZOrder(ZOrder)
	, m_BackColor(ColorValue::Black)
	,m_NeedUpdate(true)
{
	_updateDimensions();
}

//---------------------------------------------------------------------
int g3dViewport::getZOrder(void) const
{
	return m_ZOrder;
}

//---------------------------------------------------------------------
g3dRenderWindow* g3dViewport::getWindow(void) const
{
	return m_Window;
}

//---------------------------------------------------------------------
g3dCamera* g3dViewport::getCamera(void) const
{
	return m_LinkedCamera;
}

//---------------------------------------------------------------------
float g3dViewport::getLeft(void) const
{
	return m_RelLeft;
}

//---------------------------------------------------------------------
float g3dViewport::getTop(void) const
{
	return m_RelTop;
}

//---------------------------------------------------------------------
float g3dViewport::getWidth(void) const
{
	return m_RelWidth;
}

//---------------------------------------------------------------------
float g3dViewport::getHeight(void) const
{
	return m_RelHeight;
}

//---------------------------------------------------------------------
int g3dViewport::getActualLeft(void) const
{
	return m_ActLeft;
}

//---------------------------------------------------------------------
int g3dViewport::getActualTop(void) const
{
	return m_ActTop;
}

//---------------------------------------------------------------------
int g3dViewport::getActualWidth(void) const
{
	return m_ActWidth;
}

//---------------------------------------------------------------------
int g3dViewport::getActualHeight(void) const
{
	return m_ActHeight;
}

//---------------------------------------------------------------------
void g3dViewport::setDimensions(float left, float top, float width, float height)
{
	m_RelLeft = left;
	m_RelTop = top;
	m_RelWidth = width;
	m_RelHeight = height;
	_updateDimensions();
}

//---------------------------------------------------------------------
void g3dViewport::setBackColor(ColorValue color)
{
	m_BackColor=color;
}

//---------------------------------------------------------------------
ColorValue g3dViewport::getBackColor(void) const
{
	return m_BackColor;
}

//---------------------------------------------------------------------
void g3dViewport::_updateDimensions(void)
{
	//取得当前渲染窗口的实际大小
		float height = (float) m_Window->getHeight();
		float width = (float) m_Window->getWidth();

	//刷新
	m_ActLeft = (int) (m_RelLeft * width);
	m_ActTop = (int) (m_RelTop * height);
	m_ActWidth = (int) (m_RelWidth * width);
	m_ActHeight = (int) (m_RelHeight * height);

	//如果有一个相连的camera则对camera的
	//aspect进行自动更新的判断执行
	if(m_LinkedCamera)
	{
		if(m_LinkedCamera->getAutoAspect()==true)
			m_LinkedCamera->setAspect((float)m_ActWidth/(float)m_ActHeight);
	}

	m_NeedUpdate=false;
}

//---------------------------------------------------------------------
void g3dViewport::setNeedUpdate(bool b)
{
	m_NeedUpdate=b;
}

//---------------------------------------------------------------------
void g3dViewport::updateDimensions()
{
	if (m_NeedUpdate)
		_updateDimensions();
}
