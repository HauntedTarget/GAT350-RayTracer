#pragma once
#include "Color.h"
#include <vector>

struct SDL_Texture;

namespace nc
{
    class Canvas
    {
    public:
        Canvas(int width, int height, const class Renderer& renderer);
        ~Canvas();

        void Update();

        void Clear(const Color::color4_t& color);
        void DrawPoint(const glm::ivec2& point, const Color::color4_t& color);

        glm::vec2 GetSize() const { return m_size; }

        friend class Renderer;

    private:
        SDL_Texture* m_texture{ nullptr };
        std::vector<Color::rgba_t> m_buffer;

        glm::ivec2 m_size{ 0 };
    };
}