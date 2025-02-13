#include "player.hpp"

namespace GAME {

    // Constructeur de Player
    Player::Player(float width, float height, sf::Color color)
        : _playerWidth(width), _playerHeight(height), _playerColor(color) {

        _shape.setSize({_playerWidth, _playerHeight});
        
        _shape.setFillColor(color);
        
        _shape.setOrigin(_playerWidth / 2, _playerHeight / 2);

        _shape.setPosition(_position);
    }

    void Player::update(const sf::Vector2u windowSize, const double deltaTime) {
        _velocity = {0.f, 0.f};
        //            X   Y

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            _velocity.x = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            _velocity.x = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            _velocity.y = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            _velocity.y = 1;
        }

        _velocity = UTILS::normalize(_velocity);
        _velocity *= (_speed * (float) deltaTime);

        _position += _velocity;

        if (_position.x < 0) {
            _position.x = 0;
        }
        if (_position.y < 0) {
            _position.y = 0;
        }
        if (_position.x > windowSize.x) {
            _position.x = windowSize.x;
        }
        if (_position.y > windowSize.y) {
            _position.y = windowSize.y;
        }

        _shape.setPosition(_position);
    }

    const sf::RectangleShape& Player::getShape() {
        return _shape;
    }

}
