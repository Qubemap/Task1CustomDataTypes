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