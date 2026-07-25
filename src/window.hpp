#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

class Window
{
public:
    Window();

    Window(sf::Vector2f backgroundSize);

    void create(sf::VideoMode videoMode, std::uint32_t style = sf::Style::Close, unsigned int maxFramerate = 60);

    void create(sf::VideoMode videoMode, sf::State state, std::uint32_t style = sf::Style::Close);

    void toggleFullscreen();

    void setViewRect(sf::FloatRect viewRect);

    sf::RenderWindow window;

    sf::Vector2u windowedResolution;
private:
    sf::State windowState;

    sf::Vector2f backgroundSize;
};