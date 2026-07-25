#include "ui_background.hpp"
#include <memory>

UIBackground::UIBackground(sf::Texture* texture, sf::FloatRect rect, BackgroundTemplate backgroundTemplate, char barOrientation, int barOffset, float scale) : UIElement(rect), backgroundTemplate(backgroundTemplate), barOrientation(barOrientation), barOffset(barOffset), scale(scale)
{
    for (int i = 0; i < 9; i++) sprites[i] = std::make_unique<sf::Sprite>(*texture);

    sprites[0]->setTextureRect({backgroundTemplate.texCoordOffset, {backgroundTemplate.texCoordSize, backgroundTemplate.texCoordSize}});
    sprites[1]->setTextureRect({{backgroundTemplate.texCoordOffset.x + backgroundTemplate.texCoordSize, backgroundTemplate.texCoordOffset.y}, {backgroundTemplate.texCoordSize, backgroundTemplate.texCoordSize}});
    sprites[2]->setTextureRect({{backgroundTemplate.texCoordOffset.x + backgroundTemplate.texCoordSize * 2, backgroundTemplate.texCoordOffset.y}, {backgroundTemplate.texCoordSize, backgroundTemplate.texCoordSize}});
    sprites[3]->setTextureRect({{backgroundTemplate.texCoordOffset.x, backgroundTemplate.texCoordOffset.y + backgroundTemplate.texCoordSize}, {backgroundTemplate.texCoordSize, backgroundTemplate.texCoordSize}});
    sprites[4]->setTextureRect({{backgroundTemplate.texCoordOffset.x + backgroundTemplate.texCoordSize, backgroundTemplate.texCoordOffset.y + backgroundTemplate.texCoordSize}, {backgroundTemplate.texCoordSize, backgroundTemplate.texCoordSize}});
    sprites[5]->setTextureRect({{backgroundTemplate.texCoordOffset.x + backgroundTemplate.texCoordSize * 2, backgroundTemplate.texCoordOffset.y + backgroundTemplate.texCoordSize}, {backgroundTemplate.texCoordSize, backgroundTemplate.texCoordSize}});
    sprites[6]->setTextureRect({{backgroundTemplate.texCoordOffset.x, backgroundTemplate.texCoordOffset.y + backgroundTemplate.texCoordSize * 2}, {backgroundTemplate.texCoordSize, backgroundTemplate.texCoordSize}});
    sprites[7]->setTextureRect({{backgroundTemplate.texCoordOffset.x + backgroundTemplate.texCoordSize, backgroundTemplate.texCoordOffset.y + backgroundTemplate.texCoordSize * 2}, {backgroundTemplate.texCoordSize, backgroundTemplate.texCoordSize}});
    sprites[8]->setTextureRect({{backgroundTemplate.texCoordOffset.x + backgroundTemplate.texCoordSize * 2, backgroundTemplate.texCoordOffset.y + backgroundTemplate.texCoordSize * 2}, {backgroundTemplate.texCoordSize, backgroundTemplate.texCoordSize}});

    resize(rect.size);

    if (barOrientation != 'n')
    {
        bar1 = std::make_unique<sf::Sprite>(*texture);
        bar2 = std::make_unique<sf::Sprite>(*texture);
    }

    updateVisuals();
}

void UIBackground::draw(sf::RenderWindow& window)
{
    if (barOrientation == 'l' || barOrientation == 't')
    {
        if (bar1) window.draw(*bar1);
        if (bar2) window.draw(*bar2);
    }
    
    for (auto& s : sprites) window.draw(*s);
    
    if (barOrientation == 'r' || barOrientation == 'b')
    {
        if (bar1) window.draw(*bar1);
        if (bar2) window.draw(*bar2);
    }
}

void UIBackground::resize(sf::Vector2f newSize)
{
    rect.size = newSize;

    float cornerSize = backgroundTemplate.texCoordSize * scale;
    float middleLength = rect.size.x - cornerSize * 2;
    float middleHeight = rect.size.y - cornerSize * 2;

    sprites[0]->setScale({scale, scale});
    sprites[1]->setScale({(middleLength / backgroundTemplate.texCoordSize) * scale, scale});
    sprites[2]->setScale({scale, scale});
    sprites[3]->setScale({scale, (middleHeight / backgroundTemplate.texCoordSize) * scale});
    sprites[4]->setScale({(middleLength / backgroundTemplate.texCoordSize) * scale, (middleHeight / backgroundTemplate.texCoordSize) * scale});
    sprites[5]->setScale({scale, (middleHeight / backgroundTemplate.texCoordSize) * scale});
    sprites[6]->setScale({scale, scale});
    sprites[7]->setScale({(middleLength / backgroundTemplate.texCoordSize) * scale, scale});
    sprites[8]->setScale({scale, scale});

    updateVisuals();
}

void UIBackground::updateVisuals()
{
    float cornerSize = backgroundTemplate.texCoordSize * scale;

    sprites[0]->setPosition(rect.position);
    sprites[1]->setPosition({rect.position.x + cornerSize, rect.position.y});
    sprites[2]->setPosition({rect.position.x + rect.size.x - cornerSize, rect.position.y});
    sprites[3]->setPosition({rect.position.x, rect.position.y + cornerSize});
    sprites[4]->setPosition({rect.position.x + cornerSize, rect.position.y + cornerSize});
    sprites[5]->setPosition({rect.position.x + rect.size.x - cornerSize, rect.position.y + cornerSize});
    sprites[6]->setPosition({rect.position.x, rect.position.y + rect.size.y - cornerSize});
    sprites[7]->setPosition({rect.position.x + cornerSize, rect.position.y + rect.size.y - cornerSize});
    sprites[8]->setPosition({rect.position.x + rect.size.x - cornerSize, rect.position.y + rect.size.y - cornerSize});

    if (bar1 && bar2)
    {
        if (barOrientation == 'l')
        {
            bar1->setTextureRect(backgroundTemplate.horizontalBarTexCoords);
            bar2->setTextureRect(backgroundTemplate.horizontalBarTexCoords);
    
            bar1->setOrigin(static_cast<sf::Vector2f>(backgroundTemplate.horizontalBarLOrigin));
            bar2->setOrigin(static_cast<sf::Vector2f>(backgroundTemplate.horizontalBarLOrigin));
    
            bar1->setPosition(sf::Vector2f(sprites[0]->getGlobalBounds().position.x + backgroundTemplate.horizontalBar1LMargin.x, sprites[0]->getGlobalBounds().position.y + backgroundTemplate.horizontalBar1LMargin.y + barOffset));
            bar2->setPosition(sf::Vector2f(sprites[0]->getGlobalBounds().position.x + backgroundTemplate.horizontalBar2LMargin.x, sprites[6]->getGlobalBounds().position.y + sprites[6]->getGlobalBounds().size.y - backgroundTemplate.horizontalBar2LMargin.y - barOffset));
        }
        else if (barOrientation == 'r')
        {
            bar1->setTextureRect(backgroundTemplate.horizontalBarTexCoords);
            bar2->setTextureRect(backgroundTemplate.horizontalBarTexCoords);
    
            bar1->setOrigin(static_cast<sf::Vector2f>(backgroundTemplate.horizontalBarROrigin));
            bar2->setOrigin(static_cast<sf::Vector2f>(backgroundTemplate.horizontalBarROrigin));
    
            bar1->setPosition(sf::Vector2f(sprites[2]->getGlobalBounds().position.x + sprites[2]->getGlobalBounds().size.x + backgroundTemplate.horizontalBar1RMargin.x, sprites[0]->getGlobalBounds().position.y + static_cast<float>(backgroundTemplate.horizontalBar1RMargin.y + barOffset)));
            bar2->setPosition(sf::Vector2f(sprites[2]->getGlobalBounds().position.x + sprites[2]->getGlobalBounds().size.x + backgroundTemplate.horizontalBar2RMargin.x, sprites[6]->getGlobalBounds().position.y + sprites[6]->getGlobalBounds().size.y - (backgroundTemplate.horizontalBar2RMargin.y + barOffset)));
        }
        else if (barOrientation == 't')
        {
            bar1->setTextureRect(backgroundTemplate.VerticalBarTexCoords);
            bar2->setTextureRect(backgroundTemplate.VerticalBarTexCoords);
    
            bar1->setOrigin(static_cast<sf::Vector2f>(backgroundTemplate.verticalBarTOrigin));
            bar2->setOrigin(static_cast<sf::Vector2f>(backgroundTemplate.verticalBarTOrigin));
    
            bar1->setPosition(sf::Vector2f(sprites[0]->getGlobalBounds().position.x + backgroundTemplate.verticalBar1TMargin.x + barOffset, sprites[0]->getGlobalBounds().position.y + backgroundTemplate.verticalBar1TMargin.y));
            bar2->setPosition(sf::Vector2f(sprites[2]->getGlobalBounds().position.x + sprites[2]->getGlobalBounds().size.x - backgroundTemplate.verticalBar2TMargin.x - barOffset, sprites[0]->getGlobalBounds().position.y + backgroundTemplate.verticalBar2TMargin.y));
        }
        else if (barOrientation == 'b')
        {
            bar1->setTextureRect(backgroundTemplate.VerticalBarTexCoords);
            bar2->setTextureRect(backgroundTemplate.VerticalBarTexCoords);
    
            bar1->setOrigin(static_cast<sf::Vector2f>(backgroundTemplate.verticalBarBOrigin));
            bar2->setOrigin(static_cast<sf::Vector2f>(backgroundTemplate.verticalBarBOrigin));
    
            bar1->setPosition(sf::Vector2f(sprites[6]->getGlobalBounds().position.x + backgroundTemplate.verticalBar1BMargin.x + barOffset, sprites[6]->getGlobalBounds().position.y + sprites[6]->getGlobalBounds().size.y + backgroundTemplate.verticalBar1BMargin.y));
            bar2->setPosition(sf::Vector2f(sprites[8]->getGlobalBounds().position.x + sprites[8]->getGlobalBounds().size.x - backgroundTemplate.verticalBar2BMargin.x - barOffset, sprites[6]->getGlobalBounds().position.y + sprites[6]->getGlobalBounds().size.y + backgroundTemplate.verticalBar2BMargin.y));
        }
    }
}