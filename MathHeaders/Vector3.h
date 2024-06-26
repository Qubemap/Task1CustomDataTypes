#pragma once
#include <string>
#include <cmath>

namespace MathClasses
{
	struct Vector3
	{
		union
		{
			struct { float x, y, z; };	// 12-bytes
			struct { float r, g, b; };	// 12-bytes
			float data[3];				// 12-bytes
		};

		Vector3() : x{ 0 }, y{ 0 }, z{ 0 }
		{
		}

		Vector3(float X, float Y, float Z) : x{ X }, y{ Y }, z{ Z }
		{
		}

		float& operator [](int dim)
		{
			return data[dim];
		}

		const float& operator [](int dim) const
		{
			return data[dim];
		}

		operator float* () { return data; }

		operator const float* () const { return data; }

		//adding vector (0, 2, 0) to another would shift the point up two units for example
		Vector3 operator +(const Vector3& rhs) const
		{
			Vector3 sum;

			//x is the LEFT vectors x-component
			//rhs.x is the RIGHT vectors x-component
			sum.x = x + rhs.x;
			sum.y = y + rhs.y;
			sum.z = z + rhs.z;

			return sum;
		}

		Vector3 operator -(const Vector3& rhs) const
		{
			Vector3 diff;

			diff.x = x - rhs.x;
			diff.y = y - rhs.y;
			diff.z = z - rhs.z;

			return diff;
		}

		//if scalar is two, vector would be doubled. (2, 4, -2) becomes (4, 8, -4) 
		Vector3 operator *(const float& scalar) const
		{
			Vector3 scaled;

			scaled.x = x * scalar;
			scaled.y = y * scalar;
			scaled.z = z * scalar;

			return scaled;
		}

		friend Vector3 operator*(const float& lhs, const Vector3& rhs)
		{
			return rhs * lhs;
		}

		Vector3 operator /(const float& div) const
		{
			Vector3 quot;

			quot.x = x / div;
			quot.y = y / div;
			quot.z = z / div;

			return quot;
		}

		void operator +=(const Vector3& rhs)
		{
			x = x + rhs.x;
			y = y + rhs.y;
			z = z + rhs.z;
		}

		void operator -=(const Vector3& rhs)
		{
			x = x - rhs.x;
			y = y - rhs.y;
			z = z - rhs.z;
		}

		
		Vector3 operator *=(const float& scalar)
		{
			x = x * scalar;
			y = y * scalar;
			z = z * scalar;
		}

		void operator /=(const Vector3& rhs)
		{
			x = x / rhs.x;
			y = y / rhs.y;
			z = z / rhs.z;
		}

		bool operator == (const Vector3& rhs) const
		{
			float xDist = fabsf(x - rhs.x);
			float yDist = fabsf(y - rhs.y);
			float zDist = fabsf(z - rhs.z);

			const float THRESHOLD = 0.00001f;

			return xDist < THRESHOLD && yDist < THRESHOLD && zDist < THRESHOLD;
		}

		bool operator !=(const Vector3& rhs) const
		{
			return !(*this == rhs);
		}

		std::string ToString() const
		{
			return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
		}

		//length of a vector
		float Magnitude() const
		{
			//return square root of all values to the power of 2 (distance formula pythag)
			return sqrtf(x * x + y * y + z * z);
		}

		//doesn't return actual distance, only used to determine if farther than another call of this function.
		float MagnitudeSqr() const
		{
			return x * x + y * y + z * z;
		}

		//Normalises the Vector (sets magnitude to 1 unit). think the 3 colored arrows in 3d software
		void Normalise()
		{
			float m = Magnitude();

			if (m == 0)
			{
				x = 0;
				y = 0;
				z = 0;
				return;
			}

			x /= m;
			y /= m;
			z /= m;
		}

		//Returns a normalised copy of the vector
		Vector3 Normalised() const
		{
			Vector3 copy = *this;
			copy.Normalise();

			return copy;
		}

		//Dot and cross product

		//dot returns difference in angle. 1 
		float Dot(const Vector3& other)
		{
			return x * other.x + y * other.y + z * other.z;
		}

		Vector3 Vector3::Cross(const Vector3& other)
		{
			return Vector3(y * other.z - z * other.y,
				z * other.x - x * other.z,
				x * other.y - y * other.x);
		}

		float AngleBetween(const Vector3& other) const
		{
			//normalise the vectors
			Vector3 a = Normalised();
			Vector3 b = other.Normalised();

			//calculate the dot product
			float d = a.Dot(other);

			//return the angle between them
			return acosf(d);
		}
	};
};