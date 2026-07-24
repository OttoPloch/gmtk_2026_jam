#include "levels.hpp"
#include "defaults.hpp"
#include "launch_pad.hpp"
#include "ui_manager.hpp"
#include "ui_button.hpp"
#include "ui_dial.hpp"

Level1::Level1() {}

Level1::Level1(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager) : Level(window, launchPad, uiManager),
powerLevel(0)
{}

void Level1::setup()
{
    uiManager->clearUI();

    uiManager->addUIBackground("bg", {{10, 10}, {120, 80}}, defaultTexCoords.bgSmallTexCoordSize, defaultTexCoords.bgSmallTexCoordOffset);
    launchButton = uiManager->addUIButton("launch", window, {{20, 58}, {1, 1}}, true, defaultTexCoords.buttonTexCoords);
    powerDial = uiManager->addUIDial("dial", window, {{65, 60}, {1, 1}}, true, defaultTexCoords.dialSmallTexCoords, 0, 100, 100./360/3);
    uiManager->addUISlider("slider", window, {{90, 58}, {1, 1}}, true, defaultTexCoords.smallHorizontalSlider);
    uiManager->addUISlider("slider2", window, {{90, 72}, {1, 1}}, true, defaultTexCoords.smallHorizontalSlider);
    UIText* text = uiManager->addUIText("text", {{68, 50}, {10, 100}}, "100");
    uiManager->addUIBackground("bg2", {{text->getRect().position.x - 3, text->getRect().position.y - 3}, {text->getRect().size.x + 6, text->getRect().size.y + 6}}, defaultTexCoords.bgTextTexCoordSize, defaultTexCoords.bgTextTexCoordOffet);

    text->valueRead = &powerLevel;
}

void Level1::update()
{
    powerLevel = powerDial->getValue();

    if (launchButton && launchButton->isDown()) launchPad->launch();
}