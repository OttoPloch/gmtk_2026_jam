#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include "ui_element.hpp"

class UIDial : public UIElement
{
public:
    UIDial(std::string group, UIManager* uiManager, SoundPlayer* soundPlayer, sf::RenderWindow* window, sf::Texture* texture, sf::FloatRect rect, bool sizeIsScale, std::vector<sf::IntRect> texCoords, int minValue, int maxValue, float valueScale = 1);

    void update();

    void draw(sf::RenderWindow& window) override;

    int getValue();

    void setValue(int newValue);
private:
    void setRect(sf::FloatRect newRect, sf::IntRect newTexCoords);

    void setRect(sf::FloatRect newRect);

    void setTexCoords(sf::IntRect newTexCoords);

    int getMouseAngle();

    void updateVisuals() override;

    sf::RenderWindow* window;

    sf::Sprite dial;

    int lastIndex;
    std::vector<sf::IntRect> texCoords;

    float value;
    
    int minValue;
    int maxValue;
    float valueScale;

    bool clicked;
    int prevAngle;
    bool canClick;
};