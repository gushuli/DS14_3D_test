#pragma once

class Degree;


/*********************************************
@类名：Radian
@描述：弧度
@说明：重载了大部分操作符，提供弧度-角度转换的接口
@修改历史：高继扬，2012/8/11，创建
*********************************************/
class Radian
{
	float mRad;

public:
	static const float PI;
	static const float fDeg2Rad ;
	static const float fRad2Deg ;
public:
	explicit Radian ( float r=0 ) : mRad(r) {}
	Radian ( const Degree& d );
	Radian& operator = ( const float& f ) { mRad = f; return *this; }
	Radian& operator = ( const Radian& r ) { mRad = r.mRad; return *this; }
	Radian& operator = ( const Degree& d );

	float valueDegrees() const; 
	float valueRadians() const { return mRad; }

    const Radian& operator + () const { return *this; }
	Radian operator + ( const Radian& r ) const { return Radian ( mRad + r.mRad ); }
	Radian operator + ( const Degree& d ) const;
	Radian& operator += ( const Radian& r ) { mRad += r.mRad; return *this; }
	Radian& operator += ( const Degree& d );
	Radian operator - () const { return Radian(-mRad); }
	Radian operator - ( const Radian& r ) const { return Radian ( mRad - r.mRad ); }
	Radian operator - ( const Degree& d ) const;
	Radian& operator -= ( const Radian& r ) { mRad -= r.mRad; return *this; }
	Radian& operator -= ( const Degree& d );
	Radian operator * ( float f ) const { return Radian ( mRad * f ); }
    Radian operator * ( const Radian& f ) const { return Radian ( mRad * f.mRad ); }
	Radian& operator *= ( float f ) { mRad *= f; return *this; }
	Radian operator / ( float f ) const { return Radian ( mRad / f ); }
	Radian& operator /= ( float f ) { mRad /= f; return *this; }
	friend Radian operator * ( float a, const Radian& b );
	friend Radian operator / ( float a, const Radian& b );
	

	bool operator <  ( const Radian& r ) const { return mRad <  r.mRad; }
	bool operator <= ( const Radian& r ) const { return mRad <= r.mRad; }
	bool operator == ( const Radian& r ) const { return mRad == r.mRad; }
	bool operator != ( const Radian& r ) const { return mRad != r.mRad; }
	bool operator >= ( const Radian& r ) const { return mRad >= r.mRad; }
	bool operator >  ( const Radian& r ) const { return mRad >  r.mRad; }

		
};


/*********************************************
@类名：Degree
@描述：角度
@说明：重载了大部分操作符，提供弧度-角度转换的接口
@修改历史：高继扬，2012/8/11，创建
*********************************************/
class Degree
{
	float mDeg; 
public:
	static const float PI;
	static const float fDeg2Rad ;
	static const float fRad2Deg ;
public:
	explicit Degree ( float d=0 ) : mDeg(d) {}
	Degree ( const Radian& r ) : mDeg(r.valueDegrees()) {}
	Degree& operator = ( const float& f ) { mDeg = f; return *this; }
	Degree& operator = ( const Degree& d ) { mDeg = d.mDeg; return *this; }
	Degree& operator = ( const Radian& r ) { mDeg = r.valueDegrees(); return *this; }

	float valueDegrees() const { return mDeg; }
	float valueRadians() const; 


	const Degree& operator + () const { return *this; }
	Degree operator + ( const Degree& d ) const { return Degree ( mDeg + d.mDeg ); }
	Degree operator + ( const Radian& r ) const { return Degree ( mDeg + r.valueDegrees() ); }
	Degree& operator += ( const Degree& d ) { mDeg += d.mDeg; return *this; }
	Degree& operator += ( const Radian& r ) { mDeg += r.valueDegrees(); return *this; }
	Degree operator - () const { return Degree(-mDeg); }
	Degree operator - ( const Degree& d ) const { return Degree ( mDeg - d.mDeg ); }
	Degree operator - ( const Radian& r ) const { return Degree ( mDeg - r.valueDegrees() ); }
	Degree& operator -= ( const Degree& d ) { mDeg -= d.mDeg; return *this; }
	Degree& operator -= ( const Radian& r ) { mDeg -= r.valueDegrees(); return *this; }
	Degree operator * ( float f ) const { return Degree ( mDeg * f ); }
    Degree operator * ( const Degree& f ) const { return Degree ( mDeg * f.mDeg ); }
	Degree& operator *= ( float f ) { mDeg *= f; return *this; }
	Degree operator / ( float f ) const { return Degree ( mDeg / f ); }
	Degree& operator /= ( float f ) { mDeg /= f; return *this; }
	friend Degree operator * ( float a, const Degree& b );
	friend Degree operator / ( float a, const Degree& b );
	bool operator <  ( const Degree& d ) const { return mDeg <  d.mDeg; }
	bool operator <= ( const Degree& d ) const { return mDeg <= d.mDeg; }
	bool operator == ( const Degree& d ) const { return mDeg == d.mDeg; }
	bool operator != ( const Degree& d ) const { return mDeg != d.mDeg; }
	bool operator >= ( const Degree& d ) const { return mDeg >= d.mDeg; }
	bool operator >  ( const Degree& d ) const { return mDeg >  d.mDeg; }

};