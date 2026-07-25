#include "window.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/VideoMode.hpp>

Window::Window() : windowState(sf::State::Windowed), windowedResolution(1440, 810), backgroundSize(100, 100) {}

Window::Window(sf::Vector2f backgroundSize) : windowState(sf::State::Windowed), windowedResolution(1440, 810), backgroundSize(backgroundSize) {}

void Window::create(sf::VideoMode videoMode, std::uint32_t style, unsigned int maxFramerate)
{
    window.create(videoMode, "COUNT DOWN", style, windowState);
    if (maxFramerate != 0) window.setFramerateLimit(maxFramerate);

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

void Window::setViewRect(sf::FloatRect viewRect)
{
    window.setView(sf::View(viewRect.position, viewRect.size));
}