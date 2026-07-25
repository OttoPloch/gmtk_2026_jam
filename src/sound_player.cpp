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
        {"tick", sf::SoundBuffer("assets/sounds/short tick.mp3")},
        {"slider", sf::SoundBuffer("assets/sounds/506054__mellau__button-click-1.wav")}
    };

    tickPlayer = std::make_unique<sf::Sound>(sounds["tick"]);
}

void SoundPlayer::play(std::string soundName)
{
    if (sounds.find(soundName) != sounds.end())
    {
        auto& p = players.emplace_back(soundName, std::make_unique<sf::Sound>(sounds[soundName]));

        p.second->play();
    }
}

void SoundPlayer::stopAll()
{
    std::vector<int> playersToRemove;

    for (int i = 0; i < players.size(); i++)
    {
        if (players[i].first != "level finish")
        {
            playersToRemove.emplace_back(i);
        }
    }

    for (auto& i : playersToRemove)
    {
        players.erase(players.begin() + i);
    }

    if (tickPlayer) tickPlayer->stop();
}

void SoundPlayer::update()
{
    std::vector<int> playersToRemove;

    for (int i = 0; i < players.size(); i++)
    {
        if (players[i].second->getStatus() == sf::Sound::Status::Stopped)
        {
            playersToRemove.emplace_back(i);
        }
    }

    for (auto i : playersToRemove)
    {
        players.erase(players.begin() + i);
    }
}