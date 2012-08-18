#include "g3dDegRad.h"


const float Radian::PI=3.1415926;
const float Radian::fDeg2Rad = Radian::PI / float(180.0);
const float Radian::fRad2Deg = float(180.0) / Radian::PI;

const float Degree::PI=3.1415926;
const float Degree::fDeg2Rad = Degree::PI / float(180.0);
const float Degree::fRad2Deg = float(180.0) / Degree::PI;


float Radian::valueDegrees() const
{
	return mRad*fRad2Deg;
}
float Degree::valueRadians() const
{
	return mDeg * fDeg2Rad;
}


Radian operator * ( float a, const Radian& b )
{
	return Radian ( a * b.valueRadians() );
}

 Radian operator / ( float a, const Radian& b )
{
	return Radian ( a / b.valueRadians() );
}

Degree operator * ( float a, const Degree& b )
{
	return Degree ( a * b.valueDegrees() );
}

Degree operator / ( float a, const Degree& b )
{
	return Degree ( a / b.valueDegrees() );
}