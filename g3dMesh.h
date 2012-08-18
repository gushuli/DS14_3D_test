#pragma once
#include "g3dBasicHeader.h"
#include "g3dSubMesh.h"

/*********************************************
类名：g3dMesh

描述：模型（g3dModel）的 完整的 网格 数据结构

说明：一个完整的模型可能由多个独立的子模型组成，每个
			子模型都应当对应一个网格结构。
			所以一个完整的网格结构应当包含一组g3dSubMesh
			的指针，以便于管理和扩展。
*********************************************/

class g3dMesh
{
public:

	/**默认构造函数
	@说明：无
	
	@参数：无

	@修改历史：
		高继扬，2012/8/16,创建
	*/
	g3dMesh(void);


	/**析构函数
	@说明：在析构函数中，会对m_SubMeshList中存放的所有
			       g3dSubMesh 进行析构，防止内存泄露。
	
	@参数：无

	@修改历史：
		高继扬，2012/8/16,创建
	*/
	~g3dMesh(void);


	/**	对Mesh中含有的所有SubMesh进行渲染 
	@说明：一个Mesh包括若干SubMesh，存储在一个vector中。
					对这个Mesh的渲染就变成了对其所有SubMesh渲染的遍历。

	@参数：无

	@修改历史：
			高继扬，2012/8/16,创建
	*/
	void RenderMesh(void);


	/**对当前g3dMesh添加一个g3dSubMesh
	@说明：无
	
	@参数：submesh是一个g3dSubMesh的指针，
					指向要添加的g3dSubMesh	
	*/
	void addSubMesh(g3dSubMesh* submesh);

	/**初始化网格的bounding box的四个参数
	@说明：无
	
	@参数：无

	@修改历史：
		高继扬，2012/8/16,创建
	*/
	void initBoundingBox();

	Vector3 getSphereCenter(void) const;

	float getSphereRadius(void) const;

	Vector3 getBoundingBoxMax(void) const;

	Vector3 getBoundingBoxMin(void) const;

private:

	///存储所有的g3dSubMesh指针。
	vector<g3dSubMesh*> m_SubMeshList;

	///网格的bounding box的8个点中的x,y,z坐标最小的点
	Vector3 m_MinPoint;
	///网格的bounding box的8个点中的x,y,z坐标最大的点
	Vector3 m_MaxPoint;
	///bounding box的外接球球心
	Vector3 m_Center;
	///外接球半径
	float m_Radius;


public:
	///mesh的名字
	std::string m_Name;

};

