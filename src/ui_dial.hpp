#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>

class UIDial
{
public:
    UIDial(sf::RenderWindow* window, sf::Texture* texture, sf::FloatRect rect, bool sizeIsScale, std::vector<sf::IntRect> texCoords, int minValue, int maxValue, float valueScale = 1);

    void update();

    void draw(sf::RenderWindow& window);

    int getValue();
private:
    void setRect(sf::FloatRect newRect, sf::IntRect newTexCoords);

    void setRect(sf::FloatRect newRect);

    void setTexCoords(sf::IntRect newTexCoords);

    int getMouseAngle();

    sf::RenderWindow* window;

    sf::Sprite dial;

    sf::FloatRect rect;

    std::vector<sf::IntRect> texCoords;

    float value;
    
    int minValue;
    int maxValue;
    float valueScale;

    bool clicked;
    int prevAngle;
    bool canClick;
};