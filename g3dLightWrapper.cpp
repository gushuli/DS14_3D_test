#include "g3dLightWrapper.h"

//------------------------------------------------------------------------------------------------
g3dLightWrapper::g3dLightWrapper(g3dLight* light)
{
	m_pLight=light;
	LightID=0;
	isActive=false;
	InitWrapper();
}

//------------------------------------------------------------------------------------------------
g3dLightWrapper::~g3dLightWrapper(void)
{
}

//------------------------------------------------------------------------------------------------
void g3dLightWrapper::setLight(g3dLight* light)
{
	m_pLight=light;
}

//------------------------------------------------------------------------------------------------
g3dLight* g3dLightWrapper::getLight(void)
{
	return m_pLight;
}

//------------------------------------------------------------------------------------------------
void g3dLightWrapper::InitWrapper()
{
	assert(m_pLight!=NULL);

	m_Name=m_pLight->m_Name;
	m_LightType=m_pLight->getType();

	ColorValue diffusecolor= m_pLight->getDiffuseColour();
	ColorValue specularcolor= m_pLight->getSpecularColour();

	//环境光和散射光最能反映物体颜色，所以只是颜色的强度不同，但各分量的比率相同
	m_LightAmbient[0]=diffusecolor.r/10.0f;
	m_LightAmbient[1]=diffusecolor.g/10.0f;
	m_LightAmbient[2]=diffusecolor.b/10.0f;
	m_LightAmbient[3]=1.0f;
	m_LightDiffuse[0]=diffusecolor.r;
	m_LightDiffuse[1]=diffusecolor.g;
	m_LightDiffuse[2]=diffusecolor.b;
	m_LightDiffuse[3]=1.0f;

	m_LightSpecular[0]=specularcolor.r;
	m_LightSpecular[1]=specularcolor.g;
	m_LightSpecular[2]=specularcolor.b;
	m_LightSpecular[3]=1.0f;

	switch(m_LightType)
	{	
	case g3dLight::LT_SPOTLIGHT:
		{
			Vector3 pos=m_pLight->getPosition();
			m_LightPosition[0]=pos.x;
			m_LightPosition[1]=pos.y;
			m_LightPosition[2]=pos.z;
			m_LightPosition[3]=1.0f;
			//1.0f indicates that this is a point light 
			//and then xyz represent the position of the light
			//Actually spotlight is a special point light,
			Vector3 dir=m_pLight->getDirection();
			m_LightDirection[0]=dir.x;
			m_LightDirection[1]=dir.y;
			m_LightDirection[2]=dir.z;
			m_LightDirection[3]=0.0f;
			//In the case of spotlight, it only needs three parameters 
			//which are the first three number of m_LightDirection, 
			//so m_LightDirection[3] has nothing to with the spotlight.
			break;
		}
	case g3dLight::LT_POINT:
		{
			Vector3 pos=m_pLight->getPosition();
			m_LightPosition[0]=pos.x;
			m_LightPosition[1]=pos.y;
			m_LightPosition[2]=pos.z;
			m_LightPosition[3]=1.0f;
			//1.0f indicates that this is a point light 
			//and then xyz represent the position of the light		
			break;		
		}
	case g3dLight::LT_DIRECTIONAL:
		{
			Vector3 dir=m_pLight->getDirection();
			m_LightDirection[0]=dir.x;
			m_LightDirection[1]=dir.y;
			m_LightDirection[2]=dir.z;
			m_LightDirection[3]=0.0f;
			//0.0f indicates that this is a directional light 
			//and then xyz represent the direction of the light
			break;		
		}
	}
}
//------------------------------------------------------------------------------------------------