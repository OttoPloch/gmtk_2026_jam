#include "level.hpp"
#include "launch_pad.hpp"
#include "ui_manager.hpp"
#include "sound_player.hpp"

Level::Level() {}

Level::Level(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager, float timeToComplete) : window(window), launchPad(launchPad), uiManager(uiManager), timeToComplete(timeToComplete) {}

void Level::setup(std::string startAnimationKey, int animLayer)
{
    animations.clear();
    
    if (startAnimationKey != "none")
    {
        beginAnimation(startAnimationKey, animLayer);
    }

    launchPad->reset();

    timeTaken = 0;

    createUI();
}

void Level::createUI()
{
    uiManager->addUIText("TEXT", {{0, 0}, {50, 1}}, "DEFAULT LEVEL", true, sf::Color::White);
}

void Level::update(float dt, float time)
{
    if (!launchPad->launching && !launchPad->failing) timeTaken += dt;
    else launchPad->soundPlayer->tickPlayer->stop();

    if (timeToComplete > 0)
    {
        if (timeTaken >= timeToComplete)
        {
            launchPad->fail();
            
            beginAnimation("hide all", 0);
        }
        else if (timeToComplete - timeTaken <= 5 && !launchPad->launching && !launchPad->failing && launchPad->soundPlayer->tickPlayer->getStatus() == sf::Sound::Status::Stopped)
        {
            launchPad->soundPlayer->tickPlayer->play();
        }
    }


    specificUpdate(dt, time);
}

void Level::specificUpdate(float dt, float time)
{

}

void Level::beginAnimation(std::string key, int layer)
{
    animations[layer].emplace_back(key, 0);
}

float Level::timeRemainingPercent()
{
    if (timeToComplete <= 0) return 1;

    return (timeToComplete - timeTaken) / timeToComplete;
}