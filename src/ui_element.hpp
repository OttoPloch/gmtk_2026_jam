#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

class SoundPlayer;
class UIManager;

class UIElement
{
public:
    UIElement();

    UIElement(std::string group, UIManager* uiManager, SoundPlayer* soundPlayer, sf::FloatRect rect);

    void setPos(sf::Vector2f pos);

    void move(sf::Vector2f dist);

    void setOffset(sf::Vector2f offset);

    void changeOffset(sf::Vector2f amount);

    virtual void updateVisuals();

    virtual void draw(sf::RenderWindow& window);

    sf::Vector2f getOffset();

    sf::FloatRect getRect();
protected:
    std::string group;

    SoundPlayer* soundPlayer;
    UIManager* uiManager;

    sf::FloatRect rect;

    sf::Vector2f position;

    sf::Vector2f offset;
};