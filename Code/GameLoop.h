#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Enemy.h"
#include "Tower.h"
#include "TowerBar.h"
#include <iostream>
#include "Ghost.h"
#include "WavesManager.h"
#include "AudioManager.h"
#include <chrono>
#include <thread>
#include "Settings.h"

class GameLoop
{
public:
    GameLoop();
    void mainLoop();
    void checkEvents();
    bool isMouseInRectangle(const sf::Vector2i &mousePosition, const sf::IntRect &rectangle);
    Map gameMap;
    Ghost ghost;
    WavesManager wavesManager;
    AudioManager audioManager;
    Settings settings;
    sf::RectangleShape finishRectangle;
    std::vector<Tower> towers;
    sf::Vector2f towerBin;
    sf::Vector2f finishPosition;
    sf::Vector2i mousePosition;
    int currentTowerIndex;
    bool towerOnMouse;
    bool canPlace;
    bool isWave;
    float finishWidth;
    float finishHeight;
    float deltaTime;
    float framerate;
    sf::Clock clock;

private:
    sf::RenderWindow window;
    void playBackgroundMusic();
    void stopBackgroundMusic();
    void playCollisionSound();
    void gameOver();
    void restartGame();
    bool enemyReachedFinish;
    sf::IntRect startButton;
    sf::IntRect settingsButton;
    sf::IntRect restartButton;
    sf::IntRect howToPlayButton;
    void howToPlay();
    int money;
    sf::Text moneyInfo;
    sf::Text waveInfo;
    sf::Font font;
    int price[3];
};

#endif