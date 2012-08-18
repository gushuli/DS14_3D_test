#include "g3dSubMesh.h"


g3dSubMesh::g3dSubMesh(t3DObject* object,tMaterialInfo* material,GLuint texture)
{
	m_pMaterial=new g3dMaterial(material,texture);
	m_pObject=new g3dObject(object);
	//默认采用object的name
	m_Name=m_pObject->m_Name;
	GenDisplayList();
}

void g3dSubMesh::setHasTextrue(bool b)
{
	m_pObject->HasTexture=b;
}

bool g3dSubMesh::GenDisplayList()
{
	//生成显示列表
	m_DisplayList=glGenLists(1);
	if(m_DisplayList!=0)
	{
		glNewList(m_DisplayList,GL_COMPILE);

		glBegin(GL_TRIANGLES);	
		for(int j=0;j<this->m_pObject->m_FaceSet.size();j++)
		{
			for(int whichVertex=0;whichVertex<3;whichVertex++)
			{
				// 获得面对每个点的索引
				int index=m_pObject->m_FaceSet[j].vertIndex[whichVertex];
				// 给出法向量
				glNormal3f(m_pObject->m_NormalSet[ index ].x, m_pObject->m_NormalSet[ index ].y,m_pObject->m_NormalSet[ index ].z);
				// 如果对象具有纹理
				if(m_pObject->HasTexture)
				{
					// 确定是否有UVW纹理坐标
					if(m_pObject->m_TexVertSet.size()>0)
					{
						glTexCoord2f(m_pObject->m_TexVertSet[index].x, m_pObject->m_TexVertSet[index].y);
					}
				}
				else
				{
					glColor3ub(m_pMaterial->m_RGB[0], m_pMaterial->m_RGB[1], m_pMaterial->m_RGB[2]);
				}
				glVertex3f(m_pObject->m_VertexSet[ index ].x, m_pObject->m_VertexSet[ index ].y,m_pObject->m_VertexSet[ index ].z);
			}
		}
		glEnd();

		glEndList();

		return true;
	}
	else
		return false;
}

void g3dSubMesh::RenderSubMesh()
{
	if(this->m_pObject->HasTexture)
	{
		// 打开纹理映射
		glEnable(GL_TEXTURE_2D);
		glColor3ub(255, 255, 255);
		glBindTexture(GL_TEXTURE_2D,this->m_pMaterial->m_Texture);
	}
	else
	{
		// 关闭纹理映射
		glDisable(GL_TEXTURE_2D);
		glColor3ub(255, 255, 255);
	}
	//调用显示列表
	glCallList(m_DisplayList);

}





g3dObject::g3dObject(t3DObject* pobject)
{
	if(pobject!=NULL)
	{
		HasTexture=pobject->bHasTexture;
		m_Name=string(pobject->strName);
		//为m_Min系列附一个初值，以便循环时比较
		m_MinZ=pobject->pVerts[0].z;
		m_MinX=pobject->pVerts[0].x;
		m_MinY=pobject->pVerts[0].y;
		//将m_Max系列初始化为m_Min系列
		m_MaxX=m_MinX;
		m_MaxY=m_MinY;
		m_MaxZ=m_MinZ;
		//初始化顶点信息
		for(int i=0;i<pobject->numOfVerts;i++)
		{
			//比较最大值
			if (pobject->pVerts[i].x>m_MaxX)
				m_MaxX=pobject->pVerts[i].x;
			if (pobject->pVerts[i].y>m_MaxY)
				m_MaxY=pobject->pVerts[i].y;
			if(pobject->pVerts[i].z>m_MaxZ)
				m_MaxZ=pobject->pVerts[i].z;
			//比较最小值
			if (pobject->pVerts[i].x<m_MinX)
				m_MinX=pobject->pVerts[i].x;
			if (pobject->pVerts[i].y<m_MinY)
				m_MinY=pobject->pVerts[i].y;
			if(pobject->pVerts[i].z<m_MinZ)
				m_MinZ=pobject->pVerts[i].z;
			//赋值
			m_VertexSet.push_back(pobject->pVerts[i]);
			m_NormalSet.push_back(pobject->pNormals[i]);
		}		
		//初始化纹理坐标信息
		for(int i=0;i<pobject->numTexVertex;i++)
			m_TexVertSet.push_back(pobject->pTexVerts[i]);
		//初始化面信息
		for(int i=0;i<pobject->numOfFaces;i++)
		{
			m_FaceSet.push_back(pobject->pFaces[i]);
		}		
	}
	else
	{
		HasTexture=false;
	}
}
g3dObject::~g3dObject(void)
{

}


g3dMaterial::g3dMaterial(tMaterialInfo* pmaterial,GLuint texture)
{
	if(pmaterial!=NULL)
	{
		m_RGB[0]=pmaterial->color[0];
		m_RGB[1]=pmaterial->color[1];
		m_RGB[2]=pmaterial->color[2];
		m_Name=string(pmaterial->strName);
		m_Texture=texture;
	}
}

g3dSubMesh::~g3dSubMesh(void)
{
}
