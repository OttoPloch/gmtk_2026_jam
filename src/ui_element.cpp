#include "ui_element.hpp"
#include "sound_player.hpp"

UIElement::UIElement() {}

UIElement::UIElement(std::string group, UIManager* uiManager, SoundPlayer* soundPlayer, sf::FloatRect rect) : group(group), uiManager(uiManager), soundPlayer(soundPlayer), rect(rect), position(rect.position), offset(0, 0) {}

void UIElement::setPos(sf::Vector2f pos)
{
    rect.position = pos;

    updateVisuals();
}

void UIElement::move(sf::Vector2f dist)
{
    rect.position += dist;

    updateVisuals();
}

void UIElement::setOffset(sf::Vector2f offset)
{
    this->offset = offset;

    rect.position = position + offset;

    updateVisuals();
}

void UIElement::changeOffset(sf::Vector2f amount)
{
    setOffset(offset + amount);
}

void UIElement::updateVisuals()
{

}

void UIElement::draw(sf::RenderWindow& window)
{

}

sf::Vector2f UIElement::getOffset()
{
    return offset;
}

sf::FloatRect UIElement::getRect()
{
    return rect;
}