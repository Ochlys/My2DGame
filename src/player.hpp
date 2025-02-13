#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "utils/vectors.hpp"

namespace GAME {

    class Player {
    public:
        Player(float width, float height, sf::Color color);
        void update(const sf::Vector2u window, const double deltaTime);
        const sf::RectangleShape& getShape();  // Retourner une référence au joueur

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

#endif
