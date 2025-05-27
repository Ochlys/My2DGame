#include "application.hpp"

namespace GAME {

    Application::Application(const std::string& name, const int width, const int height) :
        _name(name), _width(width), _height(height)
    {
        _window = new sf::RenderWindow(sf::VideoMode(_width, _height), _name);

        if (!_grassTexture.loadFromFile("../src/textures/grass/grass.png")) {
            std::cerr << "Erreur : impossible de charger la tile Grass !" << std::endl;
        }

        if (!_waterTexture.loadFromFile("../src/textures/water/water.png")) {
            std::cerr << "Erreur : impossible de charger la tile Water !" << std::endl;
        }

        if (!_treeTexture.loadFromFile("../src/textures/tree/tree.png")) {
            std::cerr << "Erreur : impossible de charger la tile Tree !" << std::endl;
        }

        if (!_sandTexture.loadFromFile("../src/textures/sand/tree.png")) {
            std::cerr << "Erreur : impossible de charger la tile Sand !" << std::endl;
        }


        std::cout << "Application initialisée." << std::endl
                  << "SFML version: "
                  << SFML_VERSION_MAJOR << "."
                  << SFML_VERSION_MINOR << "."
                  << SFML_VERSION_PATCH << std::endl;

        if (DEBUG)
            std::cout << "Débug mode activé." << std::endl;

        _initGrid(50, 20);

        MovingEntity entity{{7.0, 7.0}, 0.98f, 0.98f, sf::Color::Yellow, 1.0f};
        Player player{{2.0, 2.0}, 0.98f, 0.98f, sf::Color::Red, 2.5f};
        _entitys.push_back(std::make_shared<MovingEntity>(entity));
        m_pPlayer = std::make_shared<Player>(player);
        _entitys.push_back(m_pPlayer);
    }

    void Application::run() {
        std::cout << "Lancement de l'application." << std::endl;

        sf::Clock clock;
        const double frameTime = 1.0 / _fps;
        double deltaTime = 0.0;

        // AFFICHER LES COLLISIONS
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
            // std::cout << "FPS: " << fps << std::endl;

            // AFFICHAGES

            for(const auto& entity: _entitys)
                entity->update(deltaTime, _grid, _entitys);

            float windowWidth = _window->getSize().x;
            float windowHeight = _window->getSize().y;
            float mapWidth = _grid.size() * SQUARE_SIZE;
            float mapHeight = _grid[0].size() * SQUARE_SIZE;

            Camera camera(mapWidth, mapHeight, windowWidth, windowHeight);
            camera.update(m_pPlayer->getPixelPosition());

            _window->clear();

            _window->setView(camera.getView());

            // Grille
            for (int x = 0; x < _grid.size(); x++) {
                for (int y = 0; y < _grid[0].size(); y++) {
                    if (DEBUG && !_grid[x][y].IsTraversable) {
                        displayCollision.setPosition(x * SQUARE_SIZE, y * SQUARE_SIZE);
                        _window->draw(_grid[x][y].Shape);
                    }
                    if (_grid[x][y].IsTraversable) {
                        _window->draw(_grid[x][y].Shape);
                    }
                }
            }

            // for (int x = 0; x < _grid.size(); ++x) { 
            //     for (int y = 0; y < _grid[x].size(); ++y) {
            //         if (_grid[x][y] == Tile::Water) {
            //             _grid[x][y].Shape.setTexture(&_waterTexture);
            //         }
            //     }
            // }

            for(const auto& entity: _entitys){
                entity->draw(_window);
            }

            for (int x = 0; x < _grid.size(); x++) {
                for (int y = 0; y < _grid[0].size(); y++) {
                    if (!_grid[x][y].IsTraversable) {
                        _window->draw(_grid[x][y].Shape);
                    }
                }
            }
            _window->display();
        }
    }

    void Application::_initGrid(const int sizeX, const int sizeY) {
        _grid.resize(sizeX);
        for (auto& column : _grid)
            column.resize(sizeY);

        for (int x = 0; x < sizeX; x++) {
            for (int y = 0; y < sizeY; y++) {
                if (y == 0 || x == 0) {
                    _grid[x][y] = Tile::Void;
                } else {
                    int randTile = rand() % 100;

                    if (randTile < 2) {
                        _grid[x][y] = Tile::Tree;
                    } else if (randTile < 7) {
                        _grid[x][y] = Tile::Water;
                    } else {
                        _grid[x][y] = Tile::Grass;
                    }
                }

                _grid[x][y].Position = sf::Vector2i(x, y);
                _grid[x][y].Shape.setPosition(x * SQUARE_SIZE, y * SQUARE_SIZE);


                // TEXTURES
                if (_grid[x][y] == Tile::Grass) {
                    _grid[x][y].Shape.setTexture(&_grassTexture);
                } if (_grid[x][y] == Tile::Water) {
                    _grid[x][y].Shape.setTexture(&_waterTexture);
                } if (_grid[x][y] == Tile::Tree) {
                    _grid[x][y].Shape.setTexture(&_treeTexture);
                    _grid[x][y].Shape.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE * 5));
                    _grid[x][y].Shape.setPosition(x * SQUARE_SIZE, y * SQUARE_SIZE - SQUARE_SIZE * 4);
                if (_grid[x][y] == Tile::Sand) {
                    _grid[x][y].Shape.setTexture(&_sandTexture);
                }

                } else {
                    _grid[x][y].Shape.setFillColor(_grid[x][y].Color);
                }
            }

        }
    }

}
