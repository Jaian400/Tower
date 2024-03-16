#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

class Map
{
public:
    Map();

    void draw(sf::RenderWindow &window);

    const std::vector<sf::Vector2f> &getRoadPoints() const;

    std::vector<sf::IntRect> blockers;
    void createBlockers();

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    std::vector<sf::Vector2f> roadPoints;
    sf::VertexArray road;

    void createRoad();
    
    sf::Vector2f normalize(const sf::Vector2f &vector);
};

#endif // MAP_H
