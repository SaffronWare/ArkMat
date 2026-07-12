
#pragma once
#include <immintrin.h>

namespace ark
{
	struct Vec3;

	inline Vec3 rsqrt(Vec3 v);

	inline Vec3 dot(Vec3 v1, Vec3 v2);

	inline float fdot(Vec3 v1, Vec3 v2);

	inline Vec3 sqrt(Vec3 v);

	inline float fsqrt(Vec3 v);

	struct alignas(16) Vec3
	{
		union
		{
			struct {
				float x, y, z;
			};

			float data[3];
			__m128 reg;
		};

		Vec3() : reg(_mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f)) {}

		Vec3(float scalar) : reg(_mm_set1_ps(scalar)) {}

		Vec3(float x, float y, float z = 0.0f) : reg(_mm_set_ps(0.0f, z, y, x)) {}

		Vec3 length_squared() const
		{
			return dot(*this, *this);
		}

		Vec3 length() const
		{
			return sqrt(length_squared());
		}

		float flength_squared() const
		{
			return length_squared().x;
		}

		float flength() const
		{
			return length().x;
		}

		Vec3& normalize()
		{
			*this *= rsqrt(length_squared());
			return *this;
		}

		Vec3 normalized() const
		{
			return *this * rsqrt(length_squared());
		}

		Vec3 cross(Vec3 other) const
		{
			Vec3 crossed;
			// note to self, shuffle says ok which element from vector 1 to put in last lane, then which from 1 in before last, then which from 2 in second, etc..

			__m128 vs1 = _mm_shuffle_ps(this->reg, this->reg, _MM_SHUFFLE(3, 0, 2, 1));
			__m128 us1 = _mm_shuffle_ps(other.reg, other.reg, _MM_SHUFFLE(3, 1, 0, 2));
			__m128 r1 = _mm_mul_ps(vs1, us1);
			__m128 vs2 = _mm_shuffle_ps(this->reg, this->reg, _MM_SHUFFLE(3, 1, 0, 2));
			__m128 us2 = _mm_shuffle_ps(other.reg, other.reg, _MM_SHUFFLE(3, 0, 2, 1));
			__m128 r2 = _mm_mul_ps(vs2, us2);
			crossed.reg = _mm_sub_ps(r1, r2);
			return crossed;
		}

		Vec3& operator+=(Vec3 other)
		{
			reg = _mm_add_ps(reg, other.reg);
			return *this;
		}

		Vec3 operator+(Vec3 other) const
		{
			Vec3 res;
			res.reg = _mm_add_ps(reg, other.reg);
			return res;
		}

		Vec3& operator-=(Vec3 other)
		{
			reg = _mm_sub_ps(reg, other.reg);
			return *this;
		}

		Vec3 operator-(Vec3 other) const
		{
			Vec3 res;
			res.reg = _mm_sub_ps(reg, other.reg);
			return res;
		}

		Vec3& operator*=(Vec3 other)
		{
			reg = _mm_mul_ps(reg, other.reg);
			return *this;
		}

		Vec3 operator*(Vec3 other) const
		{
			Vec3 res;
			res.reg = _mm_mul_ps(reg, other.reg);
			return res;
		}

		Vec3& operator/=(Vec3 other)
		{
			reg = _mm_div_ps(reg, other.reg);
			return *this;
		}

		Vec3 operator/(Vec3 other) const
		{
			Vec3 res;
			res.reg = _mm_div_ps(reg, other.reg);
			return res;
		}

		Vec3& operator*=(float other)
		{
			__m128 scalar_reg = _mm_set1_ps(other);
			reg = _mm_mul_ps(reg, scalar_reg);
			return *this;
		}

		Vec3 operator*(float other) const
		{
			Vec3 res;
			__m128 scalar_reg = _mm_set1_ps(other);
			res.reg = _mm_mul_ps(reg, scalar_reg);
			return res;
		}

		Vec3& operator/=(float other)
		{
			return this->operator*=(1.0f / other);
		}

		Vec3 operator/(float other) const
		{
			return this->operator*(1.0f / other);
		}

	};

	inline Vec3 dot(Vec3 v1, Vec3 v2)
	{
		Vec3 res;
		// gonna use 0111 0111 mask to get the dot product of xyz and onyl store to xyz, w will be 0
		// 0111 0111 is equivalent to 1+2+4 which is 7, so 0x77
		res.reg = _mm_dp_ps(v1.reg, v2.reg, 0x77);
		return res;
	}

	inline float fdot(Vec3 v1, Vec3 v2)
	{
		return dot(v1, v2).x;
	}

	inline Vec3 sqrt(Vec3 v)
	{
		Vec3 res;
		res.reg = _mm_sqrt_ps(v.reg);
		return res;
	}

	inline float fsqrt(Vec3 v)
	{
		Vec3 res;
		res.reg = _mm_sqrt_ps(v.reg);
		return res.x;
	}

	inline Vec3 rsqrt(Vec3 v)
	{
		Vec3 res;
		res.reg = _mm_rsqrt_ps(v.reg);
		return res;
	}

};