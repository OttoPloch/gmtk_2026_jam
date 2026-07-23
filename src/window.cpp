#include "window.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/VideoMode.hpp>

Window::Window() : windowState(sf::State::Windowed), windowedResolution(1440, 810), backgroundSize(1000, 1000) {}

Window::Window(sf::Vector2f backgroundSize) : windowState(sf::State::Windowed), windowedResolution(1440, 810), backgroundSize(backgroundSize) {}

void Window::create(sf::VideoMode videoMode, std::uint32_t style)
{
    window.create(videoMode, "COUNT DOWN", style, windowState);
    window.setFramerateLimit(60);

    window.setView(sf::View(sf::FloatRect({0, 0}, backgroundSize)));
}

void Window::create(sf::VideoMode videoMode, sf::State state, std::uint32_t style)
{
    windowState = state;

    create(videoMode, style);
}

void Window::toggleFullscreen()
{
    if (windowState == sf::State::Fullscreen)
    {
        windowState = sf::State::Windowed;

        create(sf::VideoMode(windowedResolution), sf::Style::Close);
    }
    else
    {
        windowState = sf::State::Fullscreen;

        create(sf::VideoMode::getDesktopMode(), sf::Style::Close);
    }
}