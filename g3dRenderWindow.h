#pragma once
#include "windows.h"
#include  "tchar.h"
#include "Windows.h"
#include "g3dBasicHeader.h"
#include "g3dViewport.h"
#include "g3dCamera.h"

class g3dViewport;

/*********************************************
@类名：g3dRenderWindow
@描述：渲染窗口类

@说明：1.  渲染窗口是一种渲染对象（render target），渲染对象一般有两种：
			   一种是窗口，另一种是纹理。目前引擎仅支持渲染到窗口，不支持渲
			   染到纹理。
			   2.  渲染窗口是一个Win32窗口，Win32窗口有两种作图模式:
			   一种是利用GDI,比如在MFC、QT等中常用的画线，画圆，贴图等，
			   另一种是通过openGL函数对窗口渲染。这两种方式不能同时使用，
			   也就是说 ,是否需要调用辅助初始化openGL的窗口环境的函数（initGLWindow()）
			   需要根据提供的窗口本身的情况来决定，如果编程框架已经提供
			   了openGL的窗口环境（QGLWidget）则不需要，如果没有（CView）
			   则需要。这也就是m_HelpToInitGLWindow存在的意义，系统根据
			   这个变量来决定是否初始化opengl环境。
			   关于HWND,HDC,HGLRC的更多信息可以参看msdn的相关说明。
			   4.  一个渲染窗口可以拥有多个视口，每个视口挂接一个照相机。渲染窗口
			   根据拥有的视口来分次渲染以实现多视口渲染的效果。

@修改历史：
				高继扬，2012/8/14，创建
*********************************************/
class g3dRenderWindow
{

public:

	/**	构造函数
		@说明：无
	
		@参数：width：unsigned int，窗口的宽
		@参数：height：unsigned int，窗口的高
		@参数：hwnd：HWND，窗口句柄
		@参数：helptoInitGLwindow：bool
	
		@修改历史：
				高继扬 ,  2012/8/14，创建
	*/
	g3dRenderWindow(unsigned int width,unsigned int height,HWND hwnd,bool helptoInitGLwindow);

	/**	析构函数
		@说明：无
	
		@参数：无
	
		@修改历史：
				高继扬 ,  2012/8/14，创建
	*/
	~g3dRenderWindow(void);

	/**	辅助初始化窗口opengl环境
		@说明：
				渲染窗口是一个Win32窗口，Win32窗口有两种作图模式:
			   一种是利用GDI,比如在MFC、QT等中常用的画线，画圆，贴图等，
			   另一种是通过openGL函数对窗口渲染。这两种方式不能同时使用，
			   也就是说 ,是否需要调用辅助初始化openGL的窗口环境的函数（initGLWindow()）
			   需要根据提供的窗口本身的情况来决定，如果编程框架已经提供
			   了openGL的窗口环境（QGLWidget）则不需要，如果没有（CView）
			   则需要。这也就是m_HelpToInitGLWindow存在的意义，系统根据
			   这个变量来决定是否处置初始化opengl环境。
			   关于HWND,HDC,HGLRC的更多信息可以参看msdn的相关说明。

		@参数：无

		@修改历史：
				高继扬 ,  2012/8/14，创建
	*/
	bool initGLWindow(void);

	/**	销毁窗口
		@说明：
			销毁窗口只是将窗口的设备上下文和openGL的渲染上下文释放，并不是删除
				
		@参数：无
	
		@修改历史：
				高继扬 ,  2012/8/14，创建
	*/
	void destroyWindow(void);

	/**	交换缓冲区
		@说明：无
	
		@参数：无
	
		@修改历史：
				高继扬 ,  2012/8/14，创建
	*/
	void swapBuffer(void);

	/**	得到窗口的宽
		@说明：无
	
		@参数：无
	
		@修改历史：
				高继扬 ,  2012/8/14，创建
	*/
	unsigned int getWidth(void);

	/**	得到窗口的高
		@说明：无
	
		@参数：无
	
		@修改历史：
				高继扬 ,  2012/8/14，创建
	*/
	unsigned int getHeight(void);

	/** Adds a viewport to the rendering target.
        @remarks
            A viewport is the rectangle into which rendering output is sent. This method adds
            a viewport to the render target, rendering from the supplied camera. The
            rest of the parameters are only required if you wish to add more than one viewport
            to a single rendering target. Note that size information passed to this method is
            passed as a parametric, i.e. it is relative rather than absolute. This is to allow
            viewports to automatically resize along with the target.

        @param
            cam The camera from which the viewport contents will be rendered (mandatory)
        @param
            ZOrder The relative order of the viewport with others on the target (allows overlapping
            viewports i.e. picture-in-picture). Higher ZOrders are on top of lower ones. The actual number
            is irrelevant, only the relative ZOrder matters (you can leave gaps in the numbering)
        @param
            left The relative position of the left of the viewport on the target, as a value between 0 and 1.
        @param
            top The relative position of the top of the viewport on the target, as a value between 0 and 1.
        @param
            width The relative width of the viewport on the target, as a value between 0 and 1.
        @param
            height The relative height of the viewport on the target, as a value between 0 and 1.

		@ history of previous changes ：
				高继扬，2012/8/14, Create
    */
	g3dViewport* addViewport(g3dCamera* cam, int ZOrder = 0, float left = 0.0f, float top = 0.0f ,
		float width = 1.0f, float height = 1.0f);

    /** Returns the number of viewports attached to this target.*/
        unsigned int getNumViewports(void) const;

    /** Retrieves a pointer to the viewport with the given index. */
        g3dViewport* getViewport(int index);

	/** Retrieves a pointer to the viewport with the given Zorder. 
		@remarks throws if not found.
	*/
        g3dViewport* getViewportByZOrder(int ZOrder);

    /** Removes a viewport at a given ZOrder.
    */
    void removeViewport(int ZOrder);

    /** Removes all viewports on this target.
    */
    void removeAllViewports(void);

	/**	窗口大小改变
		@说明：在resizeEvent的事件处理函数中使用
	
		@参数：无
	
		@修改历史：
				高继扬 ,  2012/8/14，创建
	*/
	void windowResized(void);


private:

	/// Private GDI Device Context
	HDC			hDC;	
	/// Permanent Rendering Context
	HGLRC		hRC;		
	/// Holds Our Window Handle
	HWND		hWnd;		

	///窗口的宽
	unsigned int m_Width;
	///窗口的高
	unsigned int m_Height;

	/// List of viewports, map on Z-order
	///（存在bug，目前仅仅支持多视口渲染，但并没有根据zOrder来调整渲染顺序，有待改进）
	std::map<int, g3dViewport*> m_ViewportList;

	/// 是否需要辅助初始化openGL窗口环境
	bool m_HelpToInitGLWindow;
	
};

