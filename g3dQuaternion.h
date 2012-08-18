#pragma once
#include "g3dDegRad.h"
#include "g3dVector3.h"
#include "g3dMatrix3.h"

/*********************************************
@类名：Quaternion
@描述：四元数
@说明：四元数是本引擎进行旋转的数学基础（网上资料挺多的）
				这个类提供了四元数一组接口，但是一般来讲，用户用
				不到，所以不做过多的介绍。
@修改历史：高继扬，2012/8/11
*********************************************/
class  Quaternion
{
public:
	float w,x,y,z;

	/// Cutoff for sine near zero
        static const float msEpsilon;

        // special values
        static const Quaternion ZERO;
        static const Quaternion IDENTITY;
public:
	/// Default constructor, initializes to identity rotation (aka 0°)
	inline Quaternion ()
		: w(1), x(0), y(0), z(0)
	{
	}
	/// Construct from an explicit list of values
	inline Quaternion (
		float fW,
		float fX, float fY, float fZ)
		: w(fW), x(fX), y(fY), z(fZ)
	{
	}
    /// Construct a quaternion from a rotation matrix
    inline Quaternion(const Matrix3& rot)
    {
        this->FromRotationMatrix(rot);
    }
    /// Construct a quaternion from an angle/axis
    inline Quaternion(const Radian& rfAngle, const Vector3& rkAxis)
    {
        this->FromAngleAxis(rfAngle, rkAxis);
    }
    /// Construct a quaternion from 3 orthonormal local axes
    inline Quaternion(const Vector3& xaxis, const Vector3& yaxis, const Vector3& zaxis)
    {
        this->FromAxes(xaxis, yaxis, zaxis);
    }
    /// Construct a quaternion from 3 orthonormal local axes
    inline Quaternion(const Vector3* akAxis)
    {
        this->FromAxes(akAxis);
    }
	
	inline float operator [] ( const size_t i ) const
	{
		assert( i < 4 );

		return *(&w+i);
	}

	/// Array accessor operator
	inline float& operator [] ( const size_t i )
	{
		assert( i < 4 );

		return *(&w+i);
	}

	/// Pointer accessor for direct copying
	inline float* ptr()
	{
		return &w;
	}

	/// Pointer accessor for direct copying
	inline const float* ptr() const
	{
		return &w;
	}

	void FromRotationMatrix (const Matrix3& kRot);
    void ToRotationMatrix (Matrix3& kRot) const;
	/** Setups the quaternion using the supplied vector, and "roll" around
		that vector by the specified radians.
	*/
    void FromAngleAxis (const Radian& rfAngle, const Vector3& rkAxis);
    void ToAngleAxis (Radian& rfAngle, Vector3& rkAxis) const;
    inline void ToAngleAxis (Degree& dAngle, Vector3& rkAxis) const {
        Radian rAngle;
        ToAngleAxis ( rAngle, rkAxis );
        dAngle = rAngle;
    }
	/** Constructs the quaternion using 3 axes, the axes are assumed to be orthonormal
		@see FromAxes
	*/
    void FromAxes (const Vector3* akAxis);
    void FromAxes (const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);
	/** Gets the 3 orthonormal axes defining the quaternion. @see FromAxes */
    void ToAxes (Vector3* akAxis) const;
    void ToAxes (Vector3& xAxis, Vector3& yAxis, Vector3& zAxis) const;

	/** Returns the X orthonormal axis defining the quaternion. Same as doing
		xAxis = Vector3::UNIT_X * this. Also called the local X-axis
	*/
    Vector3 xAxis(void) const;

    /** Returns the Y orthonormal axis defining the quaternion. Same as doing
		yAxis = Vector3::UNIT_Y * this. Also called the local Y-axis
	*/
    Vector3 yAxis(void) const;

	/** Returns the Z orthonormal axis defining the quaternion. Same as doing
		zAxis = Vector3::UNIT_Z * this. Also called the local Z-axis
	*/
    Vector3 zAxis(void) const;

    inline Quaternion& operator= (const Quaternion& rkQ)
	{
		w = rkQ.w;
		x = rkQ.x;
		y = rkQ.y;
		z = rkQ.z;
		return *this;
	}
    Quaternion operator+ (const Quaternion& rkQ) const;
    Quaternion operator- (const Quaternion& rkQ) const;
    Quaternion operator* (const Quaternion& rkQ) const;
    Quaternion operator* (float fScalar) const;
    friend Quaternion operator* (float fScalar,const Quaternion& rkQ);
    Quaternion operator- () const;
    inline bool operator== (const Quaternion& rhs) const
	{
		return (rhs.x == x) && (rhs.y == y) &&
			(rhs.z == z) && (rhs.w == w);
	}
    inline bool operator!= (const Quaternion& rhs) const
	{
		return !operator==(rhs);
	}
    // functions of a quaternion
    /// Returns the dot product of the quaternion
    float Dot (const Quaternion& rkQ) const;
    /* Returns the normal length of this quaternion.
        @note This does <b>not</b> alter any values.
    */
    float Norm () const;
    /// Normalises this quaternion, and returns the previous length
    float normalise(void); 
    Quaternion Inverse () const;  // apply to non-zero quaternion
    Quaternion UnitInverse () const;  // apply to unit-length quaternion

    /// Rotation of a vector by a quaternion
    Vector3 operator* (const Vector3& rkVector) const;

   	/** Calculate the local roll element of this quaternion.
	@param reprojectAxis By default the method returns the 'intuitive' result
		that is, if you projected the local Y of the quaternion onto the X and
		Y axes, the angle between them is returned. If set to false though, the
		result is the actual yaw that will be used to implement the quaternion,
		which is the shortest possible path to get to the same orientation and 
            may involve less axial rotation.  The co-domain of the returned value is 
            from -180 to 180 degrees.
	*/
	Radian getRoll(bool reprojectAxis = true) const;
   	/** Calculate the local pitch element of this quaternion
	@param reprojectAxis By default the method returns the 'intuitive' result
		that is, if you projected the local Z of the quaternion onto the X and
		Y axes, the angle between them is returned. If set to true though, the
		result is the actual yaw that will be used to implement the quaternion,
		which is the shortest possible path to get to the same orientation and 
        may involve less axial rotation.  The co-domain of the returned value is 
        from -180 to 180 degrees.
	*/
	Radian getPitch(bool reprojectAxis = true) const;
   	/** Calculate the local yaw element of this quaternion
	@param reprojectAxis By default the method returns the 'intuitive' result
		that is, if you projected the local Y of the quaternion onto the X and
		Z axes, the angle between them is returned. If set to true though, the
		result is the actual yaw that will be used to implement the quaternion,
		which is the shortest possible path to get to the same orientation and 
		may involve less axial rotation. The co-domain of the returned value is 
        from -180 to 180 degrees.
	*/
	Radian getYaw(bool reprojectAxis = true) const;		
	/// Equality with tolerance (tolerance is max angle difference)
};