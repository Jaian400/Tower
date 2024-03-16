#include "Ghost.h"
#include <iostream>

Ghost::Ghost() : isPinned(false), width(70), height(70), color(sf::Color(128, 128, 128, 128)), 
                    towerParametsDownload(sf::Vector2f(0.f,0.f)), fixTowerRangeOffset(1.f,1.f)
{
    visible = false;
    ghostShape.setSize(sf::Vector2f(width, height));
    ghostShape.setFillColor(color);

    towerRange.setFillColor(sf::Color(128, 128, 128, 32));
    towerRange.setOutlineColor(sf::Color(40, 40, 40, 128));
    towerRange.setOutlineThickness(4);

    for (int i = 1; i <= 3; i++)
    {
        ghostTextures[i-1].loadFromFile("towerTexture" + std::to_string(i) + ".png");
    }
}

void Ghost::PinToMouse(sf::Vector2f mousePosition) 
{
    isPinned = true;
    ghostShape.setPosition(mousePosition.x - width / 2, mousePosition.y - height / 2);
}

void Ghost::Draw(sf::RenderWindow& window) 
{
    window.draw(ghostShape);
    window.draw(towerRange);
}

void Ghost::setTexture(int num)
{
    fixTowerRangeOffset.x = 0.f;
    fixTowerRangeOffset.y = 0.f;
    fixTowerRangeOffset.x -= towerParametsDownload.range[num-1];
    fixTowerRangeOffset.y -= towerParametsDownload.range[num-1];
    towerRange.setRadius(towerParametsDownload.range[num-1]);
    ghostShape.setTexture(&ghostTextures[num-1]);
}

void Ghost::changeColor(int r, int g, int b, int a)
{
    ghostShape.setFillColor(sf::Color(r, g, b, a));
}