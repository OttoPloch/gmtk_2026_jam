#include "ui_collider.hpp"
#include "utils.hpp"

UICollider::UICollider(std::string group, UIManager* uiManager, SoundPlayer* soundPlayer, sf::RenderWindow* window, sf::FloatRect rect, bool vertical, bool setHeightManually) : UIElement(group, uiManager, soundPlayer, rect), window(window), vertical(vertical)
{
    collides = false;
    collidedLastFrame = false;

    indicator.setFillColor(sf::Color(25, 25, 25, 200));
    indicator.setPosition(rect.position);
    
    if (!setHeightManually)
    {
        if (vertical) indicator.setSize({5, rect.size.y});
        else indicator.setSize({rect.size.x, 5});
    }
    else
    {
        indicator.setSize(rect.size);
    }

    debug.setPosition(rect.position);
    debug.setFillColor(sf::Color(255, 0, 0, 100));
    debug.setSize(rect.size);
}

bool UICollider::onEnter()
{
    return collides && !collidedLastFrame;
}

void UICollider::update()
{
    collidedLastFrame = collides;

    if (mouseCollide(rect, *window))
    {
        collides = true;
    }
    else
    {
        collides = false;
    } 
}

void UICollider::draw(sf::RenderWindow& window)
{
    window.draw(indicator);
    // window.draw(debug);
}

void UICollider::updateVisuals()
{
    indicator.setPosition(rect.position);
    indicator.setSize(rect.size);
}