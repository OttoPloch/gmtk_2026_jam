#include "ui_button.hpp"
#include "utils.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

#include <iostream>

UIButton::UIButton(sf::RenderWindow* window, sf::Texture* texture, sf::FloatRect rect, bool sizeIsScale, std::array<sf::IntRect, 3> texCoords, float timeToRelease) : window(window), button(*texture), rect(rect), texCoords(texCoords), timeToRelease(timeToRelease)
{
    timeSincePressed = timeToRelease;

    if (sizeIsScale) rect.size = {texCoords[0].size.x * rect.size.x, texCoords[0].size.y * rect.size.y};

    setRect(rect, texCoords[0]);
    
    button.setOrigin({0, button.getTextureRect().size.y / 3.f});

    down = false;
    canClick = false;
}

void UIButton::update(float dt)
{
    down = false;

    if (mouseCollide({rect.position - button.getOrigin(), rect.size}, *window))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            if (timeSincePressed >= timeToRelease && canClick)
            {
                timeSincePressed = 0;
                setTexCoords(texCoords[2]);
                down = true;
            }

            canClick = false;
        }
        else
        {
            canClick = true;
        }
    }
    else
    {
        canClick = false;
    }

    timeSincePressed += dt;

    if (timeSincePressed >= timeToRelease - .1f)
    {
        setTexCoords(texCoords[0]);
    }
    else if (timeSincePressed > .2f && (!mouseCollide({rect.position - button.getOrigin(), rect.size}, *window) || !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)))
    {
        setTexCoords(texCoords[1]);
    }
}

void UIButton::draw(sf::RenderWindow& window)
{
    window.draw(button);
}

bool UIButton::isDown()
{
    return down;
}

void UIButton::setRect(sf::FloatRect newRect, sf::IntRect newTexCoords)
{
    rect = newRect;

    button.setTextureRect(newTexCoords);

    button.setPosition(rect.position);
    button.setScale({rect.size.x / button.getTextureRect().size.x, rect.size.y / button.getTextureRect().size.y});
}

void UIButton::setRect(sf::FloatRect newRect)
{
    setRect(newRect, button.getTextureRect());
}

void UIButton::setTexCoords(sf::IntRect newTexCoords)
{
    setRect(rect, newTexCoords);
}