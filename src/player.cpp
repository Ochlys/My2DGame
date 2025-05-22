#include "player.hpp"

namespace GAME {

    // Constructeur de Player
    Player::Player(const float width, const float height, const sf::Color& color)
        : _playerWidth(width), _playerHeight(height), _playerColor(color) {

        _shape.setSize({_playerWidth, _playerHeight});
        
        _shape.setFillColor(color);
        
        _shape.setOrigin(_playerWidth / 2, _playerHeight / 2);

        _shape.setPosition(_position);
    }

    void Player::update(const sf::Vector2u& windowSize, const double deltaTime, const Map& map) {
        _velocity = {0.f, 0.f};
        //            X   Y

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            _velocity.x = -1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            _velocity.x = 1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            _velocity.y = -1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            _velocity.y = 1.f;
        }

        _velocity = UTILS::normalize(_velocity);
        _velocity *= (_speed * (float) deltaTime);


        sf::Vector2f newPosition = _position + sf::Vector2f(_velocity.x, 0.0f);

        if(!isValidPosition(newPosition / SQUARE_SIZE, map))
             _velocity.x = 0.0;

        newPosition = _position + _velocity;
        if(!isValidPosition(newPosition / SQUARE_SIZE, map))
            _velocity.y = 0.0;

        _position += _velocity;

        _shape.setPosition(_position);
    }

    const sf::RectangleShape& Player::getShape() {
        return _shape;
    }

    bool Player::isValidPosition(const sf::Vector2f& position, const Map& map){
        sf::Vector2f topLeft(position.x - 0.49f, position.y - 0.49f);
        sf::Vector2f topRight(position.x + 0.49f, position.y - 0.49f);
        sf::Vector2f bottomRight(position.x + 0.49f, position.y + 0.49f);
        sf::Vector2f bottomLeft(position.x - 0.49f, position.y + 0.49f);

        std::vector<sf::Vector2i> tilesOfPosition(4);
        tilesOfPosition[0] = sf::Vector2i(topLeft);
        tilesOfPosition[1] = sf::Vector2i(bottomRight);
        tilesOfPosition[2] = sf::Vector2i(topRight);
        tilesOfPosition[3] = sf::Vector2i(bottomLeft);

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
