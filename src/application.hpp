#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "defines.hpp"
#include "player.hpp"
#include "tile.hpp"


namespace GAME {
    typedef std::vector<std::vector<Tile>> Map;

    class Application {
    public:
        Application(const std::string& name, const int width, const int height);
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

        Map _grid;

        Player _player;
    };
}

#endif // __APPLICATION_HPP__
