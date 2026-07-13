#include "Vec4.hpp"

namespace ark
{
	inline float sphereSDF(Vec4 point, Vec4 center, float radius)
	{
		return (point - center).flength() - radius;
	}

	inline float smoothMin(float a, float b, float k)
	{
		
	}

	template <typename T>
	inline float blend(T a1, T a2, float t)
	{
		return a1 * (1.0f - t) + a2 * t;
	}
};