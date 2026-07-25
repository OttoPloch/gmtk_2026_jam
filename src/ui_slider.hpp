#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "defaults.hpp"
#include "ui_element.hpp"

class UISlider : public UIElement
{
public:
    // baseEmptyPoint and baseFullPoint are percents of the texture rect
    UISlider(sf::RenderWindow* window, sf::Texture* texture, sf::FloatRect rect, bool sizeIsScale, SliderTemplate sliderTemplate);

    void update();

    void draw(sf::RenderWindow& window);
private:
    void setRect(sf::FloatRect newRect);

    void updateVisuals() override;

    sf::RenderWindow* window;

    sf::Sprite handle;
    sf::Sprite baseLeft; // left or bottom
    sf::Sprite baseMiddle;
    sf::Sprite baseRight; // right or top

    sf::Vector2f empty;
    sf::Vector2f full;
    float diff;

    sf::Vector2f baseMiddlePositionOffset;
    sf::Vector2f baseRightPositionOffset; // right or top

    sf::Vector2f scale;


    bool grabbed;
    sf::Vector2f grabOffset;
    bool canGrab;

    // percent
    float value;

    SliderTemplate sliderTemplate;
};