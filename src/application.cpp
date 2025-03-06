#include "application.hpp"
#include "player.hpp"
#include "tile.hpp"
#include "collisionManager.hpp"

namespace GAME {

    Application::Application(std::string name, int width, int height) :
    _name(name), _width(width), _height(height), 
    _player(50.f, 50.f, sf::Color::Red)
    {
        _window = new sf::RenderWindow(sf::VideoMode(_width, _height), _name);

        std::cout << "Application initialisée."
        << std::endl << "SFML version: " 
        << SFML_VERSION_MAJOR << "." 
        << SFML_VERSION_MINOR << "." 
        << SFML_VERSION_PATCH 
        << std::endl;

        _initGrid(50, 50); 
    }

    void Application::run() {
        std::cout << "Lancement de l'application." << std::endl;
        
        const sf::RectangleShape& playerShape = _player.getShape();

        sf::Clock clock;
        const double frameTime = 1.0 / _fps; 
        double deltaTime = 0.0; 
        
        while (_window->isOpen()) {
            sf::Event event;
            while (_window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    _window->close();
            }            

            // Horloge
            deltaTime = clock.restart().asSeconds();
            if (_limitFps && deltaTime < frameTime) {
                sf::sleep(sf::seconds(frameTime - deltaTime)); 
                deltaTime = frameTime;
            }
            float fps = 1.f / deltaTime;
            std::cout << "FPS: " << fps << std::endl;

            // Mises à jours
            _player.update(_window->getSize(), deltaTime);

            // AFFICHAGES

            _window->clear();

            //Grille
            for (int x = 0; x < _grid.size(); x++) {
                for (int y = 0; y < _grid[0].size(); y++) {
                    _window->draw(_grid[x][y].shape);
                }
            }

            // les collisions
            for (const collisionManager& collision : _collisions) {
                _window->draw(collision.collisionShape);
            }

            //joueur
            _window->draw(playerShape);

            _window->display();
        }
    }

    void Application::_initGrid(const int sizeX, const int sizeY) {
        _grid.resize(sizeX, std::vector<Tile>(sizeY, Tile(_squareSize, TileType::Grass)));
    
        sf::Color transparentRed(255, 0, 0, 128);
    
        for (int x = 0; x < sizeX; x++) {
            for (int y = 0; y < sizeY; y++) {
                TileType type = (rand() % 15 == 0) ? TileType::Water : TileType::Grass;
    
                _grid[x][y] = Tile(_squareSize, type);
                _grid[x][y].shape.setPosition(x * _squareSize, y * _squareSize);
    
                if (type == TileType::Grass) {
                    _grid[x][y].shape.setFillColor(sf::Color::Green);
                } else if (type == TileType::Water) {
                    _grid[x][y].shape.setFillColor(sf::Color::Blue);

                    _collisions.emplace_back(x * _squareSize, y * _squareSize, _squareSize, _squareSize, transparentRed);
                }
            }
        }
    }
    
}
