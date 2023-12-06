#pragma once
#include "glm/glm.hpp"
#include "Random.h"

#define FLT_EPSILON      1.192092896e-07F 

namespace nc
{
	template <typename T>
	inline T lerp(const T& a, const T& b, float t)
	{
		return a + t * (b - a);
	}

	inline glm::vec3 cross(const glm::vec3& v1, const glm::vec3& v2)
	{
		return glm::vec3((v1.y * v2.z) - (v1.z * v2.y),
			(v1.z * v2.x) - (v1.x * v2.z),
			(v1.x * v2.y) - (v1.y * v2.x));
	}

	inline glm::vec3 randomInUnitSphere()
	{
		glm::vec3 point;

		do
		{
			point = glm::vec3{ Random::random(-1, 1), Random::random(-1, 1), Random::random(-1, 1) };
		} while (glm::length2(point) >= 1);

		return point;
	}

	inline float dot(const glm::vec3& v1, const glm::vec3& v2)
	{
		return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
	}

	inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n)
	{
		return v - 2.0f * dot(n, v) * n;
	}

	inline bool approximately(float value1, float value2)
	{
		// check if the difference between the values is less than epsilon
		return ((float)value2 - value1 < FLT_EPSILON);
	}
}