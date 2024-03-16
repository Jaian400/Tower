#ifndef TOWER_H
#define TOWER_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <time.h>
#include <iostream>
#include <chrono>
#include <cmath>

class Tower
{
public:
    Tower(const sf::Vector2f &position);
    bool isActive;
    int towerKind;

    void update(float deltaTime, std::vector<Enemy> &enemies);
    void draw(sf::RenderWindow &window) const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;

    void setTowerTexture();

    void setTowerPosition(sf::Vector2f position);
    float range[3];

private:
    sf::RectangleShape towerShape;
    float shootingInterval[3];
    sf::Clock shootClock;
    sf::Texture bulletTexture;
    sf::Texture towerTextures[3];
    struct bullet
    {
        sf::CircleShape bulletShape;
        sf::Vector2f bulletDirection;
        std::chrono::milliseconds shootStart;
    };
    std::vector<bullet> bullets;

    void shoot(const Enemy &target, sf::Vector2f direction, float deltaTime);
};

#endif // TOWER_H
