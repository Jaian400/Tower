// TowerBar.h
#ifndef TOWERBAR_H
#define TOWERBAR_H

#include "Tower.h"
#include <SFML/Graphics.hpp>
#include <vector>

class TowerBar
{
public:
    TowerBar(sf::Vector2u windowSize);

    void update(const sf::Vector2f &mousePosition);
    void draw(sf::RenderWindow &window) const;
    void handleClick(const sf::Vector2f &mousePosition);
    void releaseClick();
    const Tower &getSelectedTower() const;

private:
    std::vector<Tower> towers;
    int draggingTowerIndex;
    sf::Vector2f towerBarPosition;
    sf::Vector2f towerSpacing;
    sf::RectangleShape coloredBar;

    Tower defaultTower;

    int selectedTowerIndex; // Dodaj zmienną selectedTowerIndex
    bool isMouseOverColoredBar(const sf::Vector2f &mousePosition) const;
};

#endif // TOWERBAR_H
