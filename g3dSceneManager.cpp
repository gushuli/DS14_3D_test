#include "g3dSceneManager.h"


///载入纹理错误标志位（临时）
#define G3D_ERROR_TEXTURE 9999  


//------------------------------------------------------------------------------------------------
g3dSceneManager::g3dSceneManager(void)
	:m_Ambient(0.2,0.2,0.2,1.0)
{
	m_pRootNode=new g3dSceneNode("RootNode");	
	m_SceneNodeMap[(m_pRootNode->m_Name)]=m_pRootNode;
}
//------------------------------------------------------------------------------------------------
g3dSceneManager::~g3dSceneManager(void)
{

	//析构m_SceneNodeMap中所有的节点，包括m_pRootNode
	for(map<string,g3dSceneNode*>::iterator it=m_SceneNodeMap.begin();it!=m_SceneNodeMap.end();it++)
	{
		//判断非空
		if(it->second!=NULL)
			delete it->second;
	}

	//析构m_LightMap中所有灯光
	for(map<string,g3dLight*>::iterator it=m_LightMap.begin();it!=m_LightMap.end();it++)
	{
		if(it->second!=NULL)
			delete it->second;
	}

	//析构MeshMap中所有的Mesh
	for(map<string,g3dMesh*>::iterator it=m_MeshMap.begin();it!=m_MeshMap.end();it++)
	{
		if(it->second!=NULL)
			delete it->second;
	}

	//析构m_CameraMap中所有Camera
	for(std::map<std::string,g3dCamera*>::iterator it=m_CameraMap.begin();it!=m_CameraMap.end();it++)
	{
		if(it->second!=NULL)
		{
			delete it->second;
		}
	}
}
//------------------------------------------------------------------------------------------------
g3dModel* g3dSceneManager::CreateModel(std::string filename)
{
	g3dMesh* Mesh=CreateMesh(filename);
	g3dModel* Model=new g3dModel(Mesh);
	return Model;
}
//------------------------------------------------------------------------------------------------
void g3dSceneManager::setAmbientColor(float r,float g,float b)
{
	m_Ambient.r=r;
	m_Ambient.g=g;
	m_Ambient.b=b;
	m_Ambient.a=1.0f;
}
//------------------------------------------------------------------------------------------------
ColorValue g3dSceneManager::getAmbientColor(void) const
{
	return m_Ambient;
}
//------------------------------------------------------------------------------------------------
g3dSceneNode* g3dSceneManager::getRootNode(void)
{
	return m_pRootNode;
}
//------------------------------------------------------------------------------------------------
g3dSceneNode* g3dSceneManager::CreateSceneNode(std::string name)
{
	g3dSceneNode* newNode=new g3dSceneNode(name);
	if(newNode!=NULL)
		m_SceneNodeMap[newNode->m_Name]=newNode;
	return newNode;
}
//------------------------------------------------------------------------------------------------
g3dLight* g3dSceneManager::CreateLight(std::string name)
{
	if(m_LightMap.size()<8)
	{
		g3dLight* newLight=new g3dLight(name);
		if(newLight!=NULL)
			m_LightMap[newLight->m_Name]=newLight;
		return newLight;
	}
	else
		return NULL;
	
}

//------------------------------------------------------------------------------------------------
g3dMesh* g3dSceneManager::CreateMesh(std::string filename)
{
	//建立一个t3DModel的临时对象，
	//便于读取3DS格式文件。
	t3DModel temp;
	m_Load3ds.Import3DS(&temp, filename.c_str());	
	// 遍历所有的材质,生成纹理
	for(int i = 0; i < temp.numOfMaterials; i++)
	{
		// 判断是否是一个文件名
		if(strlen(temp.pMaterials[i].strFile) > 0)
		{
			//  使用纹理文件名称来装入位图
			unsigned int textureID=CreateTexture( temp.pMaterials[i].strFile);
			if(textureID!=G3D_ERROR_TEXTURE)
			{
				// 设置材质的纹理ID
				temp.pMaterials[i].texureId = textureID;
			}
			else
			{
				temp.pMaterials[i].texureId =-1;
			}

		}	
		else
		{
			temp.pMaterials[i].texureId =-1;
		}
		
	}
	//新建Mesh
	g3dMesh *mesh=new g3dMesh();
	mesh->m_Name=filename;
	for(int i=0;i<temp.numOfObjects;i++)
	{
		int materialID=temp.pObject[i].materialID;
		//新建SubMesh
		g3dSubMesh* newSubMesh=
			new g3dSubMesh(&temp.pObject[i],&temp.pMaterials[materialID],(GLuint)temp.pMaterials[materialID].texureId);
		//判断textureID是否合法、有效
		if (temp.pMaterials[materialID].texureId==-1)
		{
			//将SubMesh设置为无纹理
			newSubMesh->setHasTextrue(false);
		} 
		else
		{
			//将SubMesh设置为有纹理
			newSubMesh->setHasTextrue(true);
		}

		//将SubMesh加入到Mesh中
		mesh->addSubMesh(newSubMesh);
	}
	//初始化Bounding Box信息
	mesh->initBoundingBox();
	m_MeshMap[mesh->m_Name]=mesh;
	
	return mesh;
	
}

//------------------------------------------------------------------------------------------------
g3dCamera* g3dSceneManager::CreateCamera(std::string name)
{
	g3dCamera* cam=new g3dCamera(name);
	if(cam!=NULL)
		m_CameraMap[cam->m_Name]=cam;
	return cam;
}

//------------------------------------------------------------------------------------------------
unsigned int  g3dSceneManager::CreateTexture(LPSTR strFileName)
{
	AUX_RGBImageRec *pBitmap = NULL;

	unsigned int textureID;

	if(!strFileName)
	{
		// 如果无此文件，则返回G3D_ERROR_TEXTURE(G3D_ERROR_TEXTURE表示错误）
		return G3D_ERROR_TEXTURE;
	}
	// 装入位图，并保存数据
	pBitmap = auxDIBImageLoadA(strFileName);				
	// 如果装入位图失败，则退出
	if(pBitmap == NULL)									
		exit(0);

	// 生成纹理
	glGenTextures(1, &textureID);
	// 设置像素对齐格式
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	glBindTexture(GL_TEXTURE_2D, textureID);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pBitmap->sizeX, pBitmap->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pBitmap->data);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

	// 释放位图占用的资源
	if (pBitmap)										
	{
		if (pBitmap->data)						
		{
			free(pBitmap->data);				
		}

		free(pBitmap);					
	}
	return textureID;
}
//------------------------------------------------------------------------------------------------

