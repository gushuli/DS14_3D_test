#pragma once

#include <cmath>
#include <cassert>


/*********************************************
@类名：Vector3
@描述：标准的三维向量
@说明：可以用于表示在三维坐标系中的位置，方向，和缩放因子
				重载了大部分操作符并提供了一组标准向量
@修改历史：高继扬，2012/8/10
*********************************************/

class Vector3
{
public:
	float x,y,z;

	 static const Vector3 ZERO;
    static const Vector3 UNIT_X;
    static const Vector3 UNIT_Y;
    static const Vector3 UNIT_Z;
    static const Vector3 NEGATIVE_UNIT_X;
    static const Vector3 NEGATIVE_UNIT_Y;
    static const Vector3 NEGATIVE_UNIT_Z;
    static const Vector3 UNIT_SCALE;
public:
    inline Vector3()
    {
    }

    inline Vector3( const float fX, const float fY, const float fZ )
        : x( fX ), y( fY ), z( fZ )
    {
    }

    inline explicit Vector3( const float afCoordinate[3] )
        : x( afCoordinate[0] ),
            y( afCoordinate[1] ),
            z( afCoordinate[2] )
    {
    }

    inline explicit Vector3( const int afCoordinate[3] )
    {
        x = (float)afCoordinate[0];
        y = (float)afCoordinate[1];
        z = (float)afCoordinate[2];
    }

    inline explicit Vector3( float* const r )
        : x( r[0] ), y( r[1] ), z( r[2] )
    {
    }

    inline explicit Vector3( const float scaler )
        : x( scaler )
        , y( scaler )
        , z( scaler )
    {
    }

	inline float operator [] ( const size_t i ) const
    {
        assert( i < 3 );

        return *(&x+i);
    }

	inline float& operator [] ( const size_t i )
    {
        assert( i < 3 );

        return *(&x+i);
    }
	/// Pointer accessor for direct copying
	inline float* ptr()
	{
		return &x;
	}
	/// Pointer accessor for direct copying
	inline const float* ptr() const
	{
		return &x;
	}

    /** Assigns the value of the other vector.
        @param
            rkVector The other vector
    */
    inline Vector3& operator = ( const Vector3& rkVector )
    {
        x = rkVector.x;
        y = rkVector.y;
        z = rkVector.z;

        return *this;
    }

    inline Vector3& operator = ( const float fScaler )
    {
        x = fScaler;
        y = fScaler;
        z = fScaler;

        return *this;
    }

    inline bool operator == ( const Vector3& rkVector ) const
    {
        return ( x == rkVector.x && y == rkVector.y && z == rkVector.z );
    }

    inline bool operator != ( const Vector3& rkVector ) const
    {
        return ( x != rkVector.x || y != rkVector.y || z != rkVector.z );
    }

    // arithmetic operations
    inline Vector3 operator + ( const Vector3& rkVector ) const
    {
        return Vector3(
            x + rkVector.x,
            y + rkVector.y,
            z + rkVector.z);
    }

    inline Vector3 operator - ( const Vector3& rkVector ) const
    {
        return Vector3(
            x - rkVector.x,
            y - rkVector.y,
            z - rkVector.z);
    }

    inline Vector3 operator * ( const float fScalar ) const
    {
        return Vector3(
            x * fScalar,
            y * fScalar,
            z * fScalar);
    }

    inline Vector3 operator * ( const Vector3& rhs) const
    {
        return Vector3(
            x * rhs.x,
            y * rhs.y,
            z * rhs.z);
    }

    inline Vector3 operator / ( const float fScalar ) const
    {
        assert( fScalar != 0.0 );

        float fInv = 1.0f / fScalar;

        return Vector3(
            x * fInv,
            y * fInv,
            z * fInv);
    }

    inline Vector3 operator / ( const Vector3& rhs) const
    {
        return Vector3(
            x / rhs.x,
            y / rhs.y,
            z / rhs.z);
    }

    inline const Vector3& operator + () const
    {
        return *this;
    }

    inline Vector3 operator - () const
    {
        return Vector3(-x, -y, -z);
    }

    // overloaded operators to help Vector3
    inline friend Vector3 operator * ( const float fScalar, const Vector3& rkVector )
    {
        return Vector3(
            fScalar * rkVector.x,
            fScalar * rkVector.y,
            fScalar * rkVector.z);
    }

    inline friend Vector3 operator / ( const float fScalar, const Vector3& rkVector )
    {
        return Vector3(
            fScalar / rkVector.x,
            fScalar / rkVector.y,
            fScalar / rkVector.z);
    }

    inline friend Vector3 operator + (const Vector3& lhs, const float rhs)
    {
        return Vector3(
            lhs.x + rhs,
            lhs.y + rhs,
            lhs.z + rhs);
    }

    inline friend Vector3 operator + (const float lhs, const Vector3& rhs)
    {
        return Vector3(
            lhs + rhs.x,
            lhs + rhs.y,
            lhs + rhs.z);
    }

    inline friend Vector3 operator - (const Vector3& lhs, const float rhs)
    {
        return Vector3(
            lhs.x - rhs,
            lhs.y - rhs,
            lhs.z - rhs);
    }

    inline friend Vector3 operator - (const float lhs, const Vector3& rhs)
    {
        return Vector3(
            lhs - rhs.x,
            lhs - rhs.y,
            lhs - rhs.z);
    }

    // arithmetic updates
    inline Vector3& operator += ( const Vector3& rkVector )
    {
        x += rkVector.x;
        y += rkVector.y;
        z += rkVector.z;

        return *this;
    }

    inline Vector3& operator += ( const float fScalar )
    {
        x += fScalar;
        y += fScalar;
        z += fScalar;
        return *this;
    }

    inline Vector3& operator -= ( const Vector3& rkVector )
    {
        x -= rkVector.x;
        y -= rkVector.y;
        z -= rkVector.z;

        return *this;
    }

    inline Vector3& operator -= ( const float fScalar )
    {
        x -= fScalar;
        y -= fScalar;
        z -= fScalar;
        return *this;
    }

    inline Vector3& operator *= ( const float fScalar )
    {
        x *= fScalar;
        y *= fScalar;
        z *= fScalar;
        return *this;
    }

    inline Vector3& operator *= ( const Vector3& rkVector )
    {
        x *= rkVector.x;
        y *= rkVector.y;
        z *= rkVector.z;

        return *this;
    }

    inline Vector3& operator /= ( const float fScalar )
    {
        assert( fScalar != 0.0 );

        float fInv = 1.0f / fScalar;

        x *= fInv;
        y *= fInv;
        z *= fInv;

        return *this;
    }

    inline Vector3& operator /= ( const Vector3& rkVector )
    {
        x /= rkVector.x;
        y /= rkVector.y;
        z /= rkVector.z;

        return *this;
    }


    /** Returns the length (magnitude) of the vector.
        @warning
            This operation requires a square root and is expensive in
            terms of CPU operations. If you don't need to know the exact
            length (e.g. for just comparing lengths) use squaredLength()
            instead.
    */
    inline float length () const
    {
        return sqrt( x * x + y * y + z * z );
    }

    /** Returns the square of the length(magnitude) of the vector.
        @remarks
            This  method is for efficiency - calculating the actual
            length of a vector requires a square root, which is expensive
            in terms of the operations required. This method returns the
            square of the length of the vector, i.e. the same as the
            length but before the square root is taken. Use this if you
            want to find the longest / shortest vector without incurring
            the square root.
    */
    inline float squaredLength () const
    {
        return x * x + y * y + z * z;
    }

    /** Returns the distance to another vector.
        @warning
            This operation requires a square root and is expensive in
            terms of CPU operations. If you don't need to know the exact
            distance (e.g. for just comparing distances) use squaredDistance()
            instead.
    */
    inline float distance(const Vector3& rhs) const
    {
        return (*this - rhs).length();
    }

    /** Returns the square of the distance to another vector.
        @remarks
            This method is for efficiency - calculating the actual
            distance to another vector requires a square root, which is
            expensive in terms of the operations required. This method
            returns the square of the distance to another vector, i.e.
            the same as the distance but before the square root is taken.
            Use this if you want to find the longest / shortest distance
            without incurring the square root.
    */
    inline float squaredDistance(const Vector3& rhs) const
    {
        return (*this - rhs).squaredLength();
    }

    /** Calculates the dot (scalar) product of this vector with another.
        @remarks
            The dot product can be used to calculate the angle between 2
            vectors. If both are unit vectors, the dot product is the
            cosine of the angle; otherwise the dot product must be
            divided by the product of the lengths of both vectors to get
            the cosine of the angle. This result can further be used to
            calculate the distance of a point from a plane.
        @param
            vec Vector with which to calculate the dot product (together
            with this one).
        @return
            A float representing the dot product value.
    */
    inline float dotProduct(const Vector3& vec) const
    {
        return x * vec.x + y * vec.y + z * vec.z;
    }

    /** Calculates the absolute dot (scalar) product of this vector with another.
        @remarks
            This function work similar dotProduct, except it use absolute value
            of each component of the vector to computing.
        @param
            vec Vector with which to calculate the absolute dot product (together
            with this one).
        @return
            A float representing the absolute dot product value.
    */
    inline float absDotProduct(const Vector3& vec) const
    {
        return fabs(x * vec.x) + fabs(y * vec.y) + fabs(z * vec.z);
    }

    /** Normalises the vector.
        @remarks
            This method normalises the vector such that it's
            length / magnitude is 1. The result is called a unit vector.
        @note
            This function will not crash for zero-sized vectors, but there
            will be no changes made to their components.
        @return The previous length of the vector.
    */
    inline float normalise()
    {
        float fLength = sqrt( x * x + y * y + z * z );

        if ( fLength > float(0.0f) )
        {
            float fInvLength = 1.0f / fLength;
            x *= fInvLength;
            y *= fInvLength;
            z *= fInvLength;
        }

        return fLength;
    }

    /** Calculates the cross-product of 2 vectors, i.e. the vector that
        lies perpendicular to them both.
        @remarks
            The cross-product is normally used to calculate the normal
            vector of a plane, by calculating the cross-product of 2
            non-equivalent vectors which lie on the plane (e.g. 2 edges
            of a triangle).
        @param
            vec Vector which, together with this one, will be used to
            calculate the cross-product.
        @return
            A vector which is the result of the cross-product. This
            vector will <b>NOT</b> be normalised, to maximise efficiency
            - call Vector3::normalise on the result if you wish this to
            be done. As for which side the resultant vector will be on, the
            returned vector will be on the side from which the arc from 'this'
            to rkVector is anticlockwise, e.g. UNIT_Y.crossProduct(UNIT_Z)
            = UNIT_X, whilst UNIT_Z.crossProduct(UNIT_Y) = -UNIT_X.
			This is because Joy3D uses a right-handed coordinate system.
        @par
            For a clearer explanation, look a the left and the bottom edges
            of your monitor's screen. Assume that the first vector is the
            left edge and the second vector is the bottom edge, both of
            them starting from the lower-left corner of the screen. The
            resulting vector is going to be perpendicular to both of them
            and will go <i>inside</i> the screen, towards the cathode tube
            (assuming you're using a CRT monitor, of course).
    */
    inline Vector3 crossProduct( const Vector3& rkVector ) const
    {
        return Vector3(
            y * rkVector.z - z * rkVector.y,
            z * rkVector.x - x * rkVector.z,
            x * rkVector.y - y * rkVector.x);
    }
};