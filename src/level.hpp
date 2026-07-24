#pragma once

class LaunchPad;
class UIManager;

class Level
{
public:
    Level();

    Level(LaunchPad* launchPad, UIManager* uiManager);

    void update();
private:
    LaunchPad* launchPad;
    UIManager* uiManager;
};