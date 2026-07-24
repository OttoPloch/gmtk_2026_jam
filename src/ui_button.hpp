#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class UIButton
{
public:
    UIButton(sf::RenderWindow* window, sf::Texture* texture, sf::FloatRect rect, bool sizeIsScale, std::array<sf::IntRect, 3> texCoords, float timeToRelease = 1.f);

    void update(float dt);

    void draw(sf::RenderWindow& window);

    bool isDown();
private:
    void setRect(sf::FloatRect newRect, sf::IntRect newTexCoords);
    void setRect(sf::FloatRect newRect);
    
    void setTexCoords(sf::IntRect newTexCoords);

    sf::RenderWindow* window;

    sf::Sprite button;
    sf::FloatRect rect;
    std::array<sf::IntRect, 3> texCoords;

    float timeToRelease;
    float timeSincePressed;

    bool down;
};