#ifndef __BASE_ENTITY_HPP__
#define __BASE_ENTITY_HPP__

#include <SFML/Graphics.hpp>
#include <memory>
#include "../tile.hpp"
#include "../defines.hpp"
#include "../geometry/box.hpp"

namespace GAME {
    typedef std::vector<std::vector<Tile>> Map;

    class BaseEntity {

        public:

        BaseEntity(const sf::Vector2f& iPosition, const float iWidth,const float iHeight, const sf::Color& iColor, const bool iIsTraversable) 
        : m_box(iPosition, iWidth, iHeight), m_entityColor(iColor), m_isTraversable(iIsTraversable) 
        {
            m_shape.setSize({m_box.getWidth() * SQUARE_SIZE, m_box.getHeight() * SQUARE_SIZE});
            m_shape.setFillColor(m_entityColor);
            m_shape.setOrigin(m_shape.getSize().x / 2, m_shape.getSize().y / 2);
            m_shape.setPosition(getPixelPosition());
        };
        virtual ~BaseEntity() = default;

        virtual void update(double deltaTime, const Map& map) {};
        virtual void update(double deltaTime, const Map& map, const std::vector<std::shared_ptr<BaseEntity>>& entitys) {};

        sf::Vector2f getPosition() const { return m_box.getPosition(); };
        sf::Vector2f getPixelPosition() const { return getPosition() * SQUARE_SIZE; };

        void setPosition(const sf::Vector2f& iPosition) { m_box.setPosition(iPosition); };

        bool isTraversable() const { return m_isTraversable; };

        virtual void draw(sf::RenderWindow* iWindow) const { iWindow->draw(m_shape); };

        const Box& getBox() const { return m_box; };

        protected:
            sf::RectangleShape  m_shape;

        private:
            // position dans la carte (pas par pixel)
            bool                m_isTraversable;
            Box                 m_box;

            sf::Color           m_entityColor;
    };
};

#endif