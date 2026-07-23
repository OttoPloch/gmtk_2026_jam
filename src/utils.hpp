#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Graphics.hpp>

bool collides(sf::FloatRect rect, sf::Vector2f point);

bool mouseCollide(sf::FloatRect rect, sf::RenderWindow& window);