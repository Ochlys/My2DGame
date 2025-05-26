#include "player.hpp"

namespace GAME {

    void Player::update(const double deltaTime, const Map& map, const std::vector<std::shared_ptr<BaseEntity>>& entitys) {
        m_velocity = {0.f, 0.f};
        //            X   Y

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            m_velocity.x = -1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            m_velocity.x = 1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            m_velocity.y = -1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            m_velocity.y = 1.f;
        }


        m_velocity = UTILS::normalize(m_velocity);
        m_velocity.x *= (m_speed * (float) deltaTime);
        m_velocity.y *= (m_speed * (float) deltaTime);

        sf::Vector2f newPosition = this->getPosition() + sf::Vector2f(m_velocity.x, 0.0f);
        Box newBox{newPosition, this->getBox().getWidth(), this->getBox().getHeight()};

        if(!isValidPosition(newBox, map) || detectEntityCollision(newBox, entitys))
            m_velocity.x = 0.0;
        
        newPosition = this->getPosition() + m_velocity;
        newBox.setPosition(newPosition);
        if(!isValidPosition(newBox, map) || detectEntityCollision(newBox, entitys))
            m_velocity.y = 0.0;

        // pour fix quand c'est près (opas bo)
        if(m_velocity.x == 0.0 && m_velocity.y == 0.0){
            float localSpeed = m_speed * 0.3;
            m_velocity = UTILS::normalize(m_velocity);
            m_velocity.x *= (localSpeed * (float) deltaTime);
            m_velocity.y *= (localSpeed * (float) deltaTime);

            sf::Vector2f newPosition = this->getPosition() + sf::Vector2f(m_velocity.x, 0.0f);
            Box newBox{newPosition, this->getBox().getWidth(), this->getBox().getHeight()};

            if(!isValidPosition(newBox, map) || detectEntityCollision(newBox, entitys))
                m_velocity.x = 0.0;
            
            newPosition = this->getPosition() + m_velocity;
            newBox.setPosition(newPosition);
            if(!isValidPosition(newBox, map) || detectEntityCollision(newBox, entitys))
                m_velocity.y = 0.0;
        }



        this->move(m_velocity);

        m_shape.setPosition(this->getPixelPosition());
    }
}
