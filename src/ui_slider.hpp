#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "defaults.hpp"

class UISlider
{
public:
    // baseEmptyPoint and baseFullPoint are percents of the texture rect
    UISlider(sf::RenderWindow* window, sf::Texture* texture, sf::FloatRect rect, bool sizeIsScale, SliderTemplate sliderTemplate);

    void update();

    void draw(sf::RenderWindow& window);
private:
    sf::RenderWindow* window;

    sf::Sprite handle;
    sf::Sprite baseLeft; // left or bottom
    sf::Sprite baseMiddle;
    sf::Sprite baseRight; // right or top

    sf::FloatRect rect;

    sf::IntRect handleTexCoords;
    std::array<sf::IntRect, 3> baseTexCoords;

    sf::Vector2f empty;
    sf::Vector2f full;
    float diff;

    sf::Vector2f baseMiddlePositionOffset;
    sf::Vector2f baseRightPositionOffset; // right or top

    sf::Vector2f scale;

    bool vertical; // false = horizontal


    bool grabbed;
    sf::Vector2f grabOffset;

    // percent
    float value;
};