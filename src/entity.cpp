#include "entity.hpp"
#include <iostream>

namespace GAME {

    Entity::Entity(float width, float height, const sf::Color& color)
    : _entityWidth(width), _entityHeight(height), _entityColor(color), _speedX(SQUARE_SIZE), _speedY(SQUARE_SIZE) {
        _shape.setSize({_entityWidth, _entityHeight});
        _shape.setFillColor(color);
        _shape.setPosition(_position);
    }

    void Entity::update(double deltaTime, const Map& map) {
        _timer += deltaTime;
        if (_timer >= 3.f + static_cast<float>(std::rand() % 3)) {
            int direction = std::rand() % 4;  // 0 = gauche, 1 = droite, 2 = haut, 3 = bas
            switch (direction) {
                case 0: // gauche
                    _speedX = -SQUARE_SIZE;
                    _speedY = 0.f;
                    break;
                case 1: // droite
                    _speedX = SQUARE_SIZE;
                    _speedY = 0.f;
                    break;
                case 2: // haut
                    _speedX = 0.f;
                    _speedY = -SQUARE_SIZE;
                    break;
                case 3: // bas
                    _speedX = 0.f;
                    _speedY = SQUARE_SIZE;
                    break;
            }
            _timer = 0.f;
        }
    
        sf::Vector2f newPosition = _shape.getPosition() + sf::Vector2f(_speedX * deltaTime, _speedY * deltaTime);
        
        if (isValidPosition(newPosition, map)) {
            _shape.move(_speedX * deltaTime, _speedY * deltaTime);
        }
    }

    const sf::RectangleShape& Entity::getShape() const {
        return _shape;
    }

    bool Entity::isValidPosition(const sf::Vector2f& position, const Map& map) {

        int topLeftX = (position.x / SQUARE_SIZE);
        int topLeftY = (position.y / SQUARE_SIZE);
        int bottomRightX = ((position.x + SQUARE_SIZE) / SQUARE_SIZE);
        int bottomRightY = ((position.y + SQUARE_SIZE) / SQUARE_SIZE);
    

        if (topLeftX < 0 || topLeftY < 0 || bottomRightX >= map.size() || bottomRightY >= map[0].size()) {
            return false;
        }
    
        for (int x = topLeftX; x <= bottomRightX; ++x) {
            for (int y = topLeftY; y <= bottomRightY; ++y) {
                if (bottomRightX >= map.size() || bottomRightY >= map[0].size()) {
                    return false;
                }
                if (topLeftX < 0 || topLeftY < 0) {
                    return false;
                }
                if (!map[x][y].IsTraversable) {
                    return false;
                }
            }
        }
    
        return true;
    }
    
}
