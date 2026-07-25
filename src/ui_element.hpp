#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

class UIElement
{
public:
    UIElement();

    UIElement(sf::FloatRect rect);

    void setPos(sf::Vector2f pos);

    void move(sf::Vector2f dist);

    void setOffset(sf::Vector2f offset);

    void changeOffset(sf::Vector2f amount);

    virtual void updateVisuals();

    sf::Vector2f getOffset();
protected:
    sf::FloatRect rect;

    sf::Vector2f position;

    sf::Vector2f offset;
};