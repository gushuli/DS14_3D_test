#pragma once

#include "g3dBasicHeader.h"
#include "g3dModel.h"
#include <string>
#include <map>

/*********************************************
@类名：g3dSceneNode
@描述：场景节点
@说明：一个场景节点有一个父节点和一组子节点以及一组挂接模型
				节点是模型依附的对象，是操作空间变换的基本单位。
@修改历史：高继扬，2012/8/12，创建
*********************************************/
class g3dSceneNode
{
public:

	///变换空间枚举
	enum TransformSpace
        {
            /// Transform is relative to the local space
            TS_LOCAL,
            /// Transform is relative to the space of the parent node
            TS_PARENT,
            /// Transform is relative to world space
            TS_WORLD
        };

	/**默认构造函数
	@说明：
		与带参数的构造函数相比，区别在于默认构造函数的名称是利用IDcount按照默认格式生成的
	
	@参数：无
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	g3dSceneNode(void);

	/**构造函数
	@说明：
		与默认构造函数相比，区别在于默认构造函数的名称是利用IDcount按照默认格式生成的
	
	@参数：name：std::string 
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	g3dSceneNode(std::string name);

	/**析构函数
	@说明：无
		
	@参数：无
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	~g3dSceneNode(void);

private:
	///计数器
	static int IDcount;
	///模型映射
	std::map<string,g3dModel*> m_ModelMap;
	///子节点映射
	std::map<string,g3dSceneNode*> m_ChildNodeMap;
	///父节点指针
	g3dSceneNode* m_ParentNode;//if its value is NULL, it means it has no parent and it is the root node(only one). 
	///父空间中的方向
	Quaternion m_Orientation;
	///世界空间方向
	Quaternion m_DerivedOrientation;
	///父空间中的位置
	Vector3 m_Position;
	///世界空间中的位置
	Vector3 m_DerivedPosition;
	///父空间中的缩放因子
	Vector3 m_Scale;
	///世界空间缩放因子
	Vector3 m_DerivedScale;

	///需要更新位置？
	bool m_SelfNeedUpdate;

public:
	string m_Name;
	
public:
	/**设置节点方向
	@说明：
		相对于父空间		

	@参数：
		w:float, x:flaot, y:float, z:float

	@修改历史：
		高继扬，2012/8/12，创建
	*/
	void setOrientation( float w, float x, float y, float z);

	/**设置节点方向
	@说明：
		相对于父空间		

	@参数：
		q:Quaternion,  用一个四元数表示方向

	@修改历史：
		高继扬，2012/8/12，创建
	*/
	void setOrientation(Quaternion q);

	/**取得节点方向
	@说明：
		相对于父空间		
	@参数：
		x:flaot, y:float, z:float	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	const Quaternion &getOrientation(void) const;

	/**设置节点位置
	@说明：
		相对于父空间	

	@参数：
		x:flaot, y:float, z:float	

	@修改历史：
		高继扬，2012/8/12，创建
	*/
	void setPosition( float x, float y, float z);

	/**设置节点位置
	@说明：
		相对于父空间	

	@参数：q:Vector3

	@修改历史：
		高继扬，2012/8/12，创建
	*/
	void setPosition(Vector3 q);

	/**得到节点的当前坐标
	@说明：
		相对于父空间

	@参数：无

	@修改历史：
		高继扬，2012/8/12，创建
	*/
	const Vector3 &getPosition(void) const;

	/**设置节点的缩放因子
	@说明：
		相对于父空间	

	@参数：
		x:flaot, y:float, z:float

	@修改历史：
		高继扬，2012/8/12，创建
	*/
	void setScale( float x, float y, float z);

	/**设置节点的缩放因子
		@说明：
			相对于父空间	

		@参数：
			q：Vector3

		@修改历史：
			高继扬，2012/8/12，创建
	*/
	void setScale(Vector3 q);

	/**取得当前缩放因子
	@说明：
		相对于父空间

	@参数：无

	@修改历史：
		高继扬，2012/8/12，创建
	*/
	const Vector3 &getScale(void) const;

	/**得到当前节点在世界空间中的方向
	@说明：
		通过计算所有的父节点得到

	@参数：无	

	@修改历史：
		高继扬，2012/8/12，创建
	*/
    const Quaternion & _getDerivedOrientation(void) ;

	/**得到当前节点在世界空间中的位置
	@说明：
		通过计算所有的父节点得到

	@参数：无

	@修改历史：
		高继扬，2012/8/12，创建
	*/
    const Vector3 & _getDerivedPosition(void) ;

	/**得到当前节点在世界空间中的缩放因子
	@说明：
		通过计算所有的父节点得到
		
	@参数：无
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	 const Vector3 & _getDerivedScale(void) ;

	 /**平移节点函数
	@说明：
		平移变换基于变换空间，默认是父空间
		
	@参数：
		d:Vector3&, 平移向量
	@参数：
		relativeTo：TransformSpace，选择变换空间，可选父空间（默认），本地空间和世界空间
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	void translate(const Vector3& d, TransformSpace relativeTo=TS_PARENT);

	/**平移节点
	@说明：
		平移变换基于变换空间，默认是父空间
		
	@参数：
		x:flaot, y:float, z:float，平移向量
	@参数：
		relativeTo：TransformSpace，选择变换空间，可选父空间（默认），本地空间和世界空间
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	void translate(float x, float y, float z, TransformSpace relativeTo=TS_PARENT);

	/**旋转节点
	@说明：
		在给定坐标空间中绕着一个给定旋转轴，旋转给定角度
		
	@参数：
		axis：Vector3&，旋转轴
	@参数：
		angle：Radian&，旋转角度
	@参数：
		relativeTo：TransformSpace，选择变换空间，可选父空间，本地空间（默认）和世界空间

	@修改历史：
		高继扬，2012/8/12，创建
	*/
	void rotate(const Vector3& axis, const Radian& angle, TransformSpace relativeTo=TS_LOCAL);

	/**旋转节点
	@说明：
		在给定坐标空间中绕着一个给定旋转轴，旋转给定角度
		
	@参数：
		q：Quaternion&，旋转用的四元数
	@参数：
		relativeTo：TransformSpace，选择变换空间，可选父空间，本地空间（默认）和世界空间

	@修改历史：
		高继扬，2012/8/12，创建
	*/
	void rotate(const Quaternion& q, TransformSpace relativeTo=TS_LOCAL);

	/**绕z轴旋转（横滚）
	@说明：无
		
	@参数：
		angle：Radian&，旋转角度
	@参数：
		relativeTo：TransformSpace，选择变换空间，可选父空间，本地空间（默认）和世界空间

	@修改历史：
		高继扬，2012/8/12，创建
	*/
	void roll(const Radian& angle, TransformSpace relativeTo=TS_LOCAL);

	/**绕x轴旋转（俯仰）
	@说明：无
		
	@参数：
		angle：Radian&，旋转角度
	@参数：
		relativeTo：TransformSpace，选择变换空间，可选父空间，本地空间（默认）和世界空间

	@修改历史：
		高继扬，2012/8/12，创建
	*/
	void pitch(const Radian& angle, TransformSpace relativeTo=TS_LOCAL);

	/**绕y轴旋转（航偏）
	@说明：无
		
	@参数：
		angle：Radian&，旋转角度
	@参数：
		relativeTo：TransformSpace，选择变换空间，可选父空间，本地空间（默认）和世界空间

	@修改历史：
		高继扬，2012/8/12，创建
	*/
	void yaw(const Radian& angle, TransformSpace relativeTo=TS_LOCAL);


	/**从父节点更新位置，方向和缩放因子
	@说明：
		底层函数，不建议直接调用
		
	@参数：无
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	void _updateFromParent(void) ;

	/**标志自己需要进行位置，方向或缩放因子的更新
	@说明：无
		
	@参数：b：bool
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	void setSelfNeedUpdate(bool b);

	/**通知子节点进行位置更新
	@说明：遍历，通知
		
	@参数：无
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	void NotifyChildrenUpdate(void);

	/**添加模型
	@说明：无
		
	@参数：model：g3dModel*
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	bool addModel(g3dModel* model);

	/**移除模型
	@说明：
		根据模型指针
		
	@参数：model：g3dModel*
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	bool removeModel(g3dModel* model);

	/**移除模型
	@说明：
		根据模型名称
		
	@参数：name：string
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	bool removeModel(string name);

	/**取得模型指针
	@说明：无
		
	@参数：
		index：unsigned short
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	g3dModel* getModel(unsigned short index);

	/**取得挂接模型总数
	@说明：无
		
	@参数：无
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	unsigned short getModelsNum(void);

	/**添加子节点
	@说明：无
		
	@参数：child：g3dSceneNode*
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	bool addChild( g3dSceneNode* child);

	/**移除子节点
	@说明：无
		
	@参数：name：string
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	bool removeChild(string name);

	/**移除子节点
	@说明：无
		
	@参数：child：g3dSceneNode*
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	bool removeChild(g3dSceneNode* child);

	/**取得子节点指针
	@说明：根据index
		
	@参数：index：unsigned short
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	g3dSceneNode* getChild(unsigned short index);

	/**得到子节点总数
	@说明：无
		
	@参数：无
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	unsigned short getChildrenNum(void);

	/**设置父节点
	@说明：无
		
	@参数：
		parent：g3dSceneNode *
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	void setParent(g3dSceneNode *parent);

	/**得到父节点指针
	@说明：无
		
	@参数：无
	
	@修改历史：
		高继扬，2012/8/12，创建
	*/
	 g3dSceneNode* getParent(void) const;
//private:
	
};

