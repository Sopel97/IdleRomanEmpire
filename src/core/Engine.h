#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>

namespace ireEngine {
struct Engine {
    Engine(sf::RenderWindow& window);

    void run();

private:
    sf::RenderWindow& m_window;
};

#endif // ENGINE_H
}
