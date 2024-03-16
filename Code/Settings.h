#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include "AudioManager.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <bitset>

class Settings
{
public:
    Settings(sf::RenderWindow &window);

    void draw();
    
    //basiclly zapetlamy okno ustawien, wiec nic innego sie nie zmienia = gra freezuje
    void settingsLoop(AudioManager &audioManager, bool close);
    void saveMaxWave(int num);
    int loadMaxWave();

private:
    sf::RenderWindow &window;
    sf::Sprite settingsSprite;
    sf::Texture settingsTexture;
    bool isMouseInRectangle(const sf::Vector2i &mousePosition, const sf::IntRect &rectangle);
    
    sf::Text maxWaveInfo;
    sf::Text volumeInfo;
    sf::Font font;
    sf::IntRect volumeDown;
    sf::IntRect volumeUp;
    sf::IntRect closeButton;
};

#endif