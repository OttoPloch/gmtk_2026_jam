#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Graphics.hpp>

bool collides(sf::FloatRect rect, sf::Vector2f point);

bool circleCollide(sf::Vector2f center, float radius, sf::Vector2f point);

bool mouseCollide(sf::FloatRect rect, sf::RenderWindow& window);

bool circleMouseCollide(sf::Vector2f center, float radius, sf::RenderWindow& window);

float getAngle(sf::Vector2f origin, sf::Vector2f point, bool degrees = true);