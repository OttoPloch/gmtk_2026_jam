#pragma once

#include <SFML/Graphics.hpp>

class UIBackground
{
public:
    UIBackground(sf::Texture* texture, sf::FloatRect rect, int texCoordSize = 32, float scale = 1.f);

    void draw(sf::RenderWindow& window);
private:
    std::array<std::unique_ptr<sf::Sprite>, 9> sprites;
};