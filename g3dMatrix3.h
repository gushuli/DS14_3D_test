#pragma once

#include "g3dVector3.h"
#include <cstring>


class Matrix3
{
public:
	 float m[3][3];

public:
	inline Matrix3 () {}
    inline explicit Matrix3 (const float arr[3][3])
	{
		memcpy(m,arr,9*sizeof(float));
	}
    inline Matrix3 (const Matrix3& rkMatrix)
	{
		memcpy(m,rkMatrix.m,9*sizeof(float));
	}
    Matrix3 (float fEntry00, float fEntry01, float fEntry02,
                float fEntry10, float fEntry11, float fEntry12,
                float fEntry20, float fEntry21, float fEntry22)
	{
		m[0][0] = fEntry00;
		m[0][1] = fEntry01;
		m[0][2] = fEntry02;
		m[1][0] = fEntry10;
		m[1][1] = fEntry11;
		m[1][2] = fEntry12;
		m[2][0] = fEntry20;
		m[2][1] = fEntry21;
		m[2][2] = fEntry22;
	}

};