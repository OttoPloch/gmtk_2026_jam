#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "ui_element.hpp"

class UIText : public UIElement
{
public:
    UIText(SoundPlayer* soundPlayer, sf::FloatRect rect, sf::Font* font, std::string content, bool autoSetHeight = true, sf::Color color = sf::Color(60, 255, 60));

    void update();

    void draw(sf::RenderWindow& window);

    sf::FloatRect getRect();

    float* valueRead;
    int* valueReadInt;
    bool valueInDegrees;
    bool valueInPercent;
    int valueDecimals;
private:
    void setRect(sf::FloatRect newRect, bool autoSetHeight = true);

    void updateVisuals();

    std::string content;

    sf::Text text;
};