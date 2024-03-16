#ifndef WAVESMANAGER_H
#define WAVESMANAGER_H

#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <iostream>
#include "Enemy.h"
#include "Map.h"

class WavesManager
{
    public:
        WavesManager(void);
        int currentWaveNumber; 
        int numberOfEnemies;
        int numberOfEnemiesCalculate();
        std::vector<Enemy> enemies;
        void startWave(Map gameMap);
        int numberOfDeaths;
        void restart();

    private:
        
};

#endif