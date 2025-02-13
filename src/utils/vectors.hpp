#ifndef __VECTORS_HPP__
#define __VECTORS_HPP__

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace UTILS {
    inline sf::Vector2f normalize(const sf::Vector2f& vector) {
        float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
        if (length != 0) {
            return sf::Vector2f(vector.x / length, vector.y / length);
        }
        return sf::Vector2f(0.f, 0.f);
    }
}

#endif // __VECTOR_HPP__    