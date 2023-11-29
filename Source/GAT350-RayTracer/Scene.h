#pragma once
#include "Color.h"
#include "Ray.h"
#include <memory>
#include "Camera.h"

namespace nc {
	class Scene
	{
	public:
		Scene() = default;
		Scene(const nc::Color::color3_t& topColor, const nc::Color::color3_t& bottomColor) :
			m_topColor{ topColor },
			m_bottomColor{ bottomColor }
		{}

		void Render(class Canvas& canvas);
		nc::Color::color3_t Trace(const ray_t& ray);

		void SetCamera(std::shared_ptr<Camera> camera) { m_camera = camera; }

	private:
		std::shared_ptr<Camera> m_camera;

		nc::Color::color3_t m_topColor{ 0 };
		nc::Color::color3_t m_bottomColor{ 1 };
	};
}