#include "entity.hpp"
#include <iostream>

namespace GAME {

    Entity::Entity(float width, float height, const sf::Color& color)
    : _entityWidth(width), _entityHeight(height), _entityColor(color), _speedX(SQUARE_SIZE), _speedY(SQUARE_SIZE) {
        _shape.setSize({_entityWidth, _entityHeight});
        _shape.setFillColor(color);
        _shape.setPosition(_position);
        _shape.setOrigin(_entityWidth / 2, _entityHeight / 2);
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

        //calcul des coins >:(
        sf::Vector2f topLeft((position.x - 0.49f * SQUARE_SIZE) / SQUARE_SIZE, (position.y - 0.49f * SQUARE_SIZE) / SQUARE_SIZE);
        sf::Vector2f topRight((position.x + 0.49f * SQUARE_SIZE) / SQUARE_SIZE, (position.y - 0.49f * SQUARE_SIZE) / SQUARE_SIZE);
        sf::Vector2f bottomRight((position.x + 0.49f * SQUARE_SIZE) / SQUARE_SIZE, (position.y + 0.49f * SQUARE_SIZE) / SQUARE_SIZE);
        sf::Vector2f bottomLeft((position.x - 0.49f * SQUARE_SIZE) / SQUARE_SIZE, (position.y + 0.49f * SQUARE_SIZE) / SQUARE_SIZE);

        //conversion des coins en int ?
        std::vector<sf::Vector2i> tilesOfPosition(4);
        tilesOfPosition[0] = sf::Vector2i(topLeft);
        tilesOfPosition[1] = sf::Vector2i(bottomRight);
        tilesOfPosition[2] = sf::Vector2i(topRight);
        tilesOfPosition[3] = sf::Vector2i(bottomLeft);

        //vérification
                for(sf::Vector2i& tile : tilesOfPosition){
            if(tile.x >= map.size() || tile.y >= map[0].size())
                return false;
            if(tile.x < 0 || tile.y < 0)
                return false;
            if(!map[tile.x][tile.y].IsTraversable){
                return false;
            }
        }
        return true;

    }

    
}
