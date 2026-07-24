#include "level.hpp"
#include "launch_pad.hpp"
#include "ui_manager.hpp"

Level::Level() {}

Level::Level(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager) : window(window), launchPad(launchPad), uiManager(uiManager) {}

void Level::setup()
{
    uiManager->clearUI();

    uiManager->addUIText("INFO TEXT", {{0, 0}, {300, 1}}, "DEFAULT LEVEL CONFIG", true, sf::Color::White);
}

void Level::update()
{
    
}