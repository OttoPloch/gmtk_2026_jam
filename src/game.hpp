#pragma once

#include <SFML/Graphics.hpp>
#include "launch_pad.hpp"
#include "window.hpp"

class Game
{
public:
    Game();

    void start();

private:
    void run();

    void update();

    void draw();

    void quit();

    Window window;
    LaunchPad launchPad;
};