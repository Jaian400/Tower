#ifndef GHOST_H
#define GHOST_H

#include <SFML/Graphics.hpp>
#include "Tower.h"

class Ghost 
{
    public:
        Ghost();
        void PinToMouse(sf::Vector2f mousePosition);
        void Draw(sf::RenderWindow& window);
        bool visible;
        void setTexture(int num);
        void changeColor(int, int, int, int);
        sf::CircleShape towerRange;
        sf::Vector2f fixTowerRangeOffset;

    private:
        sf::RectangleShape ghostShape;
        bool isPinned;
        int width, height;
        sf::Color color;
        sf::Texture ghostTextures[3];
        float towerKindRadius[3];
        Tower towerParametsDownload;
};

#endif