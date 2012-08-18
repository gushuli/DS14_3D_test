
#include "g3dQuaternion.h"

const float Quaternion::msEpsilon = 1e-03;
const Quaternion Quaternion::ZERO(0,0,0,0);
const Quaternion Quaternion::IDENTITY(1,0,0,0);

//-----------------------------------------------------------------------
 void Quaternion::FromRotationMatrix (const Matrix3& kRot)
{
    // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
    // article "Quaternion Calculus and Fast Animation".

    float fTrace = kRot.m[0][0]+kRot.m[1][1]+kRot.m[2][2];
    float fRoot;

    if ( fTrace > 0.0 )
    {
        // |w| > 1/2, may as well choose w > 1/2
        fRoot = sqrt(fTrace + 1.0f);  // 2w
        w = 0.5f*fRoot;
        fRoot = 0.5f/fRoot;  // 1/(4w)
        x = (kRot.m[2][1]-kRot.m[1][2])*fRoot;
        y = (kRot.m[0][2]-kRot.m[2][0])*fRoot;
        z = (kRot.m[1][0]-kRot.m[0][1])*fRoot;
    }
    else
    {
        // |w| <= 1/2
        static size_t s_iNext[3] = { 1, 2, 0 };
        size_t i = 0;
        if ( kRot.m[1][1] > kRot.m[0][0] )
            i = 1;
        if ( kRot.m[2][2] > kRot.m[i][i] )
            i = 2;
        size_t j = s_iNext[i];
        size_t k = s_iNext[j];

        fRoot = sqrt(kRot.m[i][i]-kRot.m[j][j]-kRot.m[k][k] + 1.0f);
        float* apkQuat[3] = { &x, &y, &z };
        *apkQuat[i] = 0.5f*fRoot;
        fRoot = 0.5f/fRoot;
        w = (kRot.m[k][j]-kRot.m[j][k])*fRoot;
        *apkQuat[j] = (kRot.m[j][i]+kRot.m[i][j])*fRoot;
        *apkQuat[k] = (kRot.m[k][i]+kRot.m[i][k])*fRoot;
    }
}

//-----------------------------------------------------------------------
void Quaternion::ToRotationMatrix (Matrix3& kRot) const
{
    float fTx  = x+x;
    float fTy  = y+y;
    float fTz  = z+z;
    float fTwx = fTx*w;
    float fTwy = fTy*w;
    float fTwz = fTz*w;
    float fTxx = fTx*x;
    float fTxy = fTy*x;
    float fTxz = fTz*x;
    float fTyy = fTy*y;
    float fTyz = fTz*y;
    float fTzz = fTz*z;

    kRot.m[0][0] = 1.0f-(fTyy+fTzz);
    kRot.m[0][1] = fTxy-fTwz;
    kRot.m[0][2] = fTxz+fTwy;
    kRot.m[1][0] = fTxy+fTwz;
    kRot.m[1][1] = 1.0f-(fTxx+fTzz);
    kRot.m[1][2] = fTyz-fTwx;
    kRot.m[2][0] = fTxz-fTwy;
    kRot.m[2][1] = fTyz+fTwx;
    kRot.m[2][2] = 1.0f-(fTxx+fTyy);
}

//-----------------------------------------------------------------------
void Quaternion::FromAngleAxis (const Radian& rfAngle,
    const Vector3& rkAxis)
{
    // assert:  axis[] is unit length
    //
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

    Radian fHalfAngle ( 0.5*rfAngle );
	float fSin = sin(fHalfAngle.valueRadians());
	w = cos(fHalfAngle.valueRadians());
    x = fSin*rkAxis.x;
    y = fSin*rkAxis.y;
    z = fSin*rkAxis.z;
}

//-----------------------------------------------------------------------
void Quaternion::ToAngleAxis (Radian& rfAngle, Vector3& rkAxis) const
{
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

    float fSqrLength = x*x+y*y+z*z;
    if ( fSqrLength > 0.0 )
    {
        rfAngle = 2.0*acos(w);
        float fInvLength = 1/sqrt(fSqrLength);//求倒数，便于计算
        rkAxis.x = x*fInvLength;
        rkAxis.y = y*fInvLength;
        rkAxis.z = z*fInvLength;
    }
    else
    {
        // angle is 0 (mod 2*pi), so any axis will do
        rfAngle = Radian(0.0);
        rkAxis.x = 1.0;
        rkAxis.y = 0.0;
        rkAxis.z = 0.0;
    }
}

//-----------------------------------------------------------------------
void Quaternion::FromAxes (const Vector3* akAxis)
{
    Matrix3 kRot;

    for (size_t iCol = 0; iCol < 3; iCol++)
    {
        kRot.m[0][iCol] = akAxis[iCol].x;
        kRot.m[1][iCol] = akAxis[iCol].y;
        kRot.m[2][iCol] = akAxis[iCol].z;
    }

    FromRotationMatrix(kRot);
}

//-----------------------------------------------------------------------
void Quaternion::FromAxes (const Vector3& xaxis, const Vector3& yaxis, const Vector3& zaxis)
{
    Matrix3 kRot;

    kRot.m[0][0] = xaxis.x;
    kRot.m[1][0] = xaxis.y;
    kRot.m[2][0] = xaxis.z;

    kRot.m[0][1] = yaxis.x;
    kRot.m[1][1] = yaxis.y;
    kRot.m[2][1] = yaxis.z;

    kRot.m[0][2] = zaxis.x;
    kRot.m[1][2] = zaxis.y;
    kRot.m[2][2] = zaxis.z;

    FromRotationMatrix(kRot);

}

//-----------------------------------------------------------------------
void Quaternion::ToAxes (Vector3* akAxis) const
{
    Matrix3 kRot;

    ToRotationMatrix(kRot);

    for (size_t iCol = 0; iCol < 3; iCol++)
    {
        akAxis[iCol].x = kRot.m[0][iCol];
        akAxis[iCol].y = kRot.m[1][iCol];
        akAxis[iCol].z = kRot.m[2][iCol];
    }
}

//-----------------------------------------------------------------------
Vector3 Quaternion::xAxis(void) const
{
    //float fTx  = 2.0*x;
    float fTy  = 2.0f*y;
    float fTz  = 2.0f*z;
    float fTwy = fTy*w;
    float fTwz = fTz*w;
    float fTxy = fTy*x;
    float fTxz = fTz*x;
    float fTyy = fTy*y;
    float fTzz = fTz*z;

    return Vector3(1.0f-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);
}

//-----------------------------------------------------------------------
Vector3 Quaternion::yAxis(void) const
{
    float fTx  = 2.0f*x;
    float fTy  = 2.0f*y;
    float fTz  = 2.0f*z;
    float fTwx = fTx*w;
    float fTwz = fTz*w;
    float fTxx = fTx*x;
    float fTxy = fTy*x;
    float fTyz = fTz*y;
    float fTzz = fTz*z;

    return Vector3(fTxy-fTwz, 1.0f-(fTxx+fTzz), fTyz+fTwx);
}

//-----------------------------------------------------------------------
Vector3 Quaternion::zAxis(void) const
{
    float fTx  = 2.0f*x;
    float fTy  = 2.0f*y;
    float fTz  = 2.0f*z;
    float fTwx = fTx*w;
    float fTwy = fTy*w;
    float fTxx = fTx*x;
    float fTxz = fTz*x;
    float fTyy = fTy*y;
    float fTyz = fTz*y;

    return Vector3(fTxz+fTwy, fTyz-fTwx, 1.0f-(fTxx+fTyy));
}

//-----------------------------------------------------------------------
void Quaternion::ToAxes (Vector3& xaxis, Vector3& yaxis, Vector3& zaxis) const
{
    Matrix3 kRot;

    ToRotationMatrix(kRot);

    xaxis.x = kRot.m[0][0];
    xaxis.y = kRot.m[1][0];
    xaxis.z = kRot.m[2][0];

    yaxis.x = kRot.m[0][1];
    yaxis.y = kRot.m[1][1];
    yaxis.z = kRot.m[2][1];

    zaxis.x = kRot.m[0][2];
    zaxis.y = kRot.m[1][2];
    zaxis.z = kRot.m[2][2];
}

//-----------------------------------------------------------------------
Quaternion Quaternion::operator+ (const Quaternion& rkQ) const
{
    return Quaternion(w+rkQ.w,x+rkQ.x,y+rkQ.y,z+rkQ.z);
}

//-----------------------------------------------------------------------
Quaternion Quaternion::operator- (const Quaternion& rkQ) const
{
    return Quaternion(w-rkQ.w,x-rkQ.x,y-rkQ.y,z-rkQ.z);
}

//-----------------------------------------------------------------------
Quaternion Quaternion::operator* (const Quaternion& rkQ) const
{
    // NOTE:  Multiplication is not generally commutative, so in most
    // cases p*q != q*p.

    return Quaternion
    (
        w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z,
        w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y,
        w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z,
        w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x
    );
}

//-----------------------------------------------------------------------
Quaternion Quaternion::operator* (float fScalar) const
{
    return Quaternion(fScalar*w,fScalar*x,fScalar*y,fScalar*z);
}

//-----------------------------------------------------------------------
Quaternion operator* (float fScalar, const Quaternion& rkQ)
{
    return Quaternion(fScalar*rkQ.w,fScalar*rkQ.x,fScalar*rkQ.y,
        fScalar*rkQ.z);
}

//-----------------------------------------------------------------------
Quaternion Quaternion::operator- () const
{
    return Quaternion(-w,-x,-y,-z);
}

//-----------------------------------------------------------------------
float Quaternion::Dot (const Quaternion& rkQ) const
{
    return w*rkQ.w+x*rkQ.x+y*rkQ.y+z*rkQ.z;
}

//-----------------------------------------------------------------------
float Quaternion::Norm () const
{
    return w*w+x*x+y*y+z*z;
}

//-----------------------------------------------------------------------
float Quaternion::normalise(void)
{
	float len = Norm();
	float factor = 1.0f / sqrt(len);
	*this = *this * factor;
	return len;
}

//-----------------------------------------------------------------------
Quaternion Quaternion::Inverse () const
{
    float fNorm = w*w+x*x+y*y+z*z;
    if ( fNorm > 0.0 )
    {
        float fInvNorm = 1.0f/fNorm;
        return Quaternion(w*fInvNorm,-x*fInvNorm,-y*fInvNorm,-z*fInvNorm);
    }
    else
    {
        // return an invalid result to flag the error
        return ZERO;
    }
}

//-----------------------------------------------------------------------
Quaternion Quaternion::UnitInverse () const
{
    // assert:  'this' is unit length
    return Quaternion(w,-x,-y,-z);
}

//-----------------------------------------------------------------------
Vector3 Quaternion::operator* (const Vector3& v) const
{
	// nVidia SDK implementation
	Vector3 uv, uuv;
	Vector3 qvec(x, y, z);
	uv = qvec.crossProduct(v);
	uuv = qvec.crossProduct(uv);
	uv *= (2.0f * w);
	uuv *= 2.0f;

	return v + uv + uuv;

}
//-----------------------------------------------------------------------
