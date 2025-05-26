#ifndef __TILE_HPP__
#define __TILE_HPP__

#include <SFML/Graphics.hpp>
#include "defines.hpp"

namespace GAME {

    struct Tile {
        bool IsTraversable;
        sf::Color Color;
        
        sf::RectangleShape Shape = sf::RectangleShape(SQUARE_SIZE2);
        sf::Vector2i Position = sf::Vector2i(0, 0);

        bool operator==(const Tile& other) const {
            return Color == other.Color && IsTraversable == other.IsTraversable;
        }

        static const Tile Grass;
        static const Tile Water;
        static const Tile Sand;
        static const Tile Tree;
        static const Tile Void;
    };

    inline const Tile Tile::Grass = {true, sf::Color::White};
    inline const Tile Tile::Water = {false, sf::Color::White};
    inline const Tile Tile::Sand = {true, sf::Color::Yellow};
    inline const Tile Tile::Void = {false, sf::Color::Black};
    inline const Tile Tile::Tree = {false, sf::Color::Red};
}

#endif // TILE_HPP