#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "player.hpp"

namespace GAME {

    class Application {
    public:
        Application(std::string name, int width, int height);
        void run();
    
    private:
        void _initGrid(const int sizeX, const int sizeY );


    private:
        const std::string _name;
        int               _width;
        int               _height;

        const double    _fps        = 60.0;
        const bool      _limitFps   = false;
    
        sf::RenderWindow* _window = nullptr;

        std::vector<std::vector<sf::RectangleShape>> _grid;
        
        const float     _squareSize     = 50.f; 
        const sf::Color _squareColor    = sf::Color::Red;
        const sf::Color _squareColor2   = sf::Color::Magenta;

        Player      _player;
    };
}

#endif // __APPLICATION_HPP__
