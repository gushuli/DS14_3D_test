#pragma once
#include"g3dBasicHeader.h"
#include "g3dLight.h"

/*********************************************
@类名：g3dLightWrapper
@描述：渲染系统直接使用的光源类型，不是面向用户的。
@说明：在这个类中封装了适合openGL函数直接使用的参数，它依托于场景管理器中的g3dLight，
				是针对openGL的一种对光源参数的具体实现。
@修改历史：高继扬 ,2012/8/12,创建
*********************************************/
class g3dLightWrapper
{

public:

	/**	构造函数
		@说明：无
	
		@参数：light：g3dLight*，用于初始化m_pLight
	
		@修改历史：
			高继扬，2012/8/12，创建
	*/
	g3dLightWrapper(g3dLight* light);

	/**析构函数
	*/
	~g3dLightWrapper(void);

	/**	设置m_pLight
		@说明：无
	
		@参数：light：g3dLight*，用于对m_pLight赋值
	
		@修改历史：
			高继扬，2012/8/12，创建
	*/
	void setLight(g3dLight* light);

	/**	得到当前m_pLight
		@说明：无
	
		@参数：无
	
		@修改历史：
			高继扬，2012/8/12，创建
	*/
	g3dLight* getLight(void);

private:
	/**	初始化成员变量
		@说明：在m_pLight存在的情况下，根据m_pLight的具体类型对5个数组进行赋值
	
		@参数：无
	
		@修改历史：
			高继扬，2012/8/12，创建
	*/
	void InitWrapper(void);

private:

	///g3dLight的指针，依托的对象
	g3dLight* m_pLight;

public:
	//以下的成员变量全部设为共有，因为这是面向渲染系统。

	///名称
	std::string m_Name; 

	///在opengl中分配的光源ID
	unsigned int LightID;//GLenum=unsigned int
	///是否处于活动状态
	bool isActive;

	///光源类型
	g3dLight::LightTypes m_LightType;

	///环境光
	float m_LightAmbient[4];
	///散射光
	float m_LightDiffuse[4];
	///镜面光
	float m_LightSpecular[4];
	///位置
	float m_LightPosition[4];
	///方向
	float m_LightDirection[4];
};

