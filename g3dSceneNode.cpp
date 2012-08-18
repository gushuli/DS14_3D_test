#include "g3dSceneNode.h"

int g3dSceneNode::IDcount=0;
g3dSceneNode::g3dSceneNode(void)
	:
	m_Position(Vector3::ZERO),
	m_Scale(Vector3::UNIT_SCALE),
	m_Orientation(Quaternion::IDENTITY),
	m_DerivedOrientation(Quaternion::IDENTITY),
	m_DerivedPosition(Vector3::ZERO),
	m_DerivedScale(Vector3::UNIT_SCALE),
	m_SelfNeedUpdate(true),
	m_ParentNode(NULL)
{
	m_Name="SceneNode"+IDcount;
	IDcount++;
}

g3dSceneNode::g3dSceneNode(std::string name)
	:
	m_Position(Vector3::ZERO),
	m_Scale(Vector3::UNIT_SCALE),
	m_Orientation(Quaternion::IDENTITY),
	m_DerivedOrientation(Quaternion::IDENTITY),
	m_DerivedPosition(Vector3::ZERO),
	m_DerivedScale(Vector3::UNIT_SCALE),
	m_SelfNeedUpdate(true),
	m_ParentNode(NULL)
{
	m_Name=name;
	IDcount++;
}

//-----------------------------------------------------------------------
g3dSceneNode::~g3dSceneNode(void)
{
}

//-----------------------------------------------------------------------
void g3dSceneNode::setParent(g3dSceneNode* parent)
{
	m_ParentNode=parent;
}
//-----------------------------------------------------------------------
g3dSceneNode* g3dSceneNode::getParent(void) const
{
	return m_ParentNode;
}
//-----------------------------------------------------------------------
bool g3dSceneNode::addModel(g3dModel* model)
{
	if(model->HasParent)
	{
		return false;
	}
	else
	{
		m_ModelMap[model->m_Name]=model;
		model->HasParent=true;
		return true;
	}
}
//-----------------------------------------------------------------------
bool g3dSceneNode::removeModel(g3dModel* model)
{
	for(map<string,g3dModel*>::iterator it=m_ModelMap.begin();it!=m_ModelMap.end();it++)
	{
		if((it)->second==model)
		{
			(it)->second->HasParent=false;
			m_ModelMap.erase(it);			
			return true;
		}
	}
	return false;
}
//-----------------------------------------------------------------------
bool g3dSceneNode::removeModel(string name)
{
	map<string,g3dModel*>::iterator it=m_ModelMap.find(name);
	if(it!=m_ModelMap.end())
	{
		(it)->second->HasParent=false;
		m_ModelMap.erase(it);
		return true;
	}
	else
		return false;
}
//-----------------------------------------------------------------------
g3dModel* g3dSceneNode::getModel(unsigned short index)
{
	assert(index<m_ModelMap.size());
	map<std::string, g3dModel*>::iterator it=m_ModelMap.begin();
	while(index--) it++;
	return it->second;
}
//-----------------------------------------------------------------------
unsigned short g3dSceneNode::getModelsNum(void)
{
	return m_ModelMap.size();
}
//-----------------------------------------------------------------------
bool g3dSceneNode::addChild(g3dSceneNode* child)
{
	if(child->getParent()==NULL)
	{
		child->setParent(this);
		m_ChildNodeMap[child->m_Name]=child;
		return true;
	}
	else
		return false;
}
//-----------------------------------------------------------------------
bool g3dSceneNode::removeChild(g3dSceneNode* child)
{
	for(map<string,g3dSceneNode*>::iterator it=m_ChildNodeMap.begin();it!=m_ChildNodeMap.end();it++)
	{
		if((it)->second==child)
		{
			(it)->second->setParent(NULL);
			m_ChildNodeMap.erase(it);			
			return true;
		}
	}
	return false;
}
//-----------------------------------------------------------------------
bool  g3dSceneNode::removeChild(string name)
{
	map<string,g3dSceneNode*>::iterator it=m_ChildNodeMap.find(name);
	if(it!=m_ChildNodeMap.end())
	{
		(it)->second->setParent(NULL);
		m_ChildNodeMap.erase(it);
		return true;
	}
	else
		return false;
}
//-----------------------------------------------------------------------
g3dSceneNode* g3dSceneNode::getChild(unsigned short index)
{
	assert(index<m_ChildNodeMap.size());
	map<string,g3dSceneNode*>::iterator it=m_ChildNodeMap.begin();
	while(index--) it++;
	return it->second;
}
//-----------------------------------------------------------------------
unsigned short g3dSceneNode::getChildrenNum(void)
{
	return m_ChildNodeMap.size();
}
//-----------------------------------------------------------------------
void g3dSceneNode::setOrientation( float w, float x, float y, float z)
{
	setOrientation(Quaternion(w,x,y,z));
}
//-----------------------------------------------------------------------
void g3dSceneNode::setOrientation(Quaternion q)
{
	m_Orientation=q;
	m_Orientation.normalise();
	setSelfNeedUpdate(true);
	NotifyChildrenUpdate();
}
//-----------------------------------------------------------------------
const Quaternion &g3dSceneNode::getOrientation() const
{
	return m_Orientation;
}
//-----------------------------------------------------------------------
void g3dSceneNode::setPosition( float x, float y, float z)
{
	setPosition(Vector3(x,y,z));
}
//-----------------------------------------------------------------------
void g3dSceneNode::setPosition(Vector3 pos)
{
	m_Position=pos;
	setSelfNeedUpdate(true);
	NotifyChildrenUpdate();
}
//-----------------------------------------------------------------------
const Vector3 &g3dSceneNode::getPosition() const
{
	return m_Position;
}
//-----------------------------------------------------------------------
void g3dSceneNode::setScale(Vector3 inScale)
{
    m_Scale = inScale;
	setSelfNeedUpdate(true);
    NotifyChildrenUpdate();
}
//-----------------------------------------------------------------------
void g3dSceneNode::setScale(float x, float y, float z)
{
	setScale(Vector3(x, y, z));
}
//-----------------------------------------------------------------------
const Vector3 & g3dSceneNode::getScale(void) const
{
    return m_Scale;
}
//-----------------------------------------------------------------------
// Gets the orientation of the node as derived from all parents.
const Quaternion & g3dSceneNode::_getDerivedOrientation(void) 
{
	if(m_SelfNeedUpdate==true)
		_updateFromParent();
	return m_DerivedOrientation;
}
//-----------------------------------------------------------------------
// Gets the position of the node as derived from all parents.
const Vector3 & g3dSceneNode::_getDerivedPosition(void) 
{
	if(m_SelfNeedUpdate==true)
	{
		_updateFromParent();
	}
	return m_DerivedPosition;
}
//-----------------------------------------------------------------------
// Gets the scale of the node as derived from all parents.
const Vector3 & g3dSceneNode::_getDerivedScale(void) 
{
	if(m_SelfNeedUpdate==true)
		_updateFromParent();
	return m_DerivedScale;
}
//-----------------------------------------------------------------------
void g3dSceneNode::setSelfNeedUpdate(bool b)
{
	m_SelfNeedUpdate=b;
}
//-----------------------------------------------------------------------
void g3dSceneNode::NotifyChildrenUpdate()
{
	if(!m_ChildNodeMap.empty())
	{
		for(map<string, g3dSceneNode*>::iterator it=m_ChildNodeMap.begin();it!=m_ChildNodeMap.end();it++)
		{
			it->second->setSelfNeedUpdate(true);
			it->second->NotifyChildrenUpdate();
		}
	}
}
//-----------------------------------------------------------------------
void g3dSceneNode::_updateFromParent(void) 
{
	if(m_ParentNode)//if it has a parent node.
	{
		 const Quaternion parentOrientation = m_ParentNode->_getDerivedOrientation();
		 m_DerivedOrientation=parentOrientation * m_Orientation;

		 const Vector3 parentScale = m_ParentNode->_getDerivedScale();
		 m_DerivedScale=parentScale * m_Scale;

		 const Vector3 parentPosition = m_ParentNode->_getDerivedPosition();
		 m_DerivedPosition= parentOrientation*(parentScale*m_Position);
		 m_DerivedPosition+=parentPosition;		 
	}
	else
	{
		m_DerivedOrientation=m_Orientation;
		m_DerivedPosition=m_Position;
		m_DerivedScale=m_Scale;
	}

	m_SelfNeedUpdate=false;
}
//-----------------------------------------------------------------------
void g3dSceneNode::translate(const Vector3& d, TransformSpace relativeTo)
{
    switch(relativeTo)
    {
    case TS_LOCAL:
        // position is relative to parent so transform downwards
        m_Position += m_Orientation * d;
        break;
    case TS_WORLD:
        // position is relative to parent so transform upwards
        if (m_ParentNode)
        {
            m_Position += (m_ParentNode->_getDerivedOrientation().Inverse() * d)
                / m_ParentNode->_getDerivedScale();
        }
        else
        {
            m_Position += d;
        }
        break;
    case TS_PARENT:
        m_Position += d;
        break;
    }
	setSelfNeedUpdate(true);
    NotifyChildrenUpdate();

}
//-----------------------------------------------------------------------
void g3dSceneNode::translate(float x, float y, float z, TransformSpace relativeTo)
{
    Vector3 v(x,y,z);
    translate(v, relativeTo);
}

//-----------------------------------------------------------------------
 void g3dSceneNode::rotate(const Vector3& axis, const Radian& angle, TransformSpace relativeTo)
{
    Quaternion q;
    q.FromAngleAxis(angle,axis);
    rotate(q, relativeTo);
}

//-----------------------------------------------------------------------
void g3dSceneNode::rotate(const Quaternion& q, TransformSpace relativeTo)
{
	// Normalise quaternion to avoid drift
	Quaternion qnorm = q;
	qnorm.normalise();

    switch(relativeTo)
    {
    case TS_PARENT:
        // Rotations are normally relative to local axes, transform up
        m_Orientation = qnorm * m_Orientation;
        break;
    case TS_WORLD:
        // Rotations are normally relative to local axes, transform up
        m_Orientation = m_Orientation * _getDerivedOrientation().Inverse()
            * qnorm * _getDerivedOrientation();
        break;
    case TS_LOCAL:
        // Note the order of the mult, i.e. q comes after
        m_Orientation = m_Orientation * qnorm;
        break;
    }
	setSelfNeedUpdate(true);
    NotifyChildrenUpdate();
}
//-----------------------------------------------------------------------
void g3dSceneNode::roll(const Radian& angle, TransformSpace relativeTo)
{
    rotate(Vector3::UNIT_Z, angle, relativeTo);
}
//-----------------------------------------------------------------------
void g3dSceneNode::pitch(const Radian& angle, TransformSpace relativeTo)
{
    rotate(Vector3::UNIT_X, angle, relativeTo);
}
//-----------------------------------------------------------------------
void g3dSceneNode::yaw(const Radian& angle, TransformSpace relativeTo)
{
    rotate(Vector3::UNIT_Y, angle, relativeTo);
}