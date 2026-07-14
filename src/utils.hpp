#include "Vec4.hpp"
#include <cstdlib>
#include <iostream>
#include <cmath>

namespace ark
{
	inline float sphereSDF(Vec4 point, Vec4 center, float radius)
	{
		return (point - center).flength() - radius;
	}

	inline float smoothMin(float a, float b, float k)
	{
		
	}

	inline Vec3 rotateY(Vec3 v, float t)
	{
		float c = std::cosf(t);
		float s = std::sinf(t);
		return Vec3(v.x * c - v.z * s, v.y, v.x * s + v.z * c);
	}

	template <typename T>
	inline T blend(T a1, T a2, float t)
	{
		return a1 * (1.0f - t) + a2 * t;
	}

	inline float uniform(unsigned int seed = 0)
	{
		seed = (seed ^ 61) ^ (seed >> 16);
		seed += (seed << 3);
		seed ^= (seed >> 4);
		seed *= 0x27d4eb2d;
		seed ^= (seed >> 15);


		unsigned int hx = seed * 1103515245U;


		float x = (float)(hx & 0xFFFFFF) / 16777216.0f;


		return x;
	}

	inline float uniform(float min, float max, unsigned int seed)
	{
		return min + (max - min) * uniform(seed);
	}

	inline float pow3(float x)
	{
		return x * x * x;
	}

	inline float pow2(float x)
	{
		return x * x;
	}

	inline Vec3 v3uniform(unsigned int seed)
	{

		seed = (seed ^ 61) ^ (seed >> 16);
		seed += (seed << 3);
		seed ^= (seed >> 4);
		seed *= 0x27d4eb2d;
		seed ^= (seed >> 15);


		unsigned int hx = seed * 1103515245U;
		unsigned int hy = seed * 134775813U;
		unsigned int hz = seed * 201314235U;

		float x = (float)(hx & 0xFFFFFF) / 16777216.0f;
		float y = (float)(hy & 0xFFFFFF) / 16777216.0f;
		float z = (float)(hz & 0xFFFFFF) / 16777216.0f;

		return Vec3(x, y, z);
	}

	inline float PlaneSDF(Vec3 plane_point, Vec3 plane_normal, Vec3 point)
	{
		return std::fabsf(dot(plane_normal, point - plane_point).x);
	}

	// very simple function to turn an SDF with overestimated distance to try to bring them down and underestimate
	inline float SDFFunctionBounder(Vec3 point, Vec3 max_gradient_normal, Vec3 function_val_at_point)
	{
		// get the plane of highest gradient at function point
		// need to turn max_graident into a normal OR smt else hmm.

		return PlaneSDF(function_val_at_point, max_gradient_normal, point);
	}

	inline float SineAxisSDF(Vec3 point)
	{
		point -= Vec3(0.0f, 20.0f, 0.0f);

		if (std::fabsf(point.y) > 1.1f)
		{
			return std::fminf(std::fabsf(point.y - 1.0f), std::fabsf(point.y+1)); // 0.1f to avoid false hits
		}

		float val = std::sinf(point.x);

		Vec3 max_gradient_normal = Vec3(1.0f, 1.0f, 0.0f).cross(Vec3(0.0f, 0.0f, 1.0f)).normalized() * -1.0f;
		//max_gradient_normal = Vec3(1.9f, -1.0f, 0.0f).normalized();

	
		return SDFFunctionBounder(point, max_gradient_normal, Vec3(point.x, val, point.z));

	}



	

};