#include "Settings.h"
#include <iostream>

const char secretKey = 'K';

Settings::Settings(sf::RenderWindow &window)
    : window(window)
{
    if (!settingsTexture.loadFromFile("settings.jpg"))
    {
        std::cerr << "Failed to load background image!" << std::endl;
    }

    settingsSprite.setTexture(settingsTexture);
    settingsSprite.setPosition(0, 0);

    volumeDown = sf::IntRect(229, 165, 101, 101);
    volumeUp = sf::IntRect(628, 172, 99, 93);
    closeButton = sf::IntRect(722, 136, 38, 37);

    if (!font.loadFromFile("Algerian Font.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
    }

    volumeInfo.setFont(font);
    volumeInfo.setCharacterSize(38);
    volumeInfo.setFillColor(sf::Color::White);
    volumeInfo.setPosition(528.f, 188.f);
    
    maxWaveInfo.setFont(font);
    maxWaveInfo.setCharacterSize(41);
    maxWaveInfo.setFillColor(sf::Color::White);
    maxWaveInfo.setPosition(624.f, 338.f);
}

void Settings::settingsLoop(AudioManager &audioManager, bool close)
{
    while (window.isOpen())
    {
        if (close)
        {
            return;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (isMouseInRectangle(mousePosition, volumeDown) && audioManager.actualVolume != 0)
                    {
                        audioManager.actualVolume -= 10;
                        audioManager.playMusic("music_game.mp3");
                    }
                    else if (isMouseInRectangle(mousePosition, volumeUp) && audioManager.actualVolume != 100)
                    {
                        audioManager.actualVolume += 10;
                        audioManager.playMusic("music_game.mp3");
                    }
                    else if (isMouseInRectangle(mousePosition, closeButton))
                    {
                        close = true;
                    }
                }
            }
        }

        window.clear();

        window.draw(settingsSprite);    
        volumeInfo.setString(std::to_string(int(audioManager.actualVolume)));
        window.draw(volumeInfo);
        maxWaveInfo.setString(std::to_string(loadMaxWave()));
        //std::cout<<"Max wave: "<<loadMaxWave()<<std::endl;
        window.draw(maxWaveInfo);
        
        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(32));
    }
}

bool Settings::isMouseInRectangle(const sf::Vector2i &mousePosition, const sf::IntRect &rectangle)
{
    return rectangle.contains(mousePosition);
}

// Funkcja do szyfrowania danych
std::string encrypt(const std::string& data) 
{
    std::string encryptedData = data;
    for (char& c : encryptedData) 
    {
        c = c ^ secretKey;
    }
    return encryptedData;
}

// Funkcja do deszyfrowania danych
std::string decrypt(const std::string& data) 
{
    return encrypt(data);
}

void Settings::saveMaxWave(int num)
{
    std::ofstream plik_zapisu("maxWave.dat", std::ios::binary);

    if (plik_zapisu.is_open()) 
    {
        // Zapisz liczbÍ w formie binarnej
        std::bitset<sizeof(int) * 8> bityLiczby(num);
        plik_zapisu.write(reinterpret_cast<char*>(&bityLiczby), sizeof(int));

        plik_zapisu.close();

        std::cout << "Liczba " <<  num <<  "zostala zapisana do pliku .dat." << std::endl;
    }
    else 
    {
        std::cerr << "Blad podczas otwierania pliku do zapisu!" << std::endl;
    }
}

int Settings::loadMaxWave()
{
     std::ifstream plik_odczytu("maxWave.dat", std::ios::binary);

    if (plik_odczytu.is_open()) 
    {
        std::bitset<sizeof(int) * 8> bityLiczby;
        plik_odczytu.read(reinterpret_cast<char*>(&bityLiczby), sizeof(int));

        // Konwertuj z powrotem do liczby
        int odczytanaLiczba = static_cast<int>(bityLiczby.to_ulong());

        plik_odczytu.close();

        //std::cout << "Odczytana liczba: " << odczytanaLiczba << std::endl;

        return odczytanaLiczba;
    }
    else 
    {
        std::cerr << "Blad podczas otwierania pliku do odczytu!" << std::endl;
        return 0;
    }
}