#include "ui_manager.hpp"
#include <iostream>

UIManager::UIManager()
{
    if (!uiBackgroundTexture.loadFromFile("../../assets/ui.png"))
    {
        std::cout << "ERROR loading ui background texture.\n";
    }

    if (!uiButtonTexture.loadFromFile("../../assets/buttons.png"))
    {
        std::cout << "ERROR loading ui button texture.\n";
    }
}

void UIManager::addUIBackground(sf::FloatRect rect, sf::Texture* texture)
{
    if (!texture) texture = &uiBackgroundTexture;

    backgrounds.emplace_back(texture, rect);
}

void UIManager::addUIButton(sf::RenderWindow* window, sf::FloatRect rect, sf::Texture* texture, std::array<sf::IntRect, 3> texCoords, float timeToRelease)
{
    if (!window) return;

    if (!texture) texture = &uiButtonTexture;

    buttons.emplace_back(window, texture, rect, texCoords, timeToRelease);
}

void UIManager::clearUI()
{
    backgrounds.clear();
    buttons.clear();
}

void UIManager::update(float dt)
{
    for (auto& b : buttons) b.update(dt);
}

void UIManager::draw(sf::RenderWindow& window)
{
    for (auto& u : backgrounds) u.draw(window);

    for (auto& b : buttons) b.draw(window);
}