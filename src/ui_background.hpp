#pragma once

#include "defaults.hpp"
#include <SFML/Graphics.hpp>
#include "ui_element.hpp"

class UIBackground : public UIElement
{
public:
    UIBackground(sf::Texture* texture, sf::FloatRect rect, BackgroundTemplate backgroundTemplate, char barOrientation = 'n', int barOffset = 5, float scale = 1.f);

    void draw(sf::RenderWindow& window);

    void resize(sf::Vector2f newSize);
private:
    void updateVisuals() override;

    std::array<std::unique_ptr<sf::Sprite>, 9> sprites;

    std::unique_ptr<sf::Sprite> bar1;
    std::unique_ptr<sf::Sprite> bar2;
    
    char barOrientation;

    BackgroundTemplate backgroundTemplate;
    float scale;
    int barOffset;
};