#include "ui_button.hpp"
#include "utils.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

UIButton::UIButton(sf::RenderWindow* window, sf::Texture* texture, sf::FloatRect rect, std::array<sf::IntRect, 3> texCoords, float timeToRelease) : window(window), button(*texture), rect(rect), texCoords(texCoords), timeToRelease(timeToRelease)
{
    timeSincePressed = timeToRelease;

    setRect(rect, texCoords[0]);
}

void UIButton::update(float dt)
{
    if (mouseCollide(rect, *window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && timeSincePressed >= timeToRelease)
    {
        std::cout << timeSincePressed << '\n';

        timeSincePressed = 0;

        setTexCoords(texCoords[2]);
    }
    else
    {
        timeSincePressed += dt;

        if (timeSincePressed >= timeToRelease - .1f)
        {
            setTexCoords(texCoords[0]);
        }
        else if (timeSincePressed > .2f && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            setTexCoords(texCoords[1]);
        }
    }
}

void UIButton::draw(sf::RenderWindow& window)
{
    window.draw(button);
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