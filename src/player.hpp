#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <SFML/Graphics.hpp>
#include "utils/vectors.hpp"
#include "tile.hpp"

namespace GAME {
    typedef std::vector<std::vector<Tile>> Map;

    class Player {
    public:
        Player(const float width, const float height, const sf::Color& color);
        void update(const sf::Vector2u& windowSize, const double deltaTime, const Map& map);
        const sf::RectangleShape& getShape();
        static bool isValidPosition(const sf::Vector2f& position, const Map& map);

    private:
        /* Paramètre */
        float       _playerWidth;
        float       _playerHeight;

        sf::Vector2f _position = {150.f, 200.f};

        /* Affichage */
        sf::RectangleShape  _shape;
        sf::Color           _playerColor;

        /* Physique */
        sf::Vector2f _velocity;

        const float _speed = 150.f;
    };

}

#endif // __PLAYER_HPP__
