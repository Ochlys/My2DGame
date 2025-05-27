#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <string>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>
#include "defines.hpp"
#include "player.hpp"
#include "tile.hpp"
#include "utils/Camera.hpp"
#include "entity/baseEntity.hpp"
#include "entity/movingEntity.hpp"


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

        std::shared_ptr<Player> m_pPlayer;
        std::vector<std::shared_ptr<BaseEntity>> _entitys;

        sf::Texture _grassTexture;
        sf::Texture _waterTexture;
        sf::Texture _treeTexture;
        sf::Texture _sandTexture;
        sf::Sprite _grassSprite;
        sf::Sprite _treeSprite;
        sf::Sprite _sandSprite;
    };
}

#endif // __APPLICATION_HPP__
