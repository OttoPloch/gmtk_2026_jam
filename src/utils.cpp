#include "utils.hpp"
#include "SFML/Window/Mouse.hpp"

bool collides(sf::FloatRect rect, sf::Vector2f point)
{
    return (point.x >= rect.position.x && point.x <= rect.position.x + rect.size.x && point.y >= rect.position.y && point.y <= rect.position.y + rect.size.y);
}

bool mouseCollide(sf::FloatRect rect, sf::RenderWindow& window)
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    return collides(rect, mousePos);
}