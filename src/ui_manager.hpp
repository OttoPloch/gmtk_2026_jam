#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "ui_background.hpp"
#include "ui_button.hpp"

class UIManager
{
public:
    UIManager();

    void addUIBackground(sf::FloatRect rect, sf::Texture* texture = nullptr);

    void addUIButton(sf::RenderWindow* window, sf::FloatRect rect, sf::Texture* texture = nullptr, std::array<sf::IntRect, 3> texCoords = {sf::IntRect({0, 0}, {36, 36}), sf::IntRect({36, 0}, {36, 36}), sf::IntRect({72, 0}, {36, 36})}, float timeToRelease = 1.f);

    void clearUI();

    void update(float dt);

    void draw(sf::RenderWindow& window);
private:
    std::vector<UIBackground> backgrounds;
    sf::Texture uiBackgroundTexture;

    std::vector<UIButton> buttons;
    sf::Texture uiButtonTexture;
};