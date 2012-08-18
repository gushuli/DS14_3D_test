#include "g3dLight.h"

int g3dLight::IDcount=0;
//-----------------------------------------------------------------------
g3dLight::g3dLight(void)
	:
	m_LightType(LT_POINT),
	m_Position(Vector3::ZERO),
	m_Diffuse(ColorValue::White),
	m_Specular(ColorValue::Black),
	m_Direction(Vector3::UNIT_Z),
	m_AttenuationConst(1.0f),
	m_AttenuationLinear(0.0f),
	m_AttenuationQuad(0.0f),
	m_SpotExponent(0.0f),
	m_SpotCutoff(Radian((Radian::PI)/4))
{
	m_Name="Light"+IDcount;
	IDcount++;
}
//-----------------------------------------------------------------------
g3dLight::g3dLight(std::string name)
	:
	m_LightType(LT_POINT),
	m_Position(Vector3::ZERO),
	m_Diffuse(ColorValue::White),
	m_Specular(ColorValue::Black),
	m_Direction(Vector3::UNIT_Z),
	m_AttenuationConst(1.0f),
	m_AttenuationLinear(0.0f),
	m_AttenuationQuad(0.0f),
	m_SpotExponent(0.0f),
	m_SpotCutoff(Radian((Radian::PI)/4))
{
	m_Name=name;
	IDcount++;
}
//-----------------------------------------------------------------------
g3dLight::~g3dLight(void)
{
}
//-----------------------------------------------------------------------
 void g3dLight::setType(LightTypes type)
 {
	 m_LightType=type;
 }

 //-----------------------------------------------------------------------
 g3dLight::LightTypes g3dLight::getType(void) const
 {
	return m_LightType;
 }
//-----------------------------------------------------------------------
 void g3dLight::setDiffuseColour(float red, float green, float blue)
 {
	 m_Diffuse.r = red;
	 m_Diffuse.b = blue;
	 m_Diffuse.g = green;
 }
 //-----------------------------------------------------------------------
 void g3dLight::setDiffuseColour(const ColorValue& colour)
 {
	 m_Diffuse = colour;
 }
 //-----------------------------------------------------------------------
 const ColorValue& g3dLight::getDiffuseColour(void) const
 {
	 return m_Diffuse;
 }
 //-----------------------------------------------------------------------
 void g3dLight::setSpecularColour(float red, float green, float blue)
 {
	 m_Specular.r = red;
	 m_Specular.b = blue;
	 m_Specular.g = green;
 }
 //-----------------------------------------------------------------------
 void g3dLight::setSpecularColour(const ColorValue& colour)
 {
	 m_Specular = colour;
 }
 //-----------------------------------------------------------------------
 const ColorValue& g3dLight::getSpecularColour(void) const
 {
	 return m_Specular;
 }
void g3dLight::setAttenuation(float constant, float linear, float quadratic)
{
	m_AttenuationConst=constant;
	m_AttenuationLinear=linear;
	m_AttenuationQuad=quadratic;
}

//-----------------------------------------------------------------------
float g3dLight::getAttenuationConstant(void) const
{
	return m_AttenuationConst;
}

//-----------------------------------------------------------------------
float g3dLight::getAttenuationLinear(void) const
{
	return m_AttenuationLinear;
}
//-----------------------------------------------------------------------
float g3dLight::getAttenuationQuadric(void) const
{
	return m_AttenuationQuad;
}
//-----------------------------------------------------------------------
 void g3dLight::setPosition(float x, float y, float z)
 {
	setPosition(Vector3(x,y,z));
 }
 //-----------------------------------------------------------------------

void g3dLight::setPosition(const Vector3& vec)
{
	m_Position=vec;
}
//-----------------------------------------------------------------------
const Vector3& g3dLight::getPosition(void) const
{
	return m_Position;
}
//-----------------------------------------------------------------------

void g3dLight::setDirection(float x, float y, float z)
{
	setDirection(Vector3(x,y,z));
}
//-----------------------------------------------------------------------
void g3dLight::setDirection(const Vector3& vec)
{
	m_Direction=vec;
}
//-----------------------------------------------------------------------
const Vector3& g3dLight::getDirection(void) const
{
	return m_Direction;
}
//-----------------------------------------------------------------------
void g3dLight::setSpotlightRange(const Radian& cutoff, float falloff )
{
	m_SpotCutoff=cutoff;
	m_SpotExponent=falloff;
}
//-----------------------------------------------------------------------

const Radian& g3dLight::getSpotlightCutoff(void) const
{
	return m_SpotCutoff;
}
//-----------------------------------------------------------------------

float g3dLight::getSpotlightExponent(void) const
{
	return m_SpotExponent;
}
//-----------------------------------------------------------------------

void g3dLight::setSpotlightCutoff(const Radian& val)
{
	m_SpotCutoff=val;
}

//-----------------------------------------------------------------------
void g3dLight::setSpotlightExponent(float val)
{
	m_SpotExponent=val;
}


