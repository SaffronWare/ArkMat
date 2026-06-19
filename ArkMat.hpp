#pragma once
#include <immintrin.h>

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

	Vec4  operator-(const Vec4& other) const
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
		return this->operator*=(1.0f/other);
	}

	Vec4 operator/(float other) const
	{
		return this->operator*(1.0f / other);
	}
};

inline Vec4 vdot(const Vec4& v1, const Vec4& v2)
{
	Vec4 res;
	res.reg = _mm_mul_ps(v1.reg, v2.reg); 

	__m128 shuffled = _mm_shuffle_ps(res.reg, res.reg, _MM_SHUFFLE(1, 0, 3, 2));
	res.reg = _mm_add_ps(res.reg, shuffled); 
	shuffled = _mm_shuffle_ps(res.reg, res.reg, _MM_SHUFFLE(2, 3, 0, 1)); 
	res.reg = _mm_add_ps(res.reg, shuffled);
	return res;
}

inline Vec4 vadot(const Vec4& v1, const Vec4& v2)
{
	Vec4 res;
	res.reg = _mm_mul_ps(v1.reg, v2.reg);

	res.reg = _mm_hadd_ps(res.reg, res.reg); 
	res.reg = _mm_hadd_ps(res.reg, res.reg);
	return res;
}

inline Vec4 vdotp(const Vec4& v1, const Vec4& v2)
{
	Vec4 res;
	res.reg = _mm_dp_ps(v1.reg, v2.reg, 0xFF);
	return res;
}

inline float cdot(const Vec4& v1, const Vec4& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}




