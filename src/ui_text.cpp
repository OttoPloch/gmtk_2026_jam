#include "ui_text.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <iostream>

UIText::UIText(sf::FloatRect rect, sf::Font* font, std::string content, bool autoSetHeight, sf::Color color) : rect(rect), content(content), text(*font, content, 300)
{
    text.setFillColor(color);

    setRect(rect, autoSetHeight);

    valueRead = nullptr;
    valueInDegrees = false;
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

        text.setString(content);

        // fitRect();
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

void UIText::setRect(sf::FloatRect newRect, bool autoSetHeight)
{
    rect = newRect;
    
    if (autoSetHeight)
    {
        rect.size.y = rect.size.x / (text.getGlobalBounds().size.x / text.getGlobalBounds().size.y);
    }

    text.setPosition(rect.position);
    text.setScale({rect.size.x / text.getGlobalBounds().size.x, rect.size.y / text.getGlobalBounds().size.y});

    text.setOrigin(text.getLocalBounds().position);
}

void UIText::fitRect()
{
    std::cout << "//\n";
    std::cout << text.getGlobalBounds().size.x << ", " << text.getGlobalBounds().size.y << '\n';
    std::cout << rect.size.x << ", " << rect.size.y << '\n';

    sf::Vector2f center = {rect.position.x + rect.size.x / 2.f, rect.position.y + rect.size.y / 2.f};

    rect.size = {100, 1};
    rect.position = {center.x - rect.size.x / 2.f, center.y};

    setRect(rect);
}