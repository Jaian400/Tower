// AudioManager.h
#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <SFML/Audio.hpp>
#include <unordered_map>

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();

    void loadSound(const std::string &soundKey, const std::string &filePath);
    void playSound(const std::string &soundKey);
    void playMusic(const std::string &musicFilePath);
    void stopMusic();
    void setVolume(float volume);
    void emitCollisionSound();
    void emitBuildSound();
    float actualVolume;

private:
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    std::unordered_map<std::string, sf::Sound> sounds;
    sf::Music music;
};

#endif // AUDIO_MANAGER_H
