#ifndef __BOX_HPP__
#define __BOX_HPP__

#include <SFML/Graphics.hpp>

namespace GAME {

class Box {
    public:
        Box(const sf::Vector2f& iPosition, const float iSize)
        : m_position(iPosition), m_width(iSize), m_height(iSize) 
        {};
        Box(const sf::Vector2f& iPosition, const float iWidth, const float iHeight)
        : m_position(iPosition), m_width(iWidth), m_height(iHeight) 
        {};
        Box(const sf::Vector2f& iTopLeft, const sf::Vector2f& iBottomRight)
        : m_width(iBottomRight.x - iTopLeft.x), m_height(iBottomRight.y - iTopLeft.y) 
        {
            m_position.x =  (iBottomRight.x + iTopLeft.x) / 2.0;
            m_position.y =  (iBottomRight.y + iTopLeft.y) / 2.0;
        };

        sf::Vector2f getPosition() const { return m_position; };
        void setPosition( const sf::Vector2f& iNewPosition ) { m_position = iNewPosition; };

        float getSize() const { return m_width; };
        float getWidth() const { return m_width; };
        float getHeight() const { return m_height; };
        sf::Vector2f getWidthHeight() const { return sf::Vector2{ m_width, m_height }; };

        sf::Vector2f getTopLeft() const {
            return m_position - sf::Vector2f(m_width * 0.5, m_height * 0.5) ;
        }; 
        sf::Vector2f getBottomRight() const {
            return m_position + sf::Vector2f(m_width * 0.5, m_height * 0.5) ;
        }; 

        bool intersect(const Box& iBox) const {
            sf::Vector2f thisTL = this->getTopLeft();
            sf::Vector2f thisBR = this->getBottomRight();
            sf::Vector2f otherTL = iBox.getTopLeft();
            sf::Vector2f otherBR = iBox.getBottomRight();

            return !(
                thisBR.x < otherTL.x ||
                thisTL.x > otherBR.x ||
                thisBR.y < otherTL.y ||
                thisTL.y > otherBR.y);
        };

    private:
        sf::Vector2f    m_position;
        float           m_width;
        float           m_height;
};

};

#endif