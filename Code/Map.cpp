#include "Map.h"
#include <iostream>
#include <cmath>

Map::Map()
{
    // Load background
    if (!backgroundTexture.loadFromFile("background5.jpg"))
    {
        std::cerr << "Failed to load background image!" << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture);

    // Set up the road points
    roadPoints.push_back(sf::Vector2f(-100.f, 80.f));
    roadPoints.push_back(sf::Vector2f(388.f, 80.f));
    roadPoints.push_back(sf::Vector2f(388.f, 280.f));
    roadPoints.push_back(sf::Vector2f(177.f, 280.f));
    roadPoints.push_back(sf::Vector2f(177.f, 490.f));
    roadPoints.push_back(sf::Vector2f(588.f, 490.f));
    roadPoints.push_back(sf::Vector2f(588.f, 81.f));
    roadPoints.push_back(sf::Vector2f(700.f, 81.f));

    // Create the road
    //createRoad();
    createBlockers();
}

void Map::draw(sf::RenderWindow &window)
{
    // Draw background
    window.draw(backgroundSprite);

    //Draw the road
    //window.draw(road);
}

const std::vector<sf::Vector2f> &Map::getRoadPoints() const
{
    return roadPoints;
}

void Map::createRoad()
{
    road.setPrimitiveType(sf::Quads);
    road.resize((roadPoints.size() - 1) * 4);

    for (std::size_t i = 0; i < roadPoints.size() - 1; ++i)
    {
        sf::Vector2f dir = normalize(roadPoints[i + 1] - roadPoints[i]);
        sf::Vector2f normal(-dir.y, dir.x);

        sf::Vector2f offset = normal * 33.f;

        road[i * 4 + 0].position = roadPoints[i] + offset;
        road[i * 4 + 1].position = roadPoints[i + 1] + offset;
        road[i * 4 + 2].position = roadPoints[i + 1] - offset;
        road[i * 4 + 3].position = roadPoints[i] - offset;

        for (int j = 0; j < 4; ++j)
        {
            road[i * 4 + j].color = sf::Color::White;
        }
    }
}

void Map::createBlockers()
{
    blockers.push_back(sf::IntRect (0, 44, 453, 115));
    blockers.push_back(sf::IntRect (352, 153, 102, 203));
    blockers.push_back(sf::IntRect(148, 244, 214, 112));
    blockers.push_back(sf::IntRect(147, 346, 103, 214));
    blockers.push_back(sf::IntRect(239, 458, 408, 98));
    blockers.push_back(sf::IntRect(552, 45, 100, 422));
    blockers.push_back(sf::IntRect(640, 31, 164, 128));
    blockers.push_back(sf::IntRect(780, 0, 170, 600));
    blockers.push_back(sf::IntRect(642, 225, 161, 100));
    blockers.push_back(sf::IntRect(323, 562, 73, 38));
    blockers.push_back(sf::IntRect(0, 470, 100, 129));
    blockers.push_back(sf::IntRect(0, 0, 118, 46));
    blockers.push_back(sf::IntRect(446, 0, 107, 72));
    blockers.push_back(sf::IntRect(61, 165, 103, 93));
    blockers.push_back(sf::IntRect(714, 488, 73, 112));
    blockers.push_back(sf::IntRect(0, 0, 800, 30));
    blockers.push_back(sf::IntRect(0, 0, 35, 600));
    blockers.push_back(sf::IntRect(0, 580, 800, 20));
    blockers.push_back(sf::IntRect(496, 255, 71, 76));
    blockers.push_back(sf::IntRect(373, 420, 112, 43));
    blockers.push_back(sf::IntRect(428, 393, 78, 30));
    blockers.push_back(sf::IntRect(449, 326, 72, 70));
    blockers.push_back(sf::IntRect(476, 299, 62, 44));
}

sf::Vector2f Map::normalize(const sf::Vector2f &vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0.0f)
    {
        return vector / length;
    }
    return vector;
}
