#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

class UIText
{
public:
    UIText(sf::FloatRect rect, sf::Font* font, std::string content, bool autoSetHeight = true, sf::Color color = sf::Color(60, 255, 60));

    void update();

    void draw(sf::RenderWindow& window);

    sf::FloatRect getRect();

    float* valueRead;
    bool valueInDegrees;
    int valueDecimals;
private:
    void setRect(sf::FloatRect newRect, bool autoSetHeight = true);

    void fitRect();

    sf::FloatRect rect;
    std::string content;

    sf::Text text;
};