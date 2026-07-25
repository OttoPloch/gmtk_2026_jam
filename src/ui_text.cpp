#include "ui_text.hpp"
#include "ui_element.hpp"
#include <SFML/Graphics/Rect.hpp>

UIText::UIText(SoundPlayer* soundPlayer, sf::FloatRect rect, sf::Font* font, std::string content, char autoSet, sf::Color color) : UIElement(soundPlayer, rect), content(content), text(*font, content, 300)
{
    text.setFillColor(color);

    setRect(rect, autoSet);

    valueRead = nullptr;
    valueReadInt = nullptr;
    valueInDegrees = false;
    valueInPercent = false;
    valueDecimals = 2;
}

void UIText::update()
{
    if (valueRead)
    {
        double scale = 1 / pow(10, valueDecimals);
        float adjustedVal = static_cast<int>(*valueRead / scale) * scale;
        
        content = std::to_string(adjustedVal);

        while (content.at(content.size() - 1) == '0') content.erase(content.size() - 1);
        if (content.at(content.size() - 1) == '.') content.erase(content.size() - 1);

        if (valueInDegrees) content += "°";
        if (valueInPercent) content += "%";
        
        text.setString(content);
    }
    else if (valueReadInt)
    {
        content = std::to_string(*valueReadInt);
        
        if (valueInDegrees) content += "°";
        if (valueInPercent) content += "%";

        text.setString(content);
    }
}

void UIText::draw(sf::RenderWindow& window)
{
    window.draw(text);
}

sf::FloatRect UIText::getRect()
{
    return rect;
}

void UIText::setString(std::string newContent)
{
    content = newContent;

    text.setString(content);
}

void UIText::setRect(sf::FloatRect newRect, char autoSet)
{
    rect = newRect;
    
    if (autoSet == 'h')
    {
        rect.size.y = rect.size.x / (text.getGlobalBounds().size.x / text.getGlobalBounds().size.y);
    }
    else if (autoSet == 'l')
    {
        rect.size.x = rect.size.y * (text.getGlobalBounds().size.x / text.getGlobalBounds().size.y);
    }

    text.setPosition(rect.position);
    text.setScale({rect.size.x / text.getGlobalBounds().size.x, rect.size.y / text.getGlobalBounds().size.y});

    text.setOrigin(text.getLocalBounds().position);
}

void UIText::updateVisuals()
{
    text.setPosition(rect.position);
}