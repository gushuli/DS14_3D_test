#pragma once

#include "g3dCamera.h"
#include "g3dRenderWindow.h"
#include "g3dBasicHeader.h"

class g3dRenderWindow;

/*********************************************
@类名：g3dViewport
@描述：视口
@说明：视口是连接照相机和窗口的桥梁，可以说它是计算机中的虚拟世界和
				看到的图像之间的桥梁。每个照相机只能连接一个视口，每个视口也
				只能连接一个照相机，而一个渲染窗口可以拥有多个视口，这样实现
				了多视口渲染。
@修改历史：高继扬 2012/8/15，创建
*********************************************/
class g3dViewport
{
public:

	/** 构造函数（常用）
		@说明：无

        @参数:
            camera :g3dCamera* , 这个照相机的指针会作为视口的图像来源
        @参数：
			target：g3dRenderWindow* 渲染目标（这里是一个渲染窗口）
         @参数：
			left：float
        @参数：
            top：float
        @参数
            width：float
        @参数
            height：float
            视口的尺寸用四个浮点数描述，它们都是在【0,1】之间的。这样做的
			好处是设置比例，而非具体大小。当窗口大小放生变化时，可根据这些
			变量自动调整。
        @参数
            ZOrder 可以理解为视口到窗口的距离，数字越小，里窗口越远，
			会被具有更大的ZOrder的窗口覆盖。

		@修改历史：
			高继扬，2012/8/15，创建
    */
    g3dViewport(
        g3dCamera* camera,
       g3dRenderWindow* target,
        float left, float top,
        float width, float height,
        int ZOrder);

	/**默认构造函数
	@说明：无
	
	@参数：无
	
	@修改历史：
		高继扬，2012/8/15，创建
	*/
	g3dViewport(void);

	/**析构函数
	@说明：无
	
	@参数：无
	
	@修改历史：
		高继扬，2012/8/15，创建
	*/
	~g3dViewport(void);

	/** Get the camera to use for rendering to this viewport. */
	g3dCamera* getCamera(void) const;

	/**Get the render Window*/
	g3dRenderWindow* getWindow(void) const;

    /** Sets the camera to use for rendering to this viewport. */
    void setCamera(g3dCamera* cam);

    /** Gets the Z-Order of this viewport. */
	int getZOrder(void) const;
	/** Gets one of the relative dimensions of the viewport,
        a value between 0.0 and 1.0.
    */
    float getLeft(void) const;

    /** Gets one of the relative dimensions of the viewport, a value
        between 0.0 and 1.0.
    */
    float getTop(void) const;

    /** Gets one of the relative dimensions of the viewport, a value
        between 0.0 and 1.0.
    */

    float getWidth(void) const;
    /** Gets one of the relative dimensions of the viewport, a value
        between 0.0 and 1.0.
    */

    float getHeight(void) const;
    /** Gets one of the actual dimensions of the viewport, a value in
        pixels.
    */

    int getActualLeft(void) const;
    /** Gets one of the actual dimensions of the viewport, a value in
        pixels.
    */

    int getActualTop(void) const;
    /** Gets one of the actual dimensions of the viewport, a value in
        pixels.
    */
    int getActualWidth(void) const;
    /** Gets one of the actual dimensions of the viewport, a value in
        pixels.
    */

    int getActualHeight(void) const;

    /** 设置尺寸（创建后）
		@说明：
			视口的尺寸用四个浮点数描述，它们都是在【0,1】之间的。这样做的
			好处是设置比例，而非具体大小。当窗口大小放生变化时，可根据这些
			变量自动调整。

		@参数：
			left：float
		@参数：
			top：float
		@参数
			width：float
		@参数
			height：float
		
		@修改历史：
			高继扬，2012/8/15，创建
    */
    void setDimensions(float left, float top, float width, float height);

	/**Get the m_Backcolor(background color)
	*/
	ColorValue getBackColor(void) const;

	/**Set the m_Backcolor(background color)
	*/
	void setBackColor(ColorValue color);

	/**更新视口的实际尺寸
	@说明：
		底层函数，不建议直接调用，建议使用updateDimensions（);
	
	@参数：无
	
	@修改历史：
		高继扬，2012/8/10，创建
	*/
	void _updateDimensions();

	/**设置标志需要更新的布尔值*/
	void setNeedUpdate(bool b);

	/**更新视口的实际尺寸
	@说明：
		建议使用;
	
	@参数：无
	
	@修改历史：
		高继扬，2012/8/10，创建
	*/
	void updateDimensions();
	

private:
	///渲染窗口
	g3dRenderWindow* m_Window;
	///照相机
	g3dCamera* m_LinkedCamera;
	// 相对尺寸，与渲染对象实际大小无关 (0..1)
	float m_RelLeft, m_RelTop, m_RelWidth, m_RelHeight;
	// 实际尺寸，基于渲染对象
	int m_ActLeft, m_ActTop, m_ActWidth, m_ActHeight;
	/// ZOrder
	int m_ZOrder;
	/// Background options
	ColorValue m_BackColor;
	///标志是否需要对视口的实际大小进行更新
	bool m_NeedUpdate;

};

