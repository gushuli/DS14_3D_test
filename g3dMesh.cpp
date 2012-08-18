#include "g3dMesh.h"

//------------------------------------------------------------------------------------------------
g3dMesh::g3dMesh(void)
{
}
//------------------------------------------------------------------------------------------------

g3dMesh::~g3dMesh(void)
{
	for(int i=0;i<m_SubMeshList.size();i++)
	{
		if(m_SubMeshList[i]!=NULL)
		{
			delete m_SubMeshList[i];
		}
	}
}

//------------------------------------------------------------------------------------------------
void g3dMesh::addSubMesh(g3dSubMesh* submesh)
{
	m_SubMeshList.push_back(submesh);
}

//------------------------------------------------------------------------------------------------
void g3dMesh::RenderMesh()
{
	//遍历，渲染
	for (int i=0;i<m_SubMeshList.size();i++)
	{
		if(m_SubMeshList[i]!=NULL)
			m_SubMeshList[i]->RenderSubMesh();
	}
}

//------------------------------------------------------------------------------------------------
void g3dMesh::initBoundingBox(void)
{
	
	if(m_SubMeshList.size()>0)
	{
		//先给一个初值，以便比较
		float minX=m_SubMeshList[0]->m_pObject->m_MinX;
		float minY=m_SubMeshList[0]->m_pObject->m_MinY;
		float minZ=m_SubMeshList[0]->m_pObject->m_MinZ;
		float maxX=m_SubMeshList[0]->m_pObject->m_MaxX;
		float maxY=m_SubMeshList[0]->m_pObject->m_MaxY;
		float maxZ=m_SubMeshList[0]->m_pObject->m_MaxZ;

		for(int i=0;i<m_SubMeshList.size();i++)
		{
			//检测最大值
			if(maxX<m_SubMeshList[i]->m_pObject->m_MaxX)
			{
				maxX=m_SubMeshList[i]->m_pObject->m_MaxX;
			}
			if (maxY<m_SubMeshList[i]->m_pObject->m_MaxY)
			{
				maxY=m_SubMeshList[i]->m_pObject->m_MaxY;
			}
			if(maxZ<m_SubMeshList[i]->m_pObject->m_MaxZ)
			{
				maxZ=m_SubMeshList[i]->m_pObject->m_MaxZ;
			}

			//检测最小值
			if(minX>m_SubMeshList[i]->m_pObject->m_MinX)
			{
				minX=m_SubMeshList[i]->m_pObject->m_MinX;
			}
			if (minY>m_SubMeshList[i]->m_pObject->m_MinY)
			{
				minY=m_SubMeshList[i]->m_pObject->m_MinY;
			}
			if(minZ>m_SubMeshList[i]->m_pObject->m_MinZ)
			{
				minZ=m_SubMeshList[i]->m_pObject->m_MinZ;
			}

		}

		//遍历结束
		//赋值
		m_MaxPoint.x=maxX;
		m_MaxPoint.y=maxY;
		m_MaxPoint.z=maxZ;
		m_MinPoint.x=minX;
		m_MinPoint.y=minY;
		m_MinPoint.z=minZ;
		//计算外接球半径和球心
		m_Radius=m_MaxPoint.distance(m_MinPoint)/2.0f;
		m_Center=(m_MaxPoint+m_MinPoint)/2.0f;
	}
}

//------------------------------------------------------------------------------------------------
Vector3 g3dMesh::getSphereCenter(void) const
{
	return m_Center;
}

//------------------------------------------------------------------------------------------------
float g3dMesh::getSphereRadius(void ) const
{
	return m_Radius;
}

//------------------------------------------------------------------------------------------------
Vector3 g3dMesh::getBoundingBoxMax(void) const
{
	return m_MaxPoint;
}

//------------------------------------------------------------------------------------------------
Vector3 g3dMesh::getBoundingBoxMin(void) const
{
	return m_MinPoint;
}
//------------------------------------------------------------------------------------------------