#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <SFML/Graphics.hpp>
#include "utils/vectors.hpp"
#include "tile.hpp"
#include <cstdlib> 

namespace GAME {
    typedef std::vector<std::vector<Tile>> Map;

    class Entity {
    public:
        Entity(float width, float height, const sf::Color& color);

        static bool isValidPosition(const sf::Vector2f& position, const Map& map);

        void update(double deltaTime, const Map& map);

        const sf::RectangleShape& getShape() const;

    private:

        float               _entityWidth;
        float               _entityHeight;

        sf::Vector2f        _position = {600.f, 400.f};
        sf::RectangleShape  _shape;
        sf::Color           _entityColor;
        sf::Vector2f        _velocity;
    
        float               _speedX;
        float               _speedY;
        float               _timer;

    };

}

#endif // __ENTITY_HPP__
