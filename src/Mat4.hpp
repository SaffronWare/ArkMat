#pragma once
#include <immintrin.h>
#include "Vec4.hpp"

namespace ark
{
	struct alignas(16 * 4) Mat4
	{
		union
		{
			__m128 rows[4];
			float data[16];
		};

		Mat4() : rows{ _mm_setzero_ps(), _mm_setzero_ps(), _mm_setzero_ps(), _mm_setzero_ps() } {}

		static Mat4 identity()
		{
			Mat4 mat;
			mat.rows[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
			mat.rows[1] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
			mat.rows[2] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
			mat.rows[3] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);
			return mat;
		}

	};

	

	
}