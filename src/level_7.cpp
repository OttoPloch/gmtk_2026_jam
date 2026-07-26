#include "level_7.hpp"
#include "launch_pad.hpp"
#include "ui_manager.hpp"
#include <iostream>

Level7::Level7() {}

Level7::Level7(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager, float timeToComplete) : Level(window, launchPad, uiManager, timeToComplete)
{}

void Level7::createUI()
{
    uiManager->resetUI();

    if (!endScreenTexture.loadFromFile("assets/space.png"))
    {
        std::cout << "ERROR loading end screen texture.\n";
    }
    endScreen = std::make_unique<sf::Sprite>(endScreenTexture);

}

void Level7::specificUpdate(float dt, float time)
{

}

void Level7::draw()
{
    window->draw(*endScreen);
}