#include "TiledTopDownSurface.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include <cmath>
#include <cstdlib>

#include <iostream>

namespace ire::core::world
{

    TiledTopDownSurface::TiledTopDownSurface(int width, int height) :
        m_width(width),
        m_height(height),
        m_tiles(width, height),
        m_gridPoints(width + 1, height + 1)
    {
        generateRandomWorld();
    }

    void TiledTopDownSurface::draw(sf::RenderTarget& target)
    {
        constexpr float cameraAngleDeg = 60.0f;

        const float pi = 3.14159265358979323846f;
        const float degToRad = (2.0f * pi / 360.0f);
        const float cameraAngleRad = cameraAngleDeg * degToRad;
        const float verticalSqueeze = std::sin(cameraAngleRad);

        const auto oldView = target.getView();
        const float oldViewportWidth = target.getViewport(oldView).width;
        const float oldViewportHeight = target.getViewport(oldView).height;
        const float aspectRatio = oldViewportWidth / oldViewportHeight;

        sf::View surfaceView;
        surfaceView.setCenter(m_width/2.0f, m_height/2.0f);
        surfaceView.setSize(m_height * aspectRatio * verticalSqueeze, m_height);
        surfaceView.setViewport(oldView.getViewport());
        surfaceView.zoom(1.0f);
        target.setView(surfaceView);

        drawGround(target);

        target.setView(oldView);
    }

    void TiledTopDownSurface::generateRandomWorld()
    {
        for (int x = 0; x < m_width; ++x)
        {
            for (int y = 0; y < m_height; ++y)
            {
                m_tiles(x, y) = TopDownGroundTile(sf::Color(rand(), rand(), rand()));
            }
        }

        util::Array2<float> elevation(m_width + 3, m_height + 3);
        for (int x = 0; x < m_width + 3; ++x)
        {
            for (int y = 0; y < m_height + 3; ++y)
            {
                elevation(x, y) = rand() % 20 / 10.0f;
            }
        }

        for (int x = 0; x < m_width + 1; ++x)
        {
            for (int y = 0; y < m_height + 1; ++y)
            {
                float sum = 0.0f;
                for (int xx = 0; xx < 2; ++xx)
                {
                    for (int yy = 0; yy < 2; ++yy)
                    {
                        sum += elevation(x + xx, y + yy);
                    }
                }
                m_gridPoints(x, y) = TopDownGridPoint(sum / 9.0f);
            }
        }
    }

    void TiledTopDownSurface::drawGround(sf::RenderTarget& target)
    {
        sf::VertexArray va(sf::PrimitiveType::Quads);
        for (int x = 0; x < m_width; ++x)
        {
            for (int y = 0; y < m_height; ++y)
            {
                const auto position = sf::Vector2f(x, y);
                //const auto color = m_tiles(x, y).getTint();
                const auto normal = getGridPointNormal(x, y);
                const auto color = sf::Color(normal.x * 127 + 127, normal.y * 127 + 127, normal.z * 127 + 127);
                const auto topLeftElevation = m_gridPoints(x, y).getElevation();
                const auto topRightElevation = m_gridPoints(x+1, y).getElevation();
                const auto bottomRightElevation = m_gridPoints(x+1, y+1).getElevation();
                const auto bottomLeftElevation = m_gridPoints(x, y+1).getElevation();
                va.append(sf::Vertex(position + sf::Vector2f(0.0f, 0.0f - topLeftElevation), color));
                va.append(sf::Vertex(position + sf::Vector2f(1.0f, 0.0f - topRightElevation), color));
                va.append(sf::Vertex(position + sf::Vector2f(1.0f, 1.0f - bottomRightElevation), color));
                va.append(sf::Vertex(position + sf::Vector2f(0.0f, 1.0f - bottomLeftElevation), color));
            }
        }
        target.draw(va);
    }

    [[nodiscard]] sf::Vector3f TiledTopDownSurface::getGridPointNormal(int x, int y) const
    {
        sf::Vector3f x0(std::max(0, x - 1), y, m_gridPoints(std::max(0, x - 1), y).getElevation());
        sf::Vector3f x1(std::min(m_width, x + 1), y, m_gridPoints(std::min(m_width, x + 1), y).getElevation());
        sf::Vector3f y0(x, std::max(0, y - 1), m_gridPoints(x, std::max(0, y - 1)).getElevation());
        sf::Vector3f y1(x, std::min(m_height, y + 1), m_gridPoints(x, std::min(m_height, y + 1)).getElevation());
        sf::Vector3f a = x1 - x0;
        sf::Vector3f b = y1 - y0;
        sf::Vector3f normal(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
        float mag = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
        return normal / mag;
    }

}