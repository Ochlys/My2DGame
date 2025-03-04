#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>

namespace GAME {

    enum class TileType { Grass, Water };

    struct Tile {
        sf::RectangleShape shape;
        TileType type;

        Tile(float size, TileType tiletype) : type(tiletype){
            shape.setSize(sf::Vector2f(size, size));

            if (type == TileType::Grass)
                shape.setFillColor(sf::Color::Green);
            else
                shape.setFillColor(sf::Color::Blue);

        }

    };
}

#endif // TILE_HPP