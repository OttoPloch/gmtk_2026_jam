#pragma once

#include "level.hpp"

class UIButton;
class UIDial;

class Level1 : public Level
{
public:
    Level1();

    Level1(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager);

    void setup() override;

    void update() override;
private:
    UIButton* launchButton;

    float powerLevel;
    UIDial* powerDial;
};