#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <SFML/Graphics.hpp>
#include "../utils/vectors.hpp"
#include "../tile.hpp"
#include "baseEntity.hpp"
#include <cstdlib> 
#include <memory> 

namespace GAME {
    typedef std::vector<std::vector<Tile>> Map;

    class MovingEntity : public BaseEntity {
    public:
        MovingEntity(const sf::Vector2f& iPosition, const float iWidth, const float iHeight, const sf::Color& iColor, const float iSpeed) 
        : BaseEntity(iPosition, iWidth, iHeight, iColor, false), m_speed(iSpeed) {} ;

        static bool isValidPosition(const Box& iBox, const Map& map);
        bool detectEntityCollision(const Box& iBox, const std::vector<std::shared_ptr<BaseEntity>>& entitys);

        void update(double deltaTime, const Map& map, const std::vector<std::shared_ptr<BaseEntity>>& entitys) override;
        void move(const sf::Vector2f& iDeplacement) { this->setPosition( this->getPosition() + iDeplacement); };

        const sf::RectangleShape& getShape() const;
        
    protected:

        sf::Vector2f        m_velocity = {0.0, 0.0};
        const float         m_speed = 1.0;

        float               m_timer = 0.0;
    };

}

#endif // __ENTITY_HPP__
