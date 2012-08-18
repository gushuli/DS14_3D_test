#pragma once
#include <cassert>


/*********************************************
@类名：ColorValue
@描述：引擎中使用的标准颜色类
@说明：重载了大部分操作符，提供了一组静态成员变量作为标准的颜色方便使用
@修改历史：高继扬，2012/8/10，创建
*********************************************/
class ColorValue
{
public:

	~ColorValue(void);
	static const ColorValue ZERO;
	static const ColorValue Black;
	static const ColorValue White;
	static const ColorValue Red;
	static const ColorValue Green;
	static const ColorValue Blue;

	ColorValue( float red = 1.0f,
		float green = 1.0f,
		float blue = 1.0f,
		float alpha = 1.0f ) : r(red), g(green), b(blue), a(alpha)
	{ }

	bool operator==(const ColorValue& rhs) const;
	bool operator!=(const ColorValue& rhs) const;

	float r,g,b,a;

	inline float operator [] ( const size_t i ) const
	{
		assert( i < 4 );

		return *(&r+i);
	}

	/// Array accessor operator
	inline float& operator [] ( const size_t i )
	{
		assert( i < 4 );

		return *(&r+i);
	}

	


	// arithmetic operations
	inline ColorValue operator + ( const ColorValue& rkVector ) const
	{
		ColorValue kSum;

		kSum.r = r + rkVector.r;
		kSum.g = g + rkVector.g;
		kSum.b = b + rkVector.b;
		kSum.a = a + rkVector.a;

		return kSum;
	}

	inline ColorValue operator - ( const ColorValue& rkVector ) const
	{
		ColorValue kDiff;

		kDiff.r = r - rkVector.r;
		kDiff.g = g - rkVector.g;
		kDiff.b = b - rkVector.b;
		kDiff.a = a - rkVector.a;

		return kDiff;
	}

	inline ColorValue operator * (const float fScalar ) const
	{
		ColorValue kProd;

		kProd.r = fScalar*r;
		kProd.g = fScalar*g;
		kProd.b = fScalar*b;
		kProd.a = fScalar*a;

		return kProd;
	}

	inline ColorValue operator * ( const ColorValue& rhs) const
	{
		ColorValue kProd;

		kProd.r = rhs.r * r;
		kProd.g = rhs.g * g;
		kProd.b = rhs.b * b;
		kProd.a = rhs.a * a;

		return kProd;
	}

	inline ColorValue operator / ( const ColorValue& rhs) const
	{
		ColorValue kProd;

		kProd.r = r / rhs.r;
		kProd.g = g / rhs.g;
		kProd.b = b / rhs.b;
		kProd.a = a / rhs.a;

		return kProd;
	}

	inline ColorValue operator / (const float fScalar ) const
	{
		assert( fScalar != 0.0 );

		ColorValue kDiv;

		float fInv = 1.0f / fScalar;
		kDiv.r = r * fInv;
		kDiv.g = g * fInv;
		kDiv.b = b * fInv;
		kDiv.a = a * fInv;

		return kDiv;
	}

	inline friend ColorValue operator* (const float fScalar, const ColorValue& rkVector )
	{
		ColorValue kProd;

		kProd.r = fScalar * rkVector.r;
		kProd.g = fScalar * rkVector.g;
		kProd.b = fScalar * rkVector.b;
		kProd.a = fScalar * rkVector.a;

		return kProd;
	}

	// arithmetic updates
	inline ColorValue& operator += ( const ColorValue& rkVector )
	{
		r += rkVector.r;
		g += rkVector.g;
		b += rkVector.b;
		a += rkVector.a;

		return *this;
	}

	inline ColorValue& operator -= ( const ColorValue& rkVector )
	{
		r -= rkVector.r;
		g -= rkVector.g;
		b -= rkVector.b;
		a -= rkVector.a;

		return *this;
	}

	inline ColorValue& operator *= (const float fScalar )
	{
		r *= fScalar;
		g *= fScalar;
		b *= fScalar;
		a *= fScalar;
		return *this;
	}

	inline ColorValue& operator /= (const float fScalar )
	{
		assert( fScalar != 0.0 );

		float fInv = 1.0f / fScalar;

		r *= fInv;
		g *= fInv;
		b *= fInv;
		a *= fInv;

		return *this;
	}
};

