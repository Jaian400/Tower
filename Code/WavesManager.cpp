#include "WavesManager.h"

WavesManager::WavesManager()
{
    currentWaveNumber = 1;
    numberOfDeaths = 0;
}

int WavesManager::numberOfEnemiesCalculate()
{
    return (currentWaveNumber*currentWaveNumber+currentWaveNumber+10);
}

void WavesManager::startWave(Map gameMap)
{
    numberOfEnemies = numberOfEnemiesCalculate();
    for (int i = 0; i < numberOfEnemies; i++)
    {
        Enemy newEnemy(gameMap.getRoadPoints());
        if(i%100==0 && currentWaveNumber > 8)
        {
            newEnemy.enemySprite.setColor(sf::Color(10, 0, 0));
            newEnemy.hp+=48;
        }
        else if((i%35==0 && currentWaveNumber > 5))
        {
            newEnemy.enemySprite.setColor(sf::Color(255, 0, 20));
            newEnemy.hp+=18;
        }
        else if(i%15==0 && currentWaveNumber > 3)
        {
            newEnemy.enemySprite.setColor(sf::Color(153, 102, 255));
            newEnemy.hp+=5;
        }
        else if (i%4==0 && currentWaveNumber > 1)
        {
            newEnemy.enemySprite.setColor(sf::Color(255, 200, 0));
            newEnemy.hp+=1;
        }

        enemies.push_back(newEnemy);
    }
    std::cout<<"Fala nr " << currentWaveNumber << " naciera"<<std::endl;
    std::cout<<numberOfEnemies<<std::endl;
}

void WavesManager::restart()
{
    enemies.clear();
    numberOfDeaths = 0;
    currentWaveNumber++;
}