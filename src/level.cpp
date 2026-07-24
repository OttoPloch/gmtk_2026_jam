#include "level.hpp"
#include "launch_pad.hpp"
#include "ui_manager.hpp"

Level::Level() {}

Level::Level(LaunchPad* launchPad, UIManager* uiManager) : launchPad(launchPad), uiManager(uiManager) {}

void Level::update()
{
    UIButton* launchButton = uiManager->getUIButton("launch");

    if (launchButton && launchButton->isDown())
    {
        launchPad->launch();
    }
}