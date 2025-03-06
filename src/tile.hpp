#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include "collisionManager.hpp"

namespace GAME {

    enum class TileType { Grass, Water, Sand };

    struct Tile {
        sf::RectangleShape shape;
        TileType type;
        collisionManager collision;

        Tile(float size, TileType tiletype) : type(tiletype), collision(0, 0, size, size, sf::Color::Black) {
            shape.setSize(sf::Vector2f(size, size));

            if (type == TileType::Grass)
                shape.setFillColor(sf::Color::Green);
            else if (type == TileType::Sand)
                shape.setFillColor(sf::Color::Yellow);
            else
                shape.setFillColor(sf::Color::Blue);
        }
    };

}


#endif // TILE_HPP