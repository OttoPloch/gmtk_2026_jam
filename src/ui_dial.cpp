#include "ui_dial.hpp"
#include "utils.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Mouse.hpp>

UIDial::UIDial(sf::RenderWindow* window, sf::Texture* texture, sf::FloatRect rect, bool sizeIsScale, std::vector<sf::IntRect> texCoords) : window(window), dial(*texture), rect(rect), texCoords(texCoords)
{
    if (sizeIsScale) rect.size = {texCoords[0].size.x * rect.size.x, texCoords[0].size.y * rect.size.y};

    setRect(rect, texCoords[0]);

    value = 0;
    prevAngle = 0;
}

void UIDial::update()
{
    sf::Vector2f center = {rect.position.x + rect.size.x / 2.f, rect.position.y + rect.size.y / 2.f};

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (!clicked && circleMouseCollide(center, center.x - rect.position.x, *window))
        {
            clicked = true;

            prevAngle = getMouseAngle();
        }
    }
    else
    {
        clicked = false;
    }

    if (clicked)
    {
        int angle = getMouseAngle();
        int diff = angle - prevAngle;
        prevAngle = angle;

        if (std::abs(diff) > 180) diff = 0;

        value += diff;

        int step = std::ceil(360.f / texCoords.size());
        int index = std::fmod(value, 360) / step;
        if (index < 0) index = texCoords.size() + index;
        setTexCoords(texCoords[index]);
    }
}

void UIDial::draw(sf::RenderWindow& window)
{
    window.draw(dial);
}

int UIDial::getValue()
{
    return value;
}

void UIDial::setRect(sf::FloatRect newRect, sf::IntRect newTexCoords)
{
    rect = newRect;

    dial.setTextureRect(newTexCoords);

    dial.setPosition(rect.position);
    dial.setScale({rect.size.x / dial.getTextureRect().size.x, rect.size.y / dial.getTextureRect().size.y});
}

void UIDial::setRect(sf::FloatRect newRect)
{
    setRect(newRect, dial.getTextureRect());
}

void UIDial::setTexCoords(sf::IntRect newTexCoords)
{
    setRect(rect, newTexCoords);
}

int UIDial::getMouseAngle()
{
    sf::Vector2f center = {rect.position.x + rect.size.x / 2.f, rect.position.y + rect.size.y / 2.f};

    sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    float angle = getAngle(center, mousePos);
    if (angle < 0) angle = 360 + angle;

    return angle;
}