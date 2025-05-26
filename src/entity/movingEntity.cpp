#include "movingEntity.hpp"
#include <iostream>
#include "../utils/vectors.hpp"

namespace GAME {

    void MovingEntity::update(double deltaTime, const Map& map, const std::vector<std::shared_ptr<BaseEntity>>& entitys) {
        m_timer += deltaTime;
        if (m_timer >= 3.f + static_cast<float>(std::rand() % 3)) {
            int direction = std::rand() % 4;  // 0 = gauche, 1 = droite, 2 = haut, 3 = bas
            switch (direction) {
                case 0: // gauche
                    m_velocity.x = -1;
                    m_velocity.y = 0.f;
                    break;
                case 1: // droite
                    m_velocity.x = 1;
                    m_velocity.y = 0.f;
                    break;
                case 2: // haut
                    m_velocity.x = 0.f;
                    m_velocity.y = -1;
                    break;
                case 3: // bas
                    m_velocity.x = 0.f;
                    m_velocity.y = 1;
                    break;
            }
            m_timer = 0.f;
            m_velocity = UTILS::normalize(m_velocity);
        }
    
        sf::Vector2f newPosition = this->getPosition() + sf::Vector2f(m_velocity.x * m_speed * deltaTime, m_velocity.y * m_speed * deltaTime);
        Box newBox{newPosition, this->getBox().getWidth(), this->getBox().getHeight()};

        if (MovingEntity::isValidPosition(newBox, map) && !detectEntityCollision(newBox, entitys)) {
            this->setPosition(newPosition);
            m_shape.setPosition(this->getPixelPosition());
        }

    }

    bool MovingEntity::detectEntityCollision(const Box& iBox, const std::vector<std::shared_ptr<BaseEntity>>& entitys){
        sf::Vector2f topLeft = iBox.getTopLeft();
        sf::Vector2f bottomRight = iBox.getBottomRight();

        for(const auto& entity : entitys){
            if(entity.get() == static_cast<BaseEntity*>(this))
                continue;
            if(entity->getBox().intersect(iBox)){
                return true;
            }
        }
        return false;
    }


    bool MovingEntity::isValidPosition(const Box& iBox, const Map& map) {

        //calcul des coins >:(
        sf::Vector2f topLeft = iBox.getTopLeft();
        sf::Vector2f bottomRight = iBox.getBottomRight();
        sf::Vector2f bottomLeft{topLeft.x, bottomRight.y};
        sf::Vector2f topRight{bottomRight.x, topLeft.y};

        //conversion des coins en int ?
        std::vector<sf::Vector2i> tilesOfPosition(4);
        tilesOfPosition[0] = sf::Vector2i(topLeft);
        tilesOfPosition[1] = sf::Vector2i(bottomRight);
        tilesOfPosition[2] = sf::Vector2i(topRight);
        tilesOfPosition[3] = sf::Vector2i(bottomLeft);

        //vérification
        for(sf::Vector2i& tile : tilesOfPosition){
            if(tile.x >= map.size() || tile.y >= map[0].size())
                return false;
            if(tile.x < 0 || tile.y < 0)
                return false;
            if(!map[tile.x][tile.y].IsTraversable){
                return false;
            }
        }
        return true;

    }

    
}
