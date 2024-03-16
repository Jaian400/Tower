// TowerBar.cpp
#include "TowerBar.h"
#include <iostream>

TowerBar::TowerBar(sf::Vector2u windowSize)
    : coloredBar(sf::Vector2f(150.f, windowSize.y)),
      defaultTower(sf::Vector2f(0.f, 0.f))
{
    towerBarPosition = sf::Vector2f(- 150.f, 0.f);
    towerSpacing = sf::Vector2f(0.f, 70.f);

    // for (float y = towerSpacing.y; y <= windowSize.y; y += towerSpacing.y)
    // {
    //     towers.emplace_back(sf::Vector2f(windowSize.x - 150.f, y));
    // }
    for (int i = 0; i < 50; i++)
    {
        towers.emplace_back(sf::Vector2f(- 150.f, 0.f));
    }

    draggingTowerIndex = -1;
    selectedTowerIndex = -1;

    defaultTower = Tower(sf::Vector2f(0.f, 0.f));
}

