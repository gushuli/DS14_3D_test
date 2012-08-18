#pragma once
#include "g3dMesh.h"


/*
class g3dObject
{
public:

	g3dObject(t3DObject *pobject);
	~g3dObject(void);
	bool HasTexture;			// 是否具有纹理映射
	string m_Name;			// 对象的名称
	vector<CVector3>  m_VertexSet;			// 对象的顶点集合
	vector<CVector3>  m_NormalSet;		// 对象的各个顶点的法向量
	vector<CVector2>  m_TexVertSet;		// 各顶点纹理UV坐标
	vector<tFace> m_FaceSet;				// 对象的面集合
};

class g3dMaterial
{
public:
	g3dMaterial(tMaterialInfo* pmaterial,unsigned int texture);
	~g3dMaterial(void);
public:
	string m_Name;//名称
	unsigned char m_RGB[3];//材质颜色
	GLuint m_Texture;//表面纹理的id（在opengl状态机中的）
};
*/

/*********************************************
@类名：g3dModel
@描述：模型类
@说明：目前比较简单，未来会加上骨骼动画部分
@修改历史：高继扬 2012/8/16，创建
*********************************************/
class g3dModel
{
public:
	g3dModel(g3dMesh* mesh);
	~g3dModel(void);

	/**渲染模型
	@说明：无
	
	@参数：无
	
	@修改历史：
		高继扬，2012/8/16
	*/
	void RenderModel();

	/**得到bounding box的外接球球心
	@说明：无
	
	@参数：无
	
	@修改历史：
		高继扬，2012/8/16
	*/
	Vector3 getSphereCenter(void) const;

	/**得到bounding box的外接球半径
	@说明：无
	
	@参数：无
	
	@修改历史：
		高继扬，2012/8/16
	*/
	float getSphereRadius(void) const;

	/**得到bounding box的坐标最大值顶点
	@说明：无
	
	@参数：无
	
	@修改历史：
		高继扬，2012/8/16
	*/
	Vector3 getBoundingBoxMax(void) const;

	/**得到bounding box的坐标最小值顶点
	@说明：无
	
	@参数：无
	
	@修改历史：
		高继扬，2012/8/16
	*/
	Vector3 getBoundingBoxMin(void) const;

public:
	///名称
	std::string m_Name;
	///是否有父节点
	bool HasParent;

private:
	///网格结构的指针
	g3dMesh* m_Mesh;

};


