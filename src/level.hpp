#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class LaunchPad;
class UIManager;

class Level
{
public:
    Level();

    Level(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager);

    void setup(std::string startAnimationKey = "none", int animLayer = 0);

    virtual void createUI();
    
    virtual void update(float dt, float time);

    // layer is what it effects. 0 is all, 1 is panel1, 2 is panel2, etc.
    void beginAnimation(std::string key, int layer);
protected:
    sf::RenderWindow* window;
    LaunchPad* launchPad;
    UIManager* uiManager;

    std::map<int, std::vector<std::pair<std::string, float>>> animations;
};