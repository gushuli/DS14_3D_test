#pragma once
#include "g3dBasicHeader.h"
#include "g3dSceneManager.h"
#include"g3dLightWrapper.h"
#include"g3dRenderWindow.h"
#include "gl/GL.h"
#include "gl/GLU.h"

/*********************************************
@类名：g3dRenderSystem
@描述：基于opengl的渲染系统
@说明：渲染系统的基本设计思想是：渲染系统与场景管理器相互独立。
			  将渲染部分做成一种可插接的模式，便于日后的维护和扩展。
			  解释一下“扩展”，目前是靠opengl来进行具体的渲染工作，那么
			  当需要移植，只需要将这部分换掉就可以了，比如opengl es，Dx
			  等。
@修改历史：高继扬，2012/8/14，创建
*********************************************/

class g3dRenderSystem
{
public:

	/**默认构造函数

	@说明：一般不使用
	
	@参数：无
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	g3dRenderSystem(void);

	/**析构函数
	
	@说明：对包含的所有LightWrapper及renderWindow进行析构
								
	@参数：无
	
	@修改历史：高继扬， 2012/8/14，创建
	*/
	~g3dRenderSystem(void);

	/**设置m_pSceneManager
	
	@说明：目的在于渲染
	
	@参数：scenemanager:g3dSceneManager*
	
	@修改历史：高继扬 2012/8/14，创建
	*/
	void setSceneManager(g3dSceneManager* scenemanager);

	/**得到当前m_pSceneManager
	
	@说明：无
	
	@参数：无
	
	@修改历史：高继扬 2012/8/14，创建
	*/
	g3dSceneManager* getSceneManager(void);

	/**初始化渲染系统
	
	@说明：负责两个工作：1.初始化LightWrapper
				   2.初始化openGL环境
	
	@参数：无
	
	@修改历史：高继扬 2012/8/14，创建
	*/
	void initRenderSystem(void);

	/**对当前场景渲染一帧
	
	@说明：渲染系统的核心函数，也是供用户在paintEvent这类事件
					处理函数中的调用的函数。
	
	@参数：无
	
	@修改历史：高继扬, 2012/8/14，创建
	*/
	void renderOneFrame(void);

	/**创建RenderWindow
	
	@说明：不要使用g3dRenderWindow的构造函数进行创建，
					因为这涉及到window的初始化工作
	
	@参数：name：std::string 窗口名称

	@参数：width：unsigned int, 渲染窗口的宽

	@参数：height：unsigned int, 渲染窗口的长

	@参数：hwnd：HWND ，渲染窗口的窗口句柄

	@参数：helptoinitGLwindow：bool, 这个布尔值代表着用户是否希望渲染系统帮助初始化
					渲染窗口的openGL环境，即是否调用initGLWindow()，因为一个窗口在默认情况
					下不支持openGL命令。这个变量的值是true还是false要取决于你的GUI编程框架是否
					已经为你做了这个工作，如果在QT中使用QGLWidget（推荐）则是false，如果是MFC
					中的view则true。
					非常关键！
	
	@修改历史：高继扬, 2012/8/14，创建
	*/
	g3dRenderWindow* CreateRenderWindow(std::string name,unsigned int width,unsigned int height,HWND hwnd, bool helptoinitGLwindow);


private:

	/**对照相机的投影部分进行渲染
	
	@说明：无
	
	@参数：cam：g3dCamera*，指定用于渲染的照相机
	
	@修改历史：高继扬, 2012/8/14，创建
	*/
	void renderCameraProj(g3dCamera* cam);

	/**对照相机的视图-模型部分进行渲染
	
	@说明：无
	
	@参数：cam：g3dCamera*，指定用于渲染的照相机
	
	@修改历史：高继扬, 2012/8/14，创建
	*/
	void renderCameraView(g3dCamera* cam);

	/**渲染场景中的所有实体
	
	@说明：渲染过程中较为关键的一环，会对场景中的所有model渲染
					在以后会逐渐加上天空盒，地面，穹顶等
	
	@参数：无
	
	@修改历史：高继扬, 2012/8/14，创建
	*/
	void renderScene(void);

	/**加载Viewport
	
	@说明：无
	
	@参数：viewport：g3dViewport* 指定视口
	
	@修改历史：高继扬, 2012/8/14，创建
	*/
	void loadViewport(g3dViewport* viewport);
	
	/**光照使能
	
	@说明：无
	
	@参数：light：g3dLightWrapper*
	
	@修改历史：高继扬, 2012/8/14，创建
	*/
	void enableLight(g3dLightWrapper* light);

	/**初始化openGL环境
	
	@说明：要与g3dRenderWindow::initGLWindow()区分
					initGLWindow()是使渲染窗口能够执行openGL命令
					initGL是初始化openGL环境
	
	@参数：无
	
	@修改历史：高继扬, 2012/8/14，创建
	*/
	void initGL();

private:

	///光源个数计数器，LightCount
	unsigned int LC;

	///场景管理器指针
	g3dSceneManager* m_pSceneManager;
	///光源参数集合
	std::map<std::string, g3dLightWrapper*> m_LightWrpMap;
	///渲染窗口指针
	g3dRenderWindow* m_RenderWindow;
	
};

