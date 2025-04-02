#include "application.hpp"

namespace GAME {

    Application::Application(const std::string& name, const int width, const int height) :
    _name(name), _width(width), _height(height), 
    _player(50.f, 50.f, sf::Color::Red),
    _entity(50.f, 50.f, sf::Color::Yellow)
    {
        _window = new sf::RenderWindow(sf::VideoMode(_width, _height), _name);

        std::cout << "Application initialisée."
        << std::endl << "SFML version: " 
        << SFML_VERSION_MAJOR << "." 
        << SFML_VERSION_MINOR << "." 
        << SFML_VERSION_PATCH 
        << std::endl;

        if(DEBUG)
            std::cout << "Débug mode activé." << std::endl;

        _initGrid(25, 12); 
    }

    void Application::run() {
        std::cout << "Lancement de l'application." << std::endl;
        
        const sf::RectangleShape& playerShape = _player.getShape();

        sf::Clock clock;
        const double frameTime = 1.0 / _fps; 
        double deltaTime = 0.0; 

        // to display collisions
        sf::RectangleShape displayCollision(SQUARE_SIZE2);
        displayCollision.setFillColor(sf::Color(200, 0, 0, 150));

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
            //std::cout << "FPS: " << fps << std::endl;

            // Mises à jours
            _player.update(_window->getSize(), deltaTime, _grid);

            // AFFICHAGES
            _window->clear();

            //Grille
            for (int x = 0; x < _grid.size(); x++) {
                for (int y = 0; y < _grid[0].size(); y++) {
                    _window->draw(_grid[x][y].Shape);
                    if(DEBUG && !_grid[x][y].IsTraversable)
                    {
                        displayCollision.setPosition(x * SQUARE_SIZE, y * SQUARE_SIZE);
                        _window->draw(displayCollision);
                    }
                }
            }

            //Caméra

            // Position du perso
            float playerX = playerShape.getPosition().x;
            float playerY = playerShape.getPosition().y;

            // Taille de la fenêtre
            float windowWidth = _window->getSize().x;
            float windowHeight = _window->getSize().y;
                    
            // Taille de la map
            float mapWidth = _grid.size() * SQUARE_SIZE;
            float mapHeight = _grid[0].size() * SQUARE_SIZE;
         
            // Limites de la caméra
            float halfWidth = windowWidth / 2.f;
            float halfHeight = windowHeight / 2.f;

            // Centre de la caméra
            float cameraX = playerX - (windowWidth / 2.f);
            float cameraY = playerY - (windowHeight / 2.f);

            Camera camera(mapWidth, mapHeight, windowWidth, windowHeight);

            sf::Vector2f playerPosition(playerX, playerY);
            camera.update(playerPosition);

            // Vue
            sf::View view = _window->getView();

            _window->setView(camera.getView());

            // Joueur
            _window->draw(playerShape);

            //entity
            _window->draw(_entity.getShape());
            _entity.update(deltaTime, _grid);

            _window->display();
        }
    }

    void Application::_initGrid(const int sizeX, const int sizeY) {
        // Allocation of the grid
        _grid.resize(sizeX);
        for (auto& collumn : _grid)
            collumn.resize(sizeY); 
    
        // Create the terrain
        for (int x = 0; x < sizeX; x++) {
            for (int y = 0; y < sizeY; y++) {
                if(y == 0 || x == 0) _grid[x][y] = Tile::Void;
                else _grid[x][y] = (rand() % 15 == 0) ? Tile::Water : Tile::Grass;
                
                _grid[x][y].Position = sf::Vector2i(x, y);
                _grid[x][y].Shape.setPosition(x * SQUARE_SIZE, y * SQUARE_SIZE);
                _grid[x][y].Shape.setFillColor(_grid[x][y].Color); 
            }
        }
    }
    
}
