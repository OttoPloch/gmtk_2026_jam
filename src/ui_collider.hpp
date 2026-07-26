#pragma once

#include "ui_element.hpp"
#include <SFML/Graphics/Rect.hpp>

class UICollider : public UIElement
{
public:
    UICollider(std::string group, UIManager* uiManager, SoundPlayer* soundPlayer, sf::RenderWindow* window, sf::FloatRect rect, bool vertical, bool setHeightManually = false);

    bool onEnter();

    void update();

    void draw(sf::RenderWindow& window) override;
private:
    void updateVisuals() override;

    sf::RenderWindow* window;

    bool collides;
    bool collidedLastFrame;

    sf::RectangleShape indicator;
    sf::RectangleShape debug;

    bool vertical;
};