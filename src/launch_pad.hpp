#pragma once

#include <SFML/Graphics.hpp>

class LaunchPad
{
public:
    LaunchPad();

    void reset();

    void launch();

    void update();

    void draw(sf::RenderWindow& window);

    sf::Vector2u getBackgroundSize();
private:
    sf::Texture bgTexture;
    sf::Sprite background;

    sf::Texture launchPadTexture;
    sf::Sprite launchPad;

    sf::Texture rocketTexture;
    sf::Sprite rocket;

    const sf::Vector2f rocketStartPosition;
    const float rocketStartSpeed;
    const float rocketSpeedMultiplier;
    
    bool launching;
    float rocketSpeed;
};