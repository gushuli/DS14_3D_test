#pragma once
#include "g3dBasicHeader.h"
#include "g3dSceneNode.h"

/************************************************************************
关于FOV和Aspect：

	Aspect ratio (y:x) = y / x = (tan (vertical FOV / 2) ) / (tan (horizontal FOV / 2) )

	horizontal FOV = 2 * arc tan ( tan (vertical FOV / 2) * (x / y) )

	vertical FOV = 2 * arc tan ( tan (horizontal FOV / 2) * (y / x) )
************************************************************************/

///投影模式枚举类型
enum ProjectionType
{
	PT_ORTHOGRAPHIC,
	PT_PERSPECTIVE
};

/*********************************************
@类名：g3dCamera
@描述：照相机
@说明：照相机类主要负责管理两类信息
			   1.  与投影相关的：平截头体，长方体和投影模式
			   2. 与视图变换相关的：up向量，position（位置，观察点）和lookat
@修改历史：高继扬，2012/8/14，创建
*********************************************/
class g3dCamera
{
public:
	/**默认构造函数
	@说明：与带参数的构造函数的区别在于，默认构造函数利用IDcount生成，
				   默认名称，其他无区别，具体初始化信息参见函数实现
	
	@参数：无

	@修改历史：高继扬，2012/8/14，创建
	*/
	g3dCamera(void);

	/**构造函数
	@说明：与默认构造函数的区别在于，默认构造函数利用IDcount生成，
	默认名称，其他无区别，具体初始化信息参见函数实现
	
	@参数：name：string类型，代表名称

	@修改历史：高继扬，2012/8/14，创建
	*/
	g3dCamera(std::string name);

	/**析构函数
	@说明：无
	
	@参数：无
	
	@修改历史：高继扬 ，2012/8/14，创建
	*/
	~g3dCamera(void);

	/**设置Projection（投影）模式
	@说明：渲染器根据投影模式选择正交投影或透视投影
	
	@参数：type：ProjectionType
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	void setProjectionType(ProjectionType type);

	/**得到当前投影模式
	@说明：无
	
	@参数：无
	
	@修改历史：高继扬 ，2012/8/14，创建
	*/
	ProjectionType getProjectionType(void) const;

	/**设置垂直FOV（field of view）
	@说明：关于FOV的描述参见类的说明和m_FOV的说明
	
	@参数：fovy：Radian
	
	@修改历史：高继扬 ，2012/8/14，创建
	*/
	void setFOVy(Radian fovy);

	/**设置垂直FOV（field of view）
	@说明：关于FOV的描述参见类的说明和m_FOV的说明
	
	@参数：fovy：Degree
	
	@修改历史：高继扬 ，2012/8/14，创建
	*/
	void setFOVy(Degree fovy);

	/**得到垂直FOV（field of view），垂直视角
	@说明：关于平截头体的描述参见类的说明和各个成员对象的说明
	
	@参数：无
	
	@修改历史：高继扬 ，2012/8/14，创建
	*/
	Radian getFOVy(void)const;

	/**设置平截头体中较远面与观察点的距离
	@说明：关于平截头体的描述参见类的说明和各个成员对象的说明
	
	@参数：far：float
	
	@修改历史：高继扬 ，2012/8/14，创建
	*/
	void setFarDist(float far);

	/**设置平截头体中较近面与观察点的距离
	@说明：关于平截头体的描述参见类的说明和各个成员对象的说明
	
	@参数：far：near
	
	@修改历史：高继扬 ，2012/8/14，创建
	*/
	void setNearDist(float near);

	/**得到平截头体中较远面与观察点的距离
	@说明：关于平截头体的描述参见类的说明和各个成员对象的说明
	
	@参数：无
	
	@修改历史：高继扬 ，2012/8/14，创建
	*/
	float getFarDist(void)const;

	/**得到平截头体中较近面与观察点的距离
	@说明：关于平截头体的描述参见类的说明和各个成员对象的说明
	
	@参数：无
	
	@修改历史：高继扬 ，2012/8/14，创建
	*/
	float getNearDist(void)const;

	/**设置平截头体中的宽长比
	@说明：关于平截头体的描述参见类的说明和各个成员对象的说明
	
	@参数：aspect：float
	
	@修改历史：高继扬 ，2012/8/14，创建
	*/
	void setAspect(float aspect);

	/**得到平截头体中的宽长比
	@说明：关于平截头体的描述参见类的说明和各个成员对象的说明
	
	@参数：aspect：float
	
	@修改历史：高继扬 ，2012/8/14，创建
	*/
	float getAspect(void)const;

	/**设置平截头体（用于透视投影）或长方体（用于正交投影）中的左坐标
	@说明：关于平截头体的描述参见类的说明和各个成员对象的说明。
				   关于左坐标，可以看glOrtho()的参数说明和glFrustum()的参数说明
	
	@参数：left：float
	
	@修改历史：高继扬 ，2012/8/14，创建
	*/
	
	void setLeft(float left);

	/**设置平截头体（用于透视投影）或长方体（用于正交投影）中的右坐标
	@说明：关于平截头体的描述参见类的说明和各个成员对象的说明。
				   关于左坐标，可以看glOrtho()的参数说明和glFrustum()的参数说明
	
	@参数：right：float
	
	@修改历史：高继扬 ，2012/8/14，创建
	*/
	void setRight(float right);

	/**设置平截头体的底
	
	@说明：无
	
	@参数：bottom：float
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	void setBottom(float bottom);
	
	/**设置平截头体的顶
	
	@说明：无
	
	@参数：top：float
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	void setTop(float top);
	
	/**得到当前平截头体（用于透视投影）或长方体（用于正交投影）中的左坐标
	
	@说明：无
	
	@参数：无
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	float getLeft(void)const;
	
	/**得到当前平截头体（用于透视投影）或长方体（用于正交投影）中的右坐标
	
	@说明：无
	
	@参数：无
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	float getRight(void)const;
	
	/**得到当前平截头体（用于透视投影）或长方体（用于正交投影）中的顶坐标
	
	@说明：无
	
	@参数：无
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	float getTop(void)const;
	
	/**得到当前平截头体（用于透视投影）或长方体（用于正交投影）中的底坐标
	
	@说明：无
	
	@参数：无
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	float getBottom(void) const;
	
	/**设置照相机位置
	
	@说明：无
	
	@参数：pos：Vector3
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	void setPosition(Vector3 pos);

	/**设置照相机位置
	
	@说明：无
	
	@参数：x:float, y:float ,z:float 
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	void setPosition(float x,float y,float z);
	
	/**设置照相机的向上方向的向量
	
	@说明：无
	
	@参数：up：Vector3
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	void setUp(Vector3 up);
	
	/**设置照相机的向上方向的向量
	
	@说明：无
	
	@参数：x:float, y:float ,z:float 
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	void setUp(float x,float y,float z);
	
	/**设置照相机的视线方向
	
	@说明：无
	
	@参数：lookat:Vector3
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	void lookat(Vector3 lookat);
	
	/**设置照相机的视线方向
	
	@说明：无
	
	@参数：x:float, y:float ,z:float 
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	void lookat(float x,float y,float z);
	
	/**取得当前照相机位置
	
	@说明：无
	
	@参数：无
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	Vector3 getPosition(void) const;
	
	/**取得当前照相机向上方向向量
	
	@说明：无
	
	@参数：无
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	Vector3 getUp(void) const;
	
	/**取得当前照相机视线方向
	
	@说明：无
	
	@参数：无
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	Vector3 getLookat(void) const;
	
	/**取得标志投影变化的布尔值
	
	@说明：无
	
	@参数：无
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	bool getProjectChanged(void);
	
	/**取得标志视图变化的布尔值
	
	@说明：无
	
	@参数：无
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	bool getLookatChanged(void);
	
	/**设置标志投影变化的布尔值
	
	@说明：无
	
	@参数：b:bool
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	void setProjectChanged(bool b);
	
	/**设置标志视图变化的布尔值
	
	@说明：无
	
	@参数：b：bool
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	void setLookatChanged(bool b);
	
	/**取得标志自动更新宽长比的布尔值
	
	@说明：无
	
	@参数：无
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	bool getAutoAspect(void);
	
	/**设置标志自动更新宽长比的布尔值
	
	@说明：无
	
	@参数：b：bool
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	void setAutoAspect(bool b);

	/**根据给定model智能地设定照相机参数，使得其在屏幕中大小适中

	@说明：每个model都有一组参数来描述它的BoundingBox，此函数就
					根据这些参数来调整自己的position、up和lookat，具体算法
					参见函数实现
	
	@参数：model：g3dModel*
	
	@修改历史：高继扬，2012/8/14，创建
	*/
	void IntelLookat(g3dModel* model);

public:
	///照相机名称
	std::string m_Name;

private:

	///ID计数器
	static int IDconst;
	
	bool m_ProjectChanged;
	bool m_LookatChanged;
	bool m_AutoAspect;
	
	///default PT_PERSPECTIVE
	ProjectionType m_ProjectionType;
	//default PI/4
	Radian m_FOVy;
	/// Far clip distance - default 10000f
	float m_FarDist;
	/// Near clip distance - default 0.5f
	float m_NearDist;
	/// x/y viewport ratio - default 1.3333
	float m_Aspect; 
	/// Frustum extents(especially for PT_ORTHOGRAPHIC)
	float m_Left, m_Right, m_Top, m_Bottom;

	///位置（观察点）
	Vector3 m_Position;
	///lookat
	Vector3 m_LookAt;
	///照相机向上矢量的方向
	Vector3 m_Up;
};

