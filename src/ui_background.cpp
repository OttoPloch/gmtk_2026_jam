#include "ui_background.hpp"

UIBackground::UIBackground(sf::Texture* texture, sf::FloatRect rect, int texCoordSize, sf::Vector2i texCoordOffset, float scale)
{
    for (int i = 0; i < 9; i++) sprites[i] = std::make_unique<sf::Sprite>(*texture);

    sprites[0]->setTextureRect({texCoordOffset, {texCoordSize, texCoordSize}});
    sprites[1]->setTextureRect({{texCoordOffset.x + texCoordSize, texCoordOffset.y}, {texCoordSize, texCoordSize}});
    sprites[2]->setTextureRect({{texCoordOffset.x + texCoordSize * 2, texCoordOffset.y}, {texCoordSize, texCoordSize}});
    sprites[3]->setTextureRect({{texCoordOffset.x, texCoordOffset.y + texCoordSize}, {texCoordSize, texCoordSize}});
    sprites[4]->setTextureRect({{texCoordOffset.x + texCoordSize, texCoordOffset.y + texCoordSize}, {texCoordSize, texCoordSize}});
    sprites[5]->setTextureRect({{texCoordOffset.x + texCoordSize * 2, texCoordOffset.y + texCoordSize}, {texCoordSize, texCoordSize}});
    sprites[6]->setTextureRect({{texCoordOffset.x, texCoordOffset.y + texCoordSize * 2}, {texCoordSize, texCoordSize}});
    sprites[7]->setTextureRect({{texCoordOffset.x + texCoordSize, texCoordOffset.y + texCoordSize * 2}, {texCoordSize, texCoordSize}});
    sprites[8]->setTextureRect({{texCoordOffset.x + texCoordSize * 2, texCoordOffset.y + texCoordSize * 2}, {texCoordSize, texCoordSize}});

    float cornerSize = texCoordSize * scale;
    float middleLength = rect.size.x - cornerSize * 2;
    float middleHeight = rect.size.y - cornerSize * 2;


    sprites[0]->setScale({scale, scale});
    sprites[1]->setScale({(middleLength / texCoordSize) * scale, scale});
    sprites[2]->setScale({scale, scale});
    sprites[3]->setScale({scale, (middleHeight / texCoordSize) * scale});
    sprites[4]->setScale({(middleLength / texCoordSize) * scale, (middleHeight / texCoordSize) * scale});
    sprites[5]->setScale({scale, (middleHeight / texCoordSize) * scale});
    sprites[6]->setScale({scale, scale});
    sprites[7]->setScale({(middleLength / texCoordSize) * scale, scale});
    sprites[8]->setScale({scale, scale});

    sprites[0]->setPosition(rect.position);
    sprites[1]->setPosition({rect.position.x + cornerSize, rect.position.y});
    sprites[2]->setPosition({rect.position.x + rect.size.x - cornerSize, rect.position.y});
    sprites[3]->setPosition({rect.position.x, rect.position.y + cornerSize});
    sprites[4]->setPosition({rect.position.x + cornerSize, rect.position.y + cornerSize});
    sprites[5]->setPosition({rect.position.x + rect.size.x - cornerSize, rect.position.y + cornerSize});
    sprites[6]->setPosition({rect.position.x, rect.position.y + rect.size.y - cornerSize});
    sprites[7]->setPosition({rect.position.x + cornerSize, rect.position.y + rect.size.y - cornerSize});
    sprites[8]->setPosition({rect.position.x + rect.size.x - cornerSize, rect.position.y + rect.size.y - cornerSize});
}

void UIBackground::draw(sf::RenderWindow& window)
{
    for (auto& s : sprites) window.draw(*s);
}