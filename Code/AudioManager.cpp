// AudioManager.cpp
#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager()
{
    // Konstruktor, jeśli potrzebne
    actualVolume = 50.f;
}

AudioManager::~AudioManager()
{
    // Destruktor, jeśli potrzebne
}

void AudioManager::loadSound(const std::string &soundKey, const std::string &filePath)
{
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(filePath))
    {
        soundBuffers[soundKey] = buffer;
    }
    else
    {
        // Obsłuż błąd ładowania dźwięku
    }
}

void AudioManager::playSound(const std::string &soundKey)
{
    auto it = soundBuffers.find(soundKey);
    if (it != soundBuffers.end())
    {
        sf::Sound sound;
        sound.setBuffer(it->second);

        sound.play();
        sounds[soundKey] = sound;
    }
    else
    {
        // Obsłuż błąd - dźwięk o danym kluczu nie został załadowany
    }
}

void AudioManager::playMusic(const std::string &musicFilePath)
{
    if (music.openFromFile(musicFilePath))
    {
        //music.setLoop(true);
        music.setVolume(actualVolume);
        music.play();
    }
    else
    {
        // Obsłuż błąd - nie udało się otworzyć pliku muzycznego
        std::cerr << "Error: Unable to open music file: " << musicFilePath << std::endl;
    }
}

void AudioManager::stopMusic()
{
    music.stop();
}
void AudioManager::emitCollisionSound()
{
    playSound("collision_sound"); // Ustaw nazwę klucza dla dźwięku kolizji
}

void AudioManager::emitBuildSound()
{
    playSound("towerPlacingSound.mp3");
}