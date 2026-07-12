#include "Vec4.hpp"

namespace ark
{
	inline float sphereSDF(const Vec4& point, const Vec4& center, float radius)
	{
		return (point - center).flength() - radius;
	}

	inline float smoothMin(float a, float b, float k)
	{
		
	}
};