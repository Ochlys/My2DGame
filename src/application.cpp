#include "application.hpp"
#include "player.hpp"

namespace GAME {

    Application::Application(std::string name, int width, int height) :
    _name(name), _width(width), _height(height), _player(50.f, 50.f, sf::Color::Blue)
    {
        _window = new sf::RenderWindow(sf::VideoMode(_width, _height), _name);

        std::cout << "Application initialisée."
        << std::endl << "SFML version: " 
        << SFML_VERSION_MAJOR << "." 
        << SFML_VERSION_MINOR << "." 
        << SFML_VERSION_PATCH 
        << std::endl;

        _initGrid(10, 10); 
    }

    void Application::run() {

        std::cout << "Lancement de l'application." << std::endl;

        const sf::RectangleShape& playerShape = _player.getShape();

        sf::Clock       clock;
        const double    frameTime = 1.0 / _fps; 
        double          deltaTime = 0.0; 
        
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

            // Affichages
            _window->clear();

            for (int x = 0; x < _grid.size(); x++) {
                for (int y = 0; y < _grid[0].size(); y++) {
                    _window->draw(_grid[x][y]);
                }
            }
            _window->draw(playerShape);

            _window->display();
        }
    }

    void Application::_initGrid(const int sizeX, const int sizeY) {
        _grid.resize(sizeX, std::vector<sf::RectangleShape>(sizeY));

        for (int x = 0; x < sizeX; x++) {
            for (int y = 0; y < sizeY; y++) {
                _grid[x][y].setSize(sf::Vector2f(_squareSize, _squareSize));
                
                if((x + y) % (2) == 0)  _grid[x][y].setFillColor(_squareColor);
                    else                _grid[x][y].setFillColor(_squareColor2);

                _grid[x][y].setPosition(x * _squareSize, y * _squareSize);
            }
        }
    }

}