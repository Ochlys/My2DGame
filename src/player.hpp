#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <SFML/Graphics.hpp>
#include <memory>
#include "utils/vectors.hpp"
#include "entity/movingEntity.hpp"
#include "tile.hpp"

namespace GAME {
    typedef std::vector<std::vector<Tile>> Map;

    class Player : public MovingEntity {
    public:
        Player(const sf::Vector2f& iPosition, const float iWidth, const float iHeight, const sf::Color& iColor, const float iSpeed)
        : MovingEntity(iPosition, iWidth, iHeight, iColor, iSpeed) {};
        
        void update(const double deltaTime, const Map& map, const std::vector<std::shared_ptr<BaseEntity>>& entitys) override;
    };

}

#endif // __PLAYER_HPP__
