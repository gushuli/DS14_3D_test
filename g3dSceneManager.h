#pragma once
#include "g3dBasicHeader.h"
#include "g3dSceneNode.h"
#include "g3dCamera.h"
#include "g3dLight.h"
#include "g3dMesh.h"
#include "3DS.H"

/*********************************************
@类名：g3dSceneManager
@描述：场景管理器
@说明：1. 总览：场景管理器是引擎中最核心的部分。它负责管理场景中的所有可动和不可动的
				物体，比如模型、照相机，地形、天空盒等。
				2.  模型需要挂接在场景节点下，场景节点组合成一个树形结构，这就是场景管理
				器中的节点树。节点树，通过一个保存在场景管理器中的根节点来遍历。
				3. 注意：一切在存在于场景（scene）中的物体，都需要通过场景管理器中的
				CreateXXX（）来创建。
@修改历史：
			高继扬，2012/8/11，创建
*********************************************/
class g3dSceneManager
{
public:

	/**	默认构造函数
	@说明：用户通过这个函数创建场景管理器
	
	@参数：无
	
	@修改历史：高继扬，2012/8/11，创建
	*/
	g3dSceneManager(void);
	/**	析构函数
	@说明：
		负责析构所有由场景管理器创建的物体
	
	@参数：无
	
	@修改历史：
		高继扬，2012/8/11，创建
	*/
	~g3dSceneManager(void);

	/**	得到根节点
	@说明：
		根节点全局只有一个，用户无法创建、无法删除。用户通过根节点进行子节点挂接。
	
	@参数：无
	
	@修改历史：高继扬，2012/8/11，创建
	*/
	g3dSceneNode* getRootNode(void);

	/**	新建场景节点
		@说明：
			不要通过g3dSceneNode的构造函数来创建节点，因为节点需要在场景管理器
			中登记，本函数是唯一合法函数。
	
		@参数：
			name：std::string
	
		@修改历史：
			高继扬，2012/8/11，创建
	*/
	g3dSceneNode* CreateSceneNode(std::string name);

	/**	新建光源
	@说明：
	不要通过g3dLight的构造函数来创建光源，因为光源需要在场景管理器
	中登记，本函数是唯一合法函数。
	
	@参数：
		name：std::string
	
	@修改历史：
		高继扬，2012/8/11，创建
	*/
	g3dLight* CreateLight(std::string name);

	/**	新建照相机
	@说明：
	不要通过g3dCamera的构造函数来创建照相机，因为照相机需要在场景管理器
	中登记，本函数是唯一合法函数。
	
	@参数：
		name：std::string
	
	@修改历史：
		高继扬，2012/8/11，创建
	*/
	g3dCamera* CreateCamera(std::string name);

	/**	新建网格
	@说明：
		不要通过g3dMesh的构造函数来创建网格，因为网格需要在场景管理器
		中登记，本函数是唯一合法函数。
	
	@参数：
		name：std::string
	
	@修改历史：
		高继扬，2012/8/11，创建
	*/
	g3dMesh* CreateMesh(std::string filename);

	/**	新建模型
	@说明：
		不要通过g3dModel的构造函数来创建模型，因为模型需要在场景管理器
		中登记，本函数是唯一合法函数。
	
	@参数：
		name：std::string
	
	@修改历史：
		高继扬，2012/8/11，创建
	*/
	g3dModel* CreateModel(std::string filename);

	/**	设置全局环境光的颜色
	@说明：
		全局环境光有且只有一个。
	
	@参数：
		r：float，g：float，b：flaot
	
	@修改历史：
		高继扬，2012/8/11，创建
	*/
	void setAmbientColor(float r,float g,float b);

	/**	得到全局环境光的颜色
	@说明：
		全局环境光有且只有一个。
	
	@参数：无
	
	@修改历史：
		高继扬，2012/8/11，创建
	*/
	ColorValue getAmbientColor(void) const;


private:

	/**	创建纹理
	@说明：
		这个函数应处于资源管理器中，由于目前引擎尚不完整，暂时放在这里。
	
	@参数：
		strFileName：LPSTR
	
	@修改历史：
		高继扬，2012/8/11，创建
	*/
	unsigned int CreateTexture(LPSTR strFileName);


public:
	friend class g3dRenderSystem;
	
private:
	///3ds loader
	CLoad3DS m_Load3ds;

	///the map of SceneNode
	///when a SceneNode is created, it stores in this map
	std::map<std::string,g3dSceneNode*> m_SceneNodeMap;
	///光源映射
	std::map<std::string,g3dLight*> m_LightMap;
	///照相机映射
	std::map<std::string,g3dCamera*> m_CameraMap;
	///the root node is a part of SceneManager and users cannot delete it. 
	g3dSceneNode* m_pRootNode;

	///the color of the ambient light,
	///ambient light cannot be created by the function CreateLight(),
	ColorValue m_Ambient;

	///resource manager
	std::map<std::string,g3dMesh*> m_MeshMap;
};

