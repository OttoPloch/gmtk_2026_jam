#include "level.hpp"
#include "defaults.hpp"
#include "launch_pad.hpp"
#include "ui_manager.hpp"

Level::Level() {}

Level::Level(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager) : window(window), launchPad(launchPad), uiManager(uiManager) {}

void Level::setup()
{
    uiManager->clearUI();

    uiManager->addUIText("INFO TEXT", {{0, 0}, {300, 1}}, "DEFAULT LEVEL", true, sf::Color::White);

    uiManager->addUIBackground("BG", {{59, 100}, {100, 100}}, defaultTexCoords.bg, 'l');
}

void Level::update()
{
    
}