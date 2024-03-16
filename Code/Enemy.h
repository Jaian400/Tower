#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>

class Enemy
{
public:
    Enemy(const std::vector<sf::Vector2f> &roadPoints, float radius = 0.0f);

    void update(float deltaTime);
    void draw(sf::RenderWindow &window) const;

    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &position);
    sf::Sprite enemySprite;
    std::size_t currentRoadPointIndex;

    int hp;
    bool dead;

private:
    std::vector<sf::Texture> EnemyTextures;
    std::vector<sf::Vector2f> roadPoints;
    std::size_t currentTextureIndex;
    float speed;

    sf::Clock clock;

    sf::Vector2f normalize(const sf::Vector2f &vector);
    float distance(const sf::Vector2f &point1, const sf::Vector2f &point2);
};

#endif // ENEMY_H
