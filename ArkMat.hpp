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


