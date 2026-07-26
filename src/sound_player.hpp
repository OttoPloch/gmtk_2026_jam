#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <map>

class SoundPlayer
{
public:
    SoundPlayer();

    void play(std::string soundName);

    void stopAll();

    void pauseAll();

    void playAll();

    void update();

    std::unique_ptr<sf::Sound> tickPlayer;
private:
    std::map<std::string, sf::SoundBuffer> sounds;

    std::vector<std::pair<std::string, std::unique_ptr<sf::Sound>>> players;
};