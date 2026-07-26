#pragma once

#include <SFML/Graphics.hpp>
#include "launch_pad.hpp"
#include "window.hpp"
#include "random.hpp"
#include "ui_manager.hpp"
#include "level.hpp"
#include "sound_player.hpp"

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

    void loadLevels();

    Window window;
    LaunchPad launchPad;
    Random random;
    UIManager uiManager;
    std::vector<std::unique_ptr<Level>> levels;
    int currLevel;

    SoundPlayer soundPlayer;

    sf::Clock dtClock;
    float dt;

    sf::Clock gameClock;
};