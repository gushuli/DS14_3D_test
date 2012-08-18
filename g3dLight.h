#pragma once

#include "g3dBasicHeader.h"



/*********************************************
@类名：g3dLight
@描述：对光源的封装
@说明：支持三种类型的光源类型：聚光灯，点光源和方向性光源提供简单的接口来操纵具体参数。
				创建光源不要直接使用构造函数，而是使用场景管理器的CreateLight（）。
				g3dLightWrapper是在渲染系统中使用的一个类型，与g3dLight一 一对应，具体参见g3dLightWrapper。
@修改历史：高继扬，2012/8/12，创建
*********************************************/
class g3dLight
{

public:
	/**默认构造函数	
		@说明：
			与参数为string的构造函数的区别在于默认构造函数：利用IDcount生成名字
						
		@参数：无
	
		@修改历史：
			高继扬，2012/8/12，创建
	*/
	g3dLight(void);

	/**构造函数	
		@说明：
			与默认构造函数的区别在于,默认构造函数利用IDcount生成名字
						
		@参数：无
	
		@修改历史：
			高继扬，2012/8/12，创建
	*/
	g3dLight(std::string name);

	/**析构函数
	*/
	~g3dLight(void);

	///光源类型枚举类型
	enum LightTypes
	{
		/// 点光源向各个方向均匀的发射光线
		LT_POINT = 0,
		/// 方向性光源向某一个方向发射平行光线
		LT_DIRECTIONAL = 1,
		/// 聚光灯，大家都懂的
		LT_SPOTLIGHT = 2
	};
	

	/** 设置光源类型
		@说明：无

		@参数：type：LightTypes

		@修改历史：
			高继扬，2012/8/12 ,  创建			
	*/
	void setType(LightTypes type);

	/** 得到光源类型
	*/
	LightTypes getType(void) const;

	 /** 设置光源的散射光颜色
        @说明：
			材质有环境光，散射光和镜面光三种属性，分别代表着对这三种光的反射比率。
			材质的环境光和散射光影响材质“看上去”的颜色，材质的镜面光属性决定它的
			反光程度。另外，材质还有一个自发光属性。
            Diffuse light simulates the typical light emanating from light sources and affects the base colour
            of objects together with ambient light.

		@参数：red:float , green:float , blue:float 

		@修改历史：
			高继扬，2012/8/12 ,  创建			
    */
    void setDiffuseColour(float red, float green, float blue);

    /** 设置光源的散射光颜色
        @说明：
			材质有环境光，散射光和镜面光三种属性，分别代表着对这三种光的反射比率。
			材质的环境光和散射光影响材质“看上去”的颜色，材质的镜面光属性决定它的
			反光程度。另外材质还有一个自发光属性。
            Diffuse light simulates the typical light emanating from light sources and affects the base colour
            of objects together with ambient light.

		@参数：colour：ColorValue&

		@修改历史：
			高继扬，2012/8/12 ,  创建			
    */
    void setDiffuseColour(const ColorValue& colour);

     /** 得到光源的散射光颜色
        @说明：
			材质有环境光，散射光和镜面光三种属性，分别代表着对这三种光的反射比率。
			材质的环境光和散射光影响材质“看上去”的颜色，材质的镜面光属性决定它的
			反光程度。另外材质还有一个自发光属性。
            Diffuse light simulates the typical light emanating from light sources and affects the base colour
            of objects together with ambient light.

		@参数：无

		@修改历史：
			高继扬，2012/8/12 ,  创建			
    */
    const ColorValue& getDiffuseColour(void) const;

   /** 设置光源的镜面光（specular light）的颜色.
       @说明：
			材质有环境光，散射光和镜面光三种属性，分别代表着对这三种光的反射比率。
			材质的环境光和散射光影响材质“看上去”的颜色，材质的镜面光属性决定它的
			反光程度。另外材质还有一个自发光属性。
       @参数：red:float, green:float, blue:float
        
		@修改历史：
			高继扬，2012/8/12，创建
    */
    void setSpecularColour(float red, float green, float blue);

    /** 设置光源的镜面光（specular light）的颜色.
       @说明：
			材质有环境光，散射光和镜面光三种属性，分别代表着对这三种光的反射比率。
			材质的环境光和散射光影响材质“看上去”的颜色，材质的镜面光属性决定它的
			反光程度。另外材质还有一个自发光属性。
       @参数：colour：ColorValue&
        
		@修改历史：
			高继扬，2012/8/12，创建
    */
    void setSpecularColour(const ColorValue& colour);

   /** 取得当前光源的镜面光（specular light）的颜色.
       @说明：
			材质有环境光，散射光和镜面光三种属性，分别代表着对这三种光的反射比率。
			材质的环境光和散射光影响材质“看上去”的颜色，材质的镜面光属性决定它的
			反光程度。另外材质还有一个自发光属性。
       @参数：无
        
		@修改历史：
			高继扬，2012/8/12，创建
    */
    const ColorValue& getSpecularColour(void) const;

	/** 设置光源的衰减参数
		@说明：
			光强会随着传播距离的增加而减小，这主要包括常数衰减因子，线性衰减因子和二次衰减因子，
			具体含义可参看opengl的光源部分。
			
		@param
			constant The constant factor in the attenuation formula: 1.0 means never attenuate, 0.0 is complete attenuation
		@param
			linear The linear factor in the attenuation formula: 1 means attenuate evenly over the distance
		@param
			quadratic The quadratic factor in the attenuation formula: adds a curvature to the attenuation formula.
	*/
	void setAttenuation(float constant, float linear, float quadratic);

	/** 得到光源衰减参数中的常数衰减因子
		@说明：无

		@参数：无

		@修改历史：
			高继扬，2012/8/12 , 创建
	*/
	float getAttenuationConstant(void) const;

	/** 得到光源衰减参数中的线性衰减因子
		@说明：无

		@参数：无

		@修改历史：
			高继扬，2012/8/12 , 创建
	*/
	float getAttenuationLinear(void) const;

	/** 得到光源衰减参数中的二次衰减因子
		@说明：无

		@参数：无

		@修改历史：
			高继扬，2012/8/12 , 创建
	*/
	float getAttenuationQuadric(void) const;

	/** 设置光源位置
		@说明：
			仅对点光源和聚光灯有效

		@参数：x:float, y:float, z:float

		@修改历史：
			高继扬，2012/8/12 , 创建
	*/
	void setPosition(float x, float y, float z);

	/** 设置光源位置
		@说明：
			仅对点光源和聚光灯有效

		@参数：vec:Vector3&

		@修改历史：
			高继扬，2012/8/12 , 创建
	*/
	void setPosition(const Vector3& vec);

	/** 得到当前光源位置
		@说明：
			仅对点光源和聚光灯有效

		@参数：无

		@修改历史：
			高继扬，2012/8/12 , 创建
	*/
	const Vector3& getPosition(void) const;

	/** 设置光源发射光线的方向
		@说明：
			仅对方向性光源和聚光灯有效

		@参数：x:float, y:float, z:float

		@修改历史：
			高继扬，2012/8/12 , 创建
	*/
	void setDirection(float x, float y, float z);

	/** 设置光源发射光线的方向
		@说明：
			仅对方向性光源和聚光灯有效

		@参数：vec:Vector3&

		@修改历史：
			高继扬，2012/8/12 , 创建
	*/
	void setDirection(const Vector3& vec);

	/** 得到光源发射光线的方向
		@说明：
			仅对方向性光源和聚光灯有效

		@参数：无

		@修改历史：
			高继扬，2012/8/12 , 创建
	*/
	const Vector3& getDirection(void) const;

	/** 设置聚光灯参数.
		@说明：
			描述一个聚光灯，在openGL中需要聚光灯切角，聚光指数和光线方向。
			这个函数设置切角和聚光指数，切角描述聚光灯光锥的半角，范围：[0,90]，
			聚光指数描述光线的聚集程度，范围：[0,1]

		@参数：
			cutoff：Radian，切角
		@参数：falloff：float，聚光指数

		@修改历史：
			高继扬，2012/8/12，创建
	*/
	void setSpotlightRange(const Radian& cutoff, float falloff = 0.0);

	/** 得到聚光灯的切角.
		@说明：
			描述一个聚光灯，在openGL中需要聚光灯切角，聚光指数和光线方向。
			切角描述聚光灯光锥的半角，范围：[0,90]，
			聚光指数描述光线的聚集程度，范围：[0,1]

		@参数：无

		@修改历史：
		高继扬，2012/8/12，创建
	*/
	const Radian& getSpotlightCutoff(void) const;

	/** 得到聚光指数
	*/
	float getSpotlightExponent(void) const;

	/** 设置聚光灯切角
		@说明：
		描述一个聚光灯，在openGL中需要聚光灯切角，聚光指数和光线方向。
		切角描述聚光灯光锥的半角，范围：[0,90]，
		聚光指数描述光线的聚集程度，范围：[0,1]

		@参数：
		cutoff：Radian，切角

		@修改历史：
		高继扬，2012/8/12，创建
	*/
	void setSpotlightCutoff(const Radian& val);

	/** 设置聚光灯聚光指数
		@说明：
		描述一个聚光灯，在openGL中需要聚光灯切角，聚光指数和光线方向。
		切角描述聚光灯光锥的半角，范围：[0,90]，
		聚光指数描述光线的聚集程度，范围：[0,1]

		@参数：
		cutoff：Radian，切角

		@修改历史：
		高继扬，2012/8/12，创建
	*/
	void setSpotlightExponent(float val);

public:
	///名称
	std::string m_Name;
private:
	///计数器
	static int IDcount;

	///光源类型
	LightTypes m_LightType;
	///位置
	Vector3 m_Position;
	///散射光颜色
	ColorValue m_Diffuse;
	///镜面光颜色
	ColorValue m_Specular;
	///光线方向
	Vector3 m_Direction;

	///聚光灯切角
	Radian m_SpotCutoff;
	///聚光灯聚光指数
	float m_SpotExponent;

	///常数衰减因子
	float m_AttenuationConst;
	///线性衰减因子
	float m_AttenuationLinear;
	///二次衰减因子
	float m_AttenuationQuad;
};

