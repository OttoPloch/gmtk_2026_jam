#pragma once

#include <SFML/Graphics.hpp>
#include "launch_pad.hpp"
#include "window.hpp"
#include "random.hpp"
#include "ui_manager.hpp"
#include "level.hpp"

class Game
{
public:
    Game();

    void start();
private:
    void run();

    void events();

    void update();

    void draw();

    void quit();

    Window window;
    LaunchPad launchPad;
    Random random;
    UIManager uiManager;
    std::vector<std::unique_ptr<Level>> levels;
    int currLevel;

    sf::Clock dtClock;
    float dt;

    sf::Clock gameClock;
};