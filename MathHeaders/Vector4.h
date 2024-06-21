#pragma once
#include <string>
#include <cmath>

namespace MathClasses
{
	struct Vector4
	{
		union
		{
			struct { float x, y, z, w; };
			//struct { float r, g, b; };
			float data[4];
		};

		Vector4() : x{ 0 }, y{ 0 }, z{ 0 }, w { 0 }
		{
		}

		Vector4(float X, float Y, float Z, float W) : x{ X }, y{ Y }, z{ Z }, w { W }
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
		Vector4 operator +(const Vector4& rhs) const
		{
			Vector4 sum;

			//x is the LEFT vectors x-component
			//rhs.x is the RIGHT vectors x-component
			sum.x = x + rhs.x;
			sum.y = y + rhs.y;
			sum.z = z + rhs.z;
			sum.w = w + rhs.w;

			return sum;
		}

		Vector4 operator -(const Vector4& rhs) const
		{
			Vector4 diff;

			diff.x = x - rhs.x;
			diff.y = y - rhs.y;
			diff.z = z - rhs.z;
			diff.w = w - rhs.w;

			return diff;
		}

		//if scalar is two, vector would be doubled. (2, 4, -2) becomes (4, 8, -4) 
		Vector4 operator *(const float& scalar) const
		{
			Vector4 scaled;

			scaled.x = x * scalar;
			scaled.y = y * scalar;
			scaled.z = z * scalar;
			scaled.w = w * scalar;

			return scaled;
		}

		friend Vector4 operator*(const float& lhs, const Vector4& rhs)
		{
			return rhs * lhs;
		}

		Vector4 operator /(const float& div) const
		{
			Vector4 quot;

			quot.x = x / div;
			quot.y = y / div;
			quot.z = z / div;
			quot.w = w / div;

			return quot;
		}

		void operator +=(const Vector4& rhs)
		{
			x = x + rhs.x;
			y = y + rhs.y;
			z = z + rhs.z;
			w = w + rhs.w;

		}

		void operator -=(const Vector4& rhs)
		{
			x = x - rhs.x;
			y = y - rhs.y;
			z = z - rhs.z;
			w = w - rhs.w;
		}


		Vector4 operator *=(const float& scalar)
		{
			x = x * scalar;
			y = y * scalar;
			z = z * scalar;
		}

		void operator /=(const Vector4& rhs)
		{
			x = x / rhs.x;
			y = y / rhs.y;
			z = z / rhs.z;
			w = w / rhs.w;
		}

		bool operator == (const Vector4& rhs) const
		{
			float xDist = fabsf(x - rhs.x);
			float yDist = fabsf(y - rhs.y);
			float zDist = fabsf(z - rhs.z);
			float wDist = fabsf(w - rhs.w);

			const float THRESHOLD = 0.00001f;

			return xDist < THRESHOLD && yDist < THRESHOLD && zDist < THRESHOLD && wDist < THRESHOLD;
		}

		bool operator !=(const Vector4& rhs) const
		{
			return !(*this == rhs);
		}

		std::string ToString() const
		{
			return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w);
		}

		//length of a vector
		float Magnitude() const
		{
			//return square root of all values to the power of 2 (distance formula pythag)
			return sqrtf(x * x + y * y + z * z + w * w);
		}

		//doesn't return actual distance, only used to determine if farther than another call of this function. redundant imo
		float MagnitudeSqr() const
		{
			return x * x + y * y + z * z + w * w;
		}

		//distance between points. "The offset between two Points can be found by subtracting one Point from the other. 
		// The magnitude of the resulting Vector represents the distance between them."
		/*static float Distance(const Vector4& start, const Vector4& end)
		{
			return (*this - other).Magnitude();
		}*/

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
			w /= m;
		}

		//Returns a normalised copy of the vector
		Vector4 Normalised() const
		{
			Vector4 copy = *this;
			copy.Normalise();

			return copy;
		}

		//Dot and cross product

		//dot returns difference in angle. 1 
		float Dot(const Vector4& other)
		{
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}

		Vector4 Vector4::Cross(const Vector4& other)
		{
			return Vector4(y * other.z - z * other.y,
				z * other.x - x * other.z,
				x * other.y - y * other.x,
				0);
		}

		float AngleBetween(const Vector4& other) const
		{
			//normalise the vectors
			Vector4 a = Normalised();
			Vector4 b = other.Normalised();

			//calculate the dot product
			float d = a.Dot(other);

			//return the angle between them
			return acosf(d);
		}
	};
};