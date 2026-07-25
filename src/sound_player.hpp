#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <map>

class SoundPlayer
{
public:
    SoundPlayer();

    void play(std::string soundName);

    void update();
private:
    std::map<std::string, sf::SoundBuffer> sounds;

    std::vector<std::unique_ptr<sf::Sound>> players;
};