#include "GameLoop.h"

sf::IntRect rectangleOnBarTowerOne(830, 218, 92, 92);
sf::IntRect rectangleOnBarTowerTwo(830, 320, 92, 92);
sf::IntRect rectangleOnBarTowerThree(830, 423, 92, 92);

GameLoop::GameLoop() : window(sf::VideoMode(950, 600), "Tower Defense Game"), towerBin(-300.f, -300.f),
                       finishPosition(700.f, 100.f), finishRectangle(sf::Vector2f(50.f, 50.f)), enemyReachedFinish(false),
                       settings(window)
{
    currentTowerIndex = 0;
    towerOnMouse = false;
    canPlace = false;
    isWave = false;
    finishWidth = 50.f;
    finishHeight = 50.f;
    framerate = 60.f;
    startButton = sf::IntRect(800, 21, 142, 54);
    settingsButton = sf::IntRect(886, 538, 55, 53);
    restartButton = sf::IntRect(807, 538, 57, 53);
    howToPlayButton = sf::IntRect(4, 3, 59, 56);

    money = 300;
    price[0] = 100;
    price[1] = 200;
    price[2] = 350;

    if (!font.loadFromFile("Algerian Font.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
    }

    moneyInfo.setFont(font);
    moneyInfo.setCharacterSize(28);
    moneyInfo.setFillColor(sf::Color::White);
    moneyInfo.setPosition(856.f, 166.f);
    moneyInfo.setString(std::to_string(money));

    waveInfo.setFont(font);
    waveInfo.setCharacterSize(34);
    waveInfo.setFillColor(sf::Color::White);
    waveInfo.setPosition(887.f, 85.f);
    waveInfo.setString(std::to_string(wavesManager.currentWaveNumber));

    for (int i = 0; i < 20; i++)
    {
        Tower newTower(sf::Vector2f(-300.f, -300.f));
        towers.push_back(newTower);
    }
}

void GameLoop::mainLoop()
{
    audioManager.playMusic("music_game.mp3");

    while (window.isOpen())
    {
        mousePosition = sf::Mouse::getPosition(window);

        if (ghost.visible)
            for (unsigned short i = 0; i < gameMap.blockers.size(); i++)
            {
                if (isMouseInRectangle(mousePosition, gameMap.blockers[i]))
                {
                    ghost.changeColor(200, 20, 20, 128);
                    canPlace = false;
                    break;
                }
                else
                {
                    canPlace = true;
                }
            }

        if (canPlace)
        {
            ghost.changeColor(128, 128, 128, 128);
        }

        // WSZYSTKIE EVENTY TUTAJ
        checkEvents();

        deltaTime = clock.restart().asSeconds();

        window.clear();

        gameMap.draw(window);

        moneyInfo.setString(std::to_string(money));
        window.draw(moneyInfo);
        waveInfo.setString(std::to_string(wavesManager.currentWaveNumber));
        window.draw(waveInfo);

        //std::cout<<isWave<<std::endl;

        if (isWave)
        {
            waveInfo.setString(std::to_string(wavesManager.currentWaveNumber));
            for (int i = 0; i < wavesManager.numberOfEnemies; i++)
            {
                if (i > 0 && wavesManager.enemies[i].getPosition().x == -100.f)
                {
                    wavesManager.enemies[i].setPosition(sf::Vector2f(float(i) * (-40.f) - 100.f, 80.f));
                }
                wavesManager.enemies[i].update(deltaTime);
                wavesManager.enemies[i].draw(window);
            }

            for (int i = 0; i < wavesManager.numberOfEnemies; i++)
            {
                if (wavesManager.enemies[i].getGlobalBounds().intersects(sf::FloatRect(finishPosition, sf::Vector2f(finishWidth, finishHeight))))
                {
                    std::cout << "enemy zabil piwnice" << std::endl;
                    gameOver();
                }
                if (!enemyReachedFinish && wavesManager.enemies[i].getGlobalBounds().intersects(sf::FloatRect(finishPosition, sf::Vector2f(finishWidth, finishHeight))))
                {
                    audioManager.playSound("collision_sound");
                    // jezeli osiagnie mozna dodac jakis dzwiek
                }
            }

            for(int i = 0; i < wavesManager.numberOfEnemies; i++)
            {
                if(!wavesManager.enemies[i].dead)
                {
                    if(wavesManager.enemies[i].hp <= 0)
                    {
                        wavesManager.enemies[i].setPosition(sf::Vector2f(-10000.f,-10000.f));
                        wavesManager.enemies[i].dead = true;
                        money+=5;
                        wavesManager.numberOfDeaths++;
                    }
                    else if (
                    wavesManager.enemies[i].enemySprite.getPosition().y > 600)
                    {
                        std::cout<<"coward"<<std::endl;
                        wavesManager.enemies[i].setPosition(sf::Vector2f(-10000.f,-10000.f));
                        wavesManager.enemies[i].dead = true;
                        money+=5;
                        wavesManager.numberOfDeaths++;
                    }
                }
            }

            if(wavesManager.numberOfEnemies == wavesManager.numberOfDeaths)
            {
                wavesManager.restart();
                isWave=false;
                std::cout<<"marwti wszyscy"<<std::endl;
            }
        }

        if(wavesManager.currentWaveNumber > settings.loadMaxWave())
        {
            settings.saveMaxWave(wavesManager.currentWaveNumber);
        }

        for (int i = 0; i < 20; i++)
        {
            towers[i].draw(window);
            towers[i].update(deltaTime, wavesManager.enemies);
        }

        if (ghost.visible)
        {
            ghost.Draw(window);
        }

        finishRectangle.setPosition(finishPosition);
        // window.draw(finishRectangle);

        std::this_thread::sleep_for(std::chrono::milliseconds(16));

        window.display();
    }
}

void GameLoop::checkEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (mousePosition.x >= 0 && mousePosition.x < window.getSize().x &&
            mousePosition.y >= 0 && mousePosition.y < window.getSize().y)
        {
            // Ghost jest zawsze przypiety do myszki, bedziemy go pokazywac gdy gracz wybierze wieze,
            // czytaj: kliknie w odpowiednim miejscu na ekranie
            ghost.PinToMouse(sf::Vector2f(mousePosition));
            ghost.towerRange.setPosition(sf::Vector2f(mousePosition));
            ghost.towerRange.move(ghost.fixTowerRangeOffset);
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left && isMouseInRectangle(mousePosition, startButton) && !isWave)
            {
                wavesManager.startWave(gameMap);
                isWave = true;
            }
            else if(event.mouseButton.button == sf::Mouse::Left && isMouseInRectangle(mousePosition, restartButton))
            {
                restartGame();
            }
            else if(event.mouseButton.button == sf::Mouse::Left && isMouseInRectangle(mousePosition, howToPlayButton) && !isWave)
            {
                std::cout<<"how to play"<<std::endl;
                howToPlay();
            }
            else if (event.mouseButton.button == sf::Mouse::Left && isMouseInRectangle(mousePosition, settingsButton) && !isWave)
            {
                settings.settingsLoop(audioManager, false);
            }

            if (event.mouseButton.button == sf::Mouse::Left && !towerOnMouse)
            {
                // Pobierz pozycję myszy w oknie
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                // Kliknięcie w obszar na ktorym naryswoana jest dana wieza
                if (isMouseInRectangle(mousePosition, rectangleOnBarTowerOne) && money>=price[0])
                {
                    towers[currentTowerIndex].towerKind = 1;
                }
                else if (isMouseInRectangle(mousePosition, rectangleOnBarTowerTwo) && money >= price[1])
                {
                    towers[currentTowerIndex].towerKind = 2;
                }
                else if (isMouseInRectangle(mousePosition, rectangleOnBarTowerThree) && money >= price[2])
                {
                    towers[currentTowerIndex].towerKind = 3;
                }
                else
                {
                    continue;
                }

                std::cout << "Kliknięto w obszar wieza " << towers[currentTowerIndex].towerKind << std::endl;
                ghost.visible = true;
                ghost.setTexture(towers[currentTowerIndex].towerKind);
                towerOnMouse = true;
            }
            else if (event.mouseButton.button == sf::Mouse::Left && towerOnMouse && canPlace)
            {
                audioManager.emitBuildSound();
                sf::Vector2f newTowerPosition = sf::Vector2f(sf::Vector2f(mousePosition) - sf::Vector2f(35.f, 35.f));
                gameMap.blockers.push_back(sf::IntRect(sf::Vector2i((newTowerPosition)+sf::Vector2f(22.f,22.f)), sf::Vector2i(22, 50)));
                towers[currentTowerIndex].setTowerPosition(newTowerPosition);
                towers[currentTowerIndex].setTowerTexture();
                towers[currentTowerIndex].isActive = true;
                money -= price[towers[currentTowerIndex].towerKind-1];
                currentTowerIndex++;
                ghost.visible = false;
                towerOnMouse = false;
            }
            else if (event.mouseButton.button == sf::Mouse::Right)
            {
                ghost.visible = false;
                towerOnMouse = false;
            }
        }
    }
}

bool GameLoop::isMouseInRectangle(const sf::Vector2i &mousePosition, const sf::IntRect &rectangle)
{
    return rectangle.contains(mousePosition);
}

void GameLoop::howToPlay()
{
    sf::Texture texture;
    sf::IntRect howToPlayRect(0, 0, 950, 600);
    sf::Sprite howToPlaySprite;
    if (!texture.loadFromFile("jakGrac.jpg"))
    {
        std::cerr << "Failed to load background image!" << std::endl;
    }
    howToPlaySprite.setTexture(texture);
    
    bool open = true;

    while(open)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        //std::cout<<"how to play in"<<std::endl;
        if(!open)
        {
            return;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                open = false;
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left && isMouseInRectangle(mousePosition, howToPlayRect))
                {
                    std::cout << "how to play out" << std::endl;
                    open = false;
                }
            }
        }

        window.clear();
        window.draw(howToPlaySprite);
        window.display();
    }
}

void GameLoop::gameOver()
{
    sf::Texture texture;
    sf::Sprite gameOverSprite;
    if (!texture.loadFromFile("gameOver.jpg"))
    {
        std::cerr << "Failed to load background image!" << std::endl;
    }
    gameOverSprite.setTexture(texture);
    
    bool open = true;

    while(open)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        mousePosition = sf::Mouse::getPosition(window);

        if(!open)
        {
            return;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                open = false;
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left && isMouseInRectangle(mousePosition, restartButton))
                {
                    open = false;
                }
            }
        }

        window.clear();
        window.draw(gameOverSprite);
        window.display();
    }

    std::cout<<"restarting"<<std::endl;
    restartGame();
}

void GameLoop::restartGame()
{
    isWave = false;
    wavesManager.restart();
    wavesManager.currentWaveNumber = 1;
    gameMap.blockers.clear();
    money = 300;
    towers.clear();
    currentTowerIndex=0;

    for (int i = 0; i < 20; i++)
    {   
        Tower newTower(sf::Vector2f(-300.f, -300.f));
        towers.push_back(newTower);
    }
    gameMap.createBlockers();
}