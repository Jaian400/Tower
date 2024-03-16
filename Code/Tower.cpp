#include "Tower.h"
#include <iostream>

Tower::Tower(const sf::Vector2f &position)
    : towerShape(sf::Vector2f(70.f, 70.f))
{
    towerShape.setPosition(position);
    isActive = false;

    for (int i = 1; i <= 3; i++)
    {
        towerTextures[i-1].loadFromFile("towerTexture" + std::to_string(i) + ".png");
    } 

    bulletTexture.loadFromFile("bulletTexture.png");

    shootingInterval[0]=2.f;
    shootingInterval[1]=2.f;
    shootingInterval[2]=1.f;

    range[0]=110.f;
    range[1]=180.f;
    range[2]=125.f;
}

void Tower::setTowerPosition(sf::Vector2f position)
{
    towerShape.setPosition(position);
}

void Tower::setTowerTexture()
{
    towerShape.setTexture(&towerTextures[towerKind-1]);
}

void Tower::update(float deltaTime, std::vector<Enemy> &enemies)
{
    if(!isActive)
        return;

    sf::Vector2f direction;
    
    // Strzelaj do wrogów
    if (shootClock.getElapsedTime().asSeconds() > shootingInterval[towerKind-1])
    {
        for (auto it = enemies.begin(); it != enemies.end(); ++it)
        {
            // Sprawdź, czy wrogowie są wystarczająco blisko, aby strzelać
            direction = (it->getPosition() + sf::Vector2f(20.f, 20.f)) - (getPosition() + sf::Vector2f(35.f, 35.f));
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (distance < range[towerKind - 1])
            {
                // Strzelaj do wrogów
                it->hp--;
                shoot(*it, direction, deltaTime);
                //std::cout << "shot by tower " << towerKind << std::endl;
                shootClock.restart();
                break;
            }
        }
    }

    // Aktualizuj pociski
    for (auto it = bullets.begin(); it != bullets.end();)
    {
        auto currentTime = std::chrono::system_clock::now();
        auto now = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch());
        //std::cout<<"Now: "<<now.count()<<" shootStart: "<<it->shootStart.count()<<std::endl;
        //std::cout << "Warunek: " << now.count() - it->shootStart.count() << std::endl;
        //std::cout<<"delta: " <<deltaTime;
        if (now.count() - it->shootStart.count() > 200.f)
        {
            //std::cout<<"bullet out"<<std::endl;
            bullets.erase(it);
        }
        else
        {
            it->bulletShape.move(it->bulletDirection * 5.f * deltaTime);
            ++it;
        }
    }
}

void Tower::draw(sf::RenderWindow &window) const
{
    window.draw(towerShape);

    // Rysuj pociski
    for (int i = 0; i<bullets.size(); i++)
    {
        window.draw(bullets[i].bulletShape);
    }
}

sf::Vector2f Tower::getPosition() const
{
    return towerShape.getPosition();
}

void Tower::shoot(const Enemy &target, sf::Vector2f direction, float deltaTime)
{
    bullet newBullet;
    newBullet.bulletShape.setRadius(10);
    newBullet.bulletShape.setTexture(&bulletTexture);
    newBullet.bulletDirection = direction;
    newBullet.bulletShape.setPosition(getPosition().x + 35.f, getPosition().y +35.f);
   
    auto currentTime = std::chrono::system_clock::now();
    newBullet.shootStart = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch());

    bullets.push_back(newBullet);
}

sf::FloatRect Tower::getGlobalBounds() const
{
    return towerShape.getGlobalBounds();
}

