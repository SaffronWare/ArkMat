#include "Vec4.hpp"
#include <cstdlib>

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
	inline T blend(T a1, T a2, float t)
	{
		return a1 * (1.0f - t) + a2 * t;
	}

	float uniform(unsigned int seed = 0)
	{
		srand(seed);
		return rand() / static_cast<float>(RAND_MAX);
	}

	float uniform(float min, float max, unsigned int seed)
	{
		return min + (max - min) * uniform(seed);
	}

};