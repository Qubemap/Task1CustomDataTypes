#pragma once
#include "Vector4.h"
#include <string>

namespace MathClasses
{
	struct Matrix4
	{
		union
		{
			struct
			{
				float m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16;
			};

			struct
			{
				Vector4 xAxis;
				Vector4 yAxis;
				Vector4 zAxis;
				Vector4 translation;
			};

			Vector4 axis[4];
			float v[16];
			float mm[4][4];
		};

		Matrix4()
		{
			m1 = m2 = m3 = m4 = m5 = m6 = m7 = m8 = m9 = m10 = m11 = m12 = m13 = m14 = m15 = m16 = 0.0f;
		}

		Matrix4(float M1, float M2, float M3, float M4, float M5, float M6, float M7, float M8, float M9, float M10, float M11, float M12, float M13, float M14, float M15, float M16)
		{
			m1 = M1;
			m2 = M2;
			m3 = M3;
			m4 = M4;
			m5 = M5;
			m6 = M6;
			m7 = M7;
			m8 = M8;
			m9 = M9;
			m10 = M10;
			m11 = M11;
			m12 = M12;
			m13 = M13;
			m14 = M14;
			m15 = M15;
			m16 = M16;
		}
		
		Matrix4(float a[])
		{
			for (int i = 0; i < 16; i++)
			{
				v[i] = a[i];
			}
		}

		operator float* () { return v; }

		operator const float* () const { return v; }

		static Matrix4 MakeIdentity()
		{
			const Matrix4 identity = Matrix4(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);

			return identity;
		}

		float& operator [](int dim)
		{
			return v[dim];
		}

		const float& operator [](int dim) const
		{
			return v[dim];
		}

		Vector4 operator * (const Vector4& v) const {
			Vector4 result;

			result[0] = mm[0][0] * v[0] + mm[1][0] * v[1] +
				mm[2][0] * v[2] + mm[3][0] * v[3];

			result[1] = mm[0][1] * v[0] + mm[1][1] * v[1] +
				mm[2][1] * v[2] + mm[3][1] * v[3];

			result[2] = mm[0][2] * v[0] + mm[1][2] * v[1] +
				mm[2][2] * v[2] + mm[3][2] * v[3];

			result[3] = mm[0][3] * v[0] + mm[1][3] * v[1] +
				mm[2][3] * v[2] + mm[3][3] * v[3];
			return result;
		}

		Matrix4 operator *(Matrix4 rhs) const
		{
			return Matrix3(
				m1 * rhs.m1 + m4 * rhs.m2 + m7 * rhs.m3,
				m2 * rhs.m1 + m5 * rhs.m2 + m8 * rhs.m3,
				m3 * rhs.m1 + m6 * rhs.m2 + m9 * rhs.m3,

				m1 * rhs.m4 + m4 * rhs.m5 + m7 * rhs.m6,
				m2 * rhs.m4 + m5 * rhs.m5 + m8 * rhs.m6,
				m3 * rhs.m4 + m6 * rhs.m5 + m9 * rhs.m6,

				m1 * rhs.m7 + m4 * rhs.m8 + m7 * rhs.m9,
				m2 * rhs.m7 + m5 * rhs.m8 + m8 * rhs.m9,
				m3 * rhs.m7 + m6 * rhs.m8 + m9 * rhs.m9);
		}

		void Matrix4::setScaled(float x, float y, float z) 
		{
			xAxis = { x, 0, 0, 0 };
			yAxis = { 0, y, 0, 0 };
			zAxis = { 0, 0, z, 0 };
			translation = { 0, 0, 0, 1 };
		}

		void Matrix4::setRotateX(float radians) 
		{
			xAxis = { 1, 0, 0, 0 };
			yAxis = { 0, cosf(radians), sinf(radians), 0 };
			zAxis = { 0, -sinf(radians), cosf(radians), 0 };
			translation = { 0, 0, 0, 1 };
		}

		void Matrix4::translate(float x, float y, float z) {
			// apply vector offset
			translation += Vector4(x, y, z, 0);
		}
	};
}