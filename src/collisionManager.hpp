#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include <SFML/Graphics.hpp>

namespace GAME {
    
    struct collisionManager
    {
        sf::RectangleShape collisionShape;
        sf::Vector2f position;

        collisionManager(float x, float y, float width, float height, sf::Color color){

            position = sf::Vector2f(x,y);
            collisionShape.setPosition(position);
            collisionShape.setSize(sf::Vector2f(width, height));
            collisionShape.setFillColor(color);

        }

    };
    

};

#endif // COLLISIONMANAGER_HPP
