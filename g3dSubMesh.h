#pragma once
#include"g3dBasicHeader.h"
#include "3DS.H"

/*********************************************
@类名：g3dObject
@描述：网格的最基本结构
@说明：存储顶点集合，面集合，顶点索引集合，顶点法线集合，UV纹理坐标集合
@修改历史：高继扬，2012/8/10，创建
*********************************************/
class g3dObject
{
public:

	/**构造函数	
	@说明：
		接受一个t3DObject的指针将其中数据转换到g3dObject
	
	@参数：
		pobject：t3DObject*
	
	@修改历史：
		高继扬，2012/8/10
	*/
	g3dObject(t3DObject *pobject);

	/**析构函数
	*/
	~g3dObject(void);


	/// 是否具有纹理映射
	bool HasTexture;		

	/// 对象的名称
	string m_Name;		

	/// 对象的顶点集合
	vector<CVector3>  m_VertexSet;	
	/// 对象的各个顶点的法向量
	vector<CVector3>  m_NormalSet;		
	/// 各顶点纹理UV坐标
	vector<CVector2>  m_TexVertSet;		
	/// 对象的面集合
	vector<tFace> m_FaceSet;	

	//以下数据分别记录着所有顶点中的各坐标分量的最大最小值。
	float m_MinX;
	float m_MinY;
	float m_MinZ;
	float m_MaxX;
	float m_MaxY;
	float m_MaxZ;
};


/*********************************************
@类名：g3dMaterial
@描述：材质
@说明：被使用在submesh中，作为材质
@修改历史：高继扬, 2012/8/10，创建
*********************************************/
class g3dMaterial
{

public:
	/**构造函数
	@说明：无
	
	@参数：
		pmaterial：tMaterialInfo*，这代表着材质的数据源
	@参数：
		texture：unsigned int ，材质表面纹理的ID
	
	@修改历史：高继扬
	*/
	g3dMaterial(tMaterialInfo* pmaterial,unsigned int texture);

	/**析构函数
	*/
	~g3dMaterial(void);

public:
	///名称
	string m_Name;

	//材质颜色
	unsigned char m_RGB[3];
	//表面纹理的id（在opengl状态机中的）
	GLuint m_Texture;
};


/*********************************************
@类名：g3dSubMesh
@描述：子网格（最小独立单元）
@说明：g3dSubMesh集合了一个material和一个object，object记录顶点数据，
			  material记录材质数据。g3dSubMesh是组成g3dMesh的基本单元
@修改历史：高继扬，2012/8/10
*********************************************/
class g3dSubMesh
{
public:
	/**默认构造函数
	*/
	g3dSubMesh(void);
	/**析构函数
	*/
	~g3dSubMesh(void);

	/**构造函数
	@说明：
		传入三个变量，分别代表顶点，材质和纹理
	@参数：
		object：t3DObject*，material：tMaterialInfo*，texture：GLuint
	@修改历史：
		高继扬 ，2012/8/10，创建
	*/
	g3dSubMesh(t3DObject* object,tMaterialInfo* material,GLuint texture);

	/**渲染子网格
	@说明：无
		
	@参数：无
	
	@修改历史：
		高继扬， 2012/8/10, 创建
	*/
	void RenderSubMesh();

	/**设置纹理标志位
	@说明：
		通过调用此函数，可以开启或者关闭纹理。但是如果网格本身不自带纹理，
		开启纹理也无效（甚至引发错误）。
	@参数：
		b：bool
	@修改历史：
		高继扬 ，2012/8/10，创建
	*/
	void setHasTextrue(bool b);

private:
	/**生成显示列表
	@说明：
		为已有顶点数据和材质生成一个显示列表，目的是加速渲染
	
	@参数：无
	
	@修改历史：
		高继扬，2012/8/10，创建
	*/
	bool GenDisplayList();

private:

	///材质
	g3dMaterial *m_pMaterial;
	///顶点数据
	g3dObject *m_pObject;
	///显示列表（用于渲染子网格）
	GLuint m_DisplayList;

public:
	///名称
	string m_Name;


public:
	//友元类
	friend class g3dMesh;

};

