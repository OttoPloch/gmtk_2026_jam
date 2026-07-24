#pragma once

#include <SFML/Graphics.hpp>

class LaunchPad;
class UIManager;

class Level
{
public:
    Level();

    Level(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager);

    virtual void setup();

    virtual void update();
protected:
    sf::RenderWindow* window;
    LaunchPad* launchPad;
    UIManager* uiManager;
};