
#pragma once
#include <immintrin.h>

namespace ark
{
	struct Vec4;

	inline Vec4 dot(const Vec4& v1, const Vec4& v2);

	inline float fdot(const Vec4& v1, const Vec4& v2);

	inline Vec4 sqrt(const Vec4& v);

	inline float fsqrt(const Vec4& v);

	struct alignas(16) Vec4
	{
		union
		{
			struct {
				float x, y, z, w;
			};
			float data[4];
			__m128 reg;
		};

		Vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) : x(x), y(y), z(z), w(w) {}

		Vec4 length_squared() const
		{
			return dot(*this, *this);
		}

		Vec4 length() const
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

		Vec4& normalize()
		{
			*this /= length();
			return *this;
		}

		Vec4 normalized()
		{
			return *this / length();
		}

		Vec4& operator+=(const Vec4& other)
		{
			reg = _mm_add_ps(reg, other.reg);
			return *this;
		}

		Vec4 operator+(const Vec4& other) const
		{
			Vec4 res;
			res.reg = _mm_add_ps(reg, other.reg);
			return res;
		}

		Vec4& operator-=(const Vec4& other)
		{
			reg = _mm_sub_ps(reg, other.reg);
			return *this;
		}

		Vec4 operator-(const Vec4& other) const
		{
			Vec4 res;
			res.reg = _mm_sub_ps(reg, other.reg);
			return res;
		}

		Vec4& operator*=(const Vec4& other)
		{
			reg = _mm_mul_ps(reg, other.reg);
			return *this;
		}

		Vec4 operator*(const Vec4& other) const
		{
			Vec4 res;
			res.reg = _mm_mul_ps(reg, other.reg);
			return res;
		}

		Vec4& operator/=(const Vec4& other)
		{
			reg = _mm_div_ps(reg, other.reg);
			return *this;
		}

		Vec4 operator/(const Vec4& other) const
		{
			Vec4 res;
			res.reg = _mm_div_ps(reg, other.reg);
			return res;
		}

		Vec4& operator*=(float other)
		{
			__m128 scalar_reg = _mm_set1_ps(other);
			reg = _mm_mul_ps(reg, scalar_reg);
			return *this;
		}

		Vec4 operator*(float other) const
		{
			Vec4 res;
			__m128 scalar_reg = _mm_set1_ps(other);
			res.reg = _mm_mul_ps(reg, scalar_reg);
			return res;
		}

		Vec4& operator/=(float other)
		{
			return this->operator*=(1.0f / other);
		}

		Vec4 operator/(float other) const
		{
			return this->operator*(1.0f / other);
		}

	};

	inline Vec4 dot(const Vec4& v1, const Vec4& v2)
	{
		Vec4 res;
		res.reg = _mm_dp_ps(v1.reg, v2.reg, 0xFF);
		return res;
	}

	inline float fdot(const Vec4& v1, const Vec4& v2)
	{
		return dot(v1, v2).x;
	}

	inline Vec4 sqrt(const Vec4& v)
	{
		Vec4 res;
		res.reg = _mm_sqrt_ps(v.reg);
		return res;
	}

	inline float fsqrt(const Vec4& v)
	{
		Vec4 res;
		res.reg = _mm_sqrt_ps(v.reg);
		return res.x;
	}

	
};