#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "ui_element.hpp"

class UIButton : public UIElement
{
public:
    UIButton(SoundPlayer* soundPlayer, sf::RenderWindow* window, sf::Texture* texture, sf::FloatRect rect, bool sizeIsScale, std::array<sf::IntRect, 3> texCoords, float timeToRelease = 1.f);

    void update(float dt);

    void draw(sf::RenderWindow& window);

    bool isDown();
private:
    void setRect(sf::FloatRect newRect, sf::IntRect newTexCoords);
    void setRect(sf::FloatRect newRect);
    
    void setTexCoords(sf::IntRect newTexCoords);

    void updateVisuals() override;

    sf::RenderWindow* window;

    sf::Sprite button;
    std::array<sf::IntRect, 3> texCoords;

    float timeToRelease;
    float timeSincePressed;

    bool down;
    bool canClick;
};