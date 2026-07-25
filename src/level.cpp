#include "level.hpp"
#include "defaults.hpp"
#include "launch_pad.hpp"
#include "ui_manager.hpp"

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
    uiManager->resetUI();
    uiManager->addUIText("INFO TEXT", {{0, 0}, {300, 1}}, "DEFAULT LEVEL", true, sf::Color::White);
    uiManager->addUIBackground("BG", {{59, 100}, {100, 100}}, defaultTexCoords.bg, 'l');
}

void Level::update(float dt, float time)
{
    timeTaken += dt;

    if (timeTaken >= timeToComplete && timeToComplete > 0)
    {
        launchPad->fail();
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