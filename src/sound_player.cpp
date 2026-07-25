#include "sound_player.hpp"
#include <SFML/Audio/SoundBuffer.hpp>

SoundPlayer::SoundPlayer()
{
    sounds = {
        {"button", sf::SoundBuffer("assets/sounds/152535__dwoboyle__electronics-flashlight-plastic-button-03.wav")},
        {"level finish", sf::SoundBuffer("assets/sounds/completetask_0.mp3")},
        {"dial spin", sf::SoundBuffer("assets/sounds/zipclick.flac")},
        {"launch", sf::SoundBuffer("assets/sounds/launch modified.mp3")},
        {"pop", sf::SoundBuffer("assets/sounds/744144__nomentero__bubble-pop-6.wav")},
        {"tick", sf::SoundBuffer("assets/sounds/short tick.mp3")}
    };

    tickPlayer = std::make_unique<sf::Sound>(sounds["tick"]);
}

void SoundPlayer::play(std::string soundName)
{
    if (sounds.find(soundName) != sounds.end())
    {
        auto& p = players.emplace_back(std::make_unique<sf::Sound>(sounds[soundName]));

        p->play();
    }
}

void SoundPlayer::update()
{
    std::vector<int> playersToRemove;

    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->getStatus() == sf::Sound::Status::Stopped)
        {
            playersToRemove.emplace_back(i);
        }
    }

    for (auto i : playersToRemove)
    {
        players.erase(players.begin() + i);
    }
}