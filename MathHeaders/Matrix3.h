#pragma once
#include "Vector3.h"
#include <string>

namespace MathClasses
{
	struct Matrix3
	{
		union
		{
			struct
			{
				float m1, m2, m3, m4, m5, m6, m7, m8, m9;
			};

			float v[9]; //1D array

			float mm[3][3]; //2d array

			Vector3 axis[3]; //as Vector3's
		};

		Matrix3()
		{
			m1 = m2 = m3 = m4 = m5 = m6 = m7 = m8 = m9 = 0.0f;
		}

		Matrix3(float M1, float M2, float M3, float M4, float M5, float M6, float M7, float M8, float M9)
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
		}

		Matrix3(float a[])
		{
			for (int i = 0; i < 9; i++)
			{
				v[i] = a[i];
			}
		}

		operator float* () { return v; }

		operator const float* () const { return v; }

		static Matrix3 MakeIdentity()
		{
			Matrix3 identity;
			identity.m1 = 1;
			identity.m2 = 0;
			identity.m3 = 0;

			identity.m4 = 0;
			identity.m5 = 1;
			identity.m6 = 0;

			identity.m7 = 0;
			identity.m8 = 0;
			identity.m9 = 1;

			return identity;
		}

		//modifiable access to each element
		float& operator [](int dim)
		{
			return v[dim];
		}

		//const access to each element
		const float& operator [](int dim) const
		{
			return v[dim];
		}

		Matrix3 operator *(Matrix3 rhs) const
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

		Matrix3 operator *=(const Matrix3 rhs)
		{
			
			m1 = m1 * rhs.m1 + m4 * rhs.m2 + m7 * rhs.m3;
			m2 = m2 * rhs.m1 + m5 * rhs.m2 + m8 * rhs.m3;
			m3 = m3 * rhs.m1 + m6 * rhs.m2 + m9 * rhs.m3;

			m4 = m1 * rhs.m4 + m4 * rhs.m5 + m7 * rhs.m6;
			m5 = m2 * rhs.m4 + m5 * rhs.m5 + m8 * rhs.m6;
			m6 = m3 * rhs.m4 + m6 * rhs.m5 + m9 * rhs.m6;

			m7 = m1 * rhs.m7 + m4 * rhs.m8 + m7 * rhs.m9;
			m8 = m2 * rhs.m7 + m5 * rhs.m8 + m8 * rhs.m9;
			m9 = m3 * rhs.m7 + m6 * rhs.m8 + m9 * rhs.m9;
		}

		bool operator == (const Matrix3& other) const
		{
			const float THRESHOLD = 0.00001f;

			float cmp;
			
			for (int i = 0; i < 9; i++)
			{
				cmp = fabsf(v[i] - other.v[i]);
				if (cmp >= THRESHOLD)
				{
					return false;
				}
				i++;
			}
			
			return true;
		}

		bool operator !=(const Matrix3& other) const
		{
			return !(*this == other);
		}

		Vector3 operator *(Vector3 rhs) const
		{
			return Vector3(
				Vector3(m1, m4, m7).Dot(rhs),
				Vector3(m2, m5, m8).Dot(rhs),
				Vector3(m3, m6, m9).Dot(rhs)
			);
		}

		Matrix3 Transposed() const
		{
			return Matrix3(m1, m4, m7, m2, m5, m8, m3, m6, m9);
		}

		std::string ToString() const
		{
			std::string str = std::to_string(v[0]);
			for (size_t i = 1; i < 9; ++i)
			{
				str += ", " + std::to_string(v[i]);
			}
			return str;
		}

		static Matrix3 MakeRotateX(float a)
		{
			return Matrix3(1, 0, 0,
				0, cosf(a), -sinf(a),
				0, sinf(a), cosf(a));
		}

		static Matrix3 MakeRotateY(float a)
		{
			return Matrix3(cosf(a), 0, -sinf(a),
				0, 1, 0,
				sinf(a), 0, cosf(a));
		}

		static Matrix3 MakeRotateZ(float a)
		{
			return Matrix3(cosf(a), sinf(a), 0,
				-sinf(a), cosf(a), 0,
				0, 0, 1);
		}
		
		static Matrix3 MakeEuler(float pitch, float yaw, float roll)
		{
			Matrix3 x = MakeRotateX(pitch);
			Matrix3 y = MakeRotateY(yaw);
			Matrix3 z = MakeRotateZ(roll);

			//order matters
			return (z * y * x);
		}

		static Matrix3 MakeScale(float xScale, float yScale, float zScale)
		{
			return Matrix3(xScale, 0.0f, 0.0f,
				0.0f, yScale, 0.0f,
				0.0f, 0.0f, zScale);
		}

		static Matrix3 MakeScale(Vector3 scale)
		{
			return MakeScale(scale.x, scale.y, scale.z);
		}


	};
	
}