#include "utils.hpp"
#include "SFML/Window/Mouse.hpp"

bool collides(sf::FloatRect rect, sf::Vector2f point)
{
    return (point.x >= rect.position.x && point.x <= rect.position.x + rect.size.x && point.y >= rect.position.y && point.y <= rect.position.y + rect.size.y);
}

bool circleCollide(sf::Vector2f center, float radius, sf::Vector2f point)
{
    return sqrt(pow(center.x - point.x, 2) + pow(center.y - point.y, 2)) < radius;
}

bool mouseCollide(sf::FloatRect rect, sf::RenderWindow& window)
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    return collides(rect, mousePos);
}

bool circleMouseCollide(sf::Vector2f center, float radius, sf::RenderWindow& window)
{
    return circleCollide(center, radius, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}

float getAngle(sf::Vector2f origin, sf::Vector2f point, bool degrees)
{
    float angle = std::atan2(point.y - origin.y, point.x - origin.x);

    if (degrees) angle *= 180.f / 3.1415926535;
    
    return angle;
}