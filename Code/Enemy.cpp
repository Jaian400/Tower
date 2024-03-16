#include "Enemy.h"
#include <iostream>
#include <cmath>

Enemy::Enemy(const std::vector<sf::Vector2f> &roadPoints, float radius)
    : roadPoints(roadPoints), currentTextureIndex(0), speed(50.0f), currentRoadPointIndex(0)
{
    std::vector<std::string> enemyTexturePaths;
    for (int i = 0; i < 12; i++)
    {
        enemyTexturePaths.push_back("EnemyTexture" + std::to_string(i) + ".png");
        // nazwy zmienione po zmianie z gif na png
    }

    // Load textures for the enemy animation
    for (std::size_t i = 0; i < enemyTexturePaths.size(); ++i)
    {
        sf::Texture texture;
        if (!texture.loadFromFile(enemyTexturePaths[i]))
        {
            std::cerr << "Failed to load enemy image: " << enemyTexturePaths[i] << std::endl;
            // Handle the error appropriately (throw exception, return error status, etc.)
        }
        EnemyTextures.push_back(texture);
    }

    // Set up the enemy sprite with the first texture
    enemySprite.setTexture(EnemyTextures[currentTextureIndex]);
    enemySprite.setPosition(roadPoints[0]);

    hp = 2;
    dead = false;
}

void Enemy::update(float deltaTime)
{
    // Animation update
    static const float animationSpeed = 0.0833f; // Adjust as needed
    if (clock.getElapsedTime().asSeconds() > animationSpeed)
    {
        // Switch to the next texture in the animation
        ++currentTextureIndex;
        if (currentTextureIndex >= EnemyTextures.size())
        {
            currentTextureIndex = 0; // Restart the animation from the beginning
        }
        enemySprite.setTexture(EnemyTextures[currentTextureIndex]);
        clock.restart();
    }

    // Movement update
    if (currentRoadPointIndex < roadPoints.size() - 1)
    {
        sf::Vector2f direction = normalize(roadPoints[currentRoadPointIndex + 1] - roadPoints[currentRoadPointIndex]);
        enemySprite.move(direction * speed * deltaTime);

        // std::cout<<enemySprite.getPosition().y<<std::endl;

        if (distance(enemySprite.getPosition(), roadPoints[currentRoadPointIndex + 1]) < 5.0f)
        {
            ++currentRoadPointIndex;
        }
    }
}

void Enemy::draw(sf::RenderWindow &window) const
{
    window.draw(enemySprite);
}

sf::FloatRect Enemy::getGlobalBounds() const
{
    return enemySprite.getGlobalBounds();
}

void Enemy::setPosition(const sf::Vector2f &position)
{
    enemySprite.setPosition(position);
}

sf::Vector2f Enemy::normalize(const sf::Vector2f &vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0.0f)
    {
        return vector / length;
    }
    return vector;
}

float Enemy::distance(const sf::Vector2f &point1, const sf::Vector2f &point2)
{
    return std::sqrt((point2.x - point1.x) * (point2.x - point1.x) + (point2.y - point1.y) * (point2.y - point1.y));
}
sf::Vector2f Enemy::getPosition() const
{
    return enemySprite.getPosition();
}