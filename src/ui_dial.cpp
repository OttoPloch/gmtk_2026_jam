#include "ui_dial.hpp"
#include "sound_player.hpp"
#include "utils.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Mouse.hpp>

UIDial::UIDial(SoundPlayer* soundPlayer, sf::RenderWindow* window, sf::Texture* texture, sf::FloatRect rect, bool sizeIsScale, std::vector<sf::IntRect> texCoords, int minValue, int maxValue, float valueScale) : UIElement(soundPlayer, rect), window(window), dial(*texture), texCoords(texCoords), minValue(minValue), maxValue(maxValue), valueScale(valueScale)
{
    if (sizeIsScale) rect.size = {texCoords[0].size.x * rect.size.x, texCoords[0].size.y * rect.size.y};

    setRect(rect, texCoords[0]);

    value = 0;
    prevAngle = 0;
}

void UIDial::update()
{
    sf::Vector2f center = {rect.position.x + rect.size.x / 2.f, rect.position.y + rect.size.y / 2.f};

    if (circleMouseCollide(center, center.x - rect.position.x, *window))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            if (!clicked && canClick)
            {
                clicked = true;
                prevAngle = getMouseAngle();
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

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) clicked = false;

    if (clicked)
    {
        int angle = getMouseAngle();
        int diff = angle - prevAngle;
        prevAngle = angle;

        if (std::abs(diff) > 180) diff = 0;

        value += diff * valueScale;

        if (value < minValue) value = minValue;
        if (value > maxValue) value = maxValue;

        float step = (360. * valueScale) / texCoords.size();
        int index = std::fmod(value, 360. * valueScale) / step;
        if (index < 0) index = texCoords.size() + index;

        if (lastIndex != index) soundPlayer->play("dial spin");

        setTexCoords(texCoords[index]);

        lastIndex = index;
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

void UIDial::updateVisuals()
{
    setRect(rect);
}