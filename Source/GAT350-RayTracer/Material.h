#pragma once
#include "Ray.h"
#include "Color.h"

namespace nc
{
	class Material
	{
	public:
		virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, Color::color3_t& color, ray_t& scattered) const = 0;
	};

	class Lambertian : public Material
	{
	public:
		Lambertian(const Color::color3_t& albedo) : m_albedo{ albedo } {}
		bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, Color::color3_t& color, ray_t& scattered) const
		{
			color = m_albedo;
			return true;
		}

	protected:
		Color::color3_t m_albedo;
	};
}