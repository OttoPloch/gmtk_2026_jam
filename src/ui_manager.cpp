#include "ui_manager.hpp"
#include "ui_dial.hpp"
#include <SFML/Graphics/Rect.hpp>
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

    if (!uiDialTexture.loadFromFile("../../assets/dials.png"))
    {
        std::cout << "ERROR loading ui dial texture.\n";
    }

    if (!uiSliderTexture.loadFromFile("../../assets/sliders.png"))
    {
        std::cout << "ERROR loading ui slider texture.\n";
    }
}

UIBackground* UIManager::addUIBackground(std::string ID, sf::FloatRect rect, int texCoordSize, sf::Vector2i texCoordOffset, sf::Texture* texture)
{
    if (!texture) texture = &uiBackgroundTexture;

    return (backgrounds[ID] = std::make_unique<UIBackground>(texture, rect, texCoordSize, texCoordOffset)).get();
}

UIButton* UIManager::addUIButton(std::string ID, sf::RenderWindow* window, sf::FloatRect rect, bool sizeIsScale, std::array<sf::IntRect, 3> texCoords, sf::Texture* texture, float timeToRelease)
{
    if (!window) return nullptr;

    if (!texture) texture = &uiButtonTexture;

    return (buttons[ID] = std::make_unique<UIButton>(window, texture, rect, sizeIsScale, texCoords, timeToRelease)).get();
}

UIDial* UIManager::addUIDial(std::string ID, sf::RenderWindow* window, sf::FloatRect rect, bool sizeIsScale, std::vector<sf::IntRect> texCoords, sf::Texture* texture)
{
    if (!texture) texture = &uiDialTexture;

    return (dials[ID] = std::make_unique<UIDial>(window, texture, rect, sizeIsScale, texCoords)).get();
}

UISlider* UIManager::addUISlider(std::string ID, sf::RenderWindow* window, sf::FloatRect rect, bool sizeIsScale, SliderTemplate sliderTemplate, sf::Texture* texture)
{
    if (!texture) texture = &uiSliderTexture;

    return (sliders[ID] = std::make_unique<UISlider>(window, texture, rect, sizeIsScale, sliderTemplate)).get();
}

UIBackground* UIManager::getUIBackground(std::string ID)
{
    if (backgrounds.find(ID) != backgrounds.end()) return backgrounds[ID].get();
    std::cout << "ERROR getting UIBackground with ID '" << ID << "'\n";
    return nullptr;
}

UIButton* UIManager::getUIButton(std::string ID)
{
    if (buttons.find(ID) != buttons.end()) return buttons[ID].get();
    std::cout << "ERROR getting UIButton with ID '" << ID << "'\n";
    return nullptr;
}

UIDial* UIManager::getUIDial(std::string ID)
{
    if (dials.find(ID) != dials.end()) return dials[ID].get();
    std::cout << "ERROR getting UIDial with ID '" << ID << "'\n";
    return nullptr;
}

UISlider* UIManager::getUISlider(std::string ID)
{
    if (sliders.find(ID) != sliders.end()) return sliders[ID].get();
    std::cout << "ERROR getting UISlider with ID '" << ID << "'\n";
    return nullptr;
}


void UIManager::clearUI()
{
    backgrounds.clear();
    buttons.clear();
    dials.clear();
    sliders.clear();
}

void UIManager::update(float dt)
{
    for (auto& b : buttons) b.second->update(dt);
    for (auto& d : dials) d.second->update();
    for (auto& s : sliders) s.second->update();
}

void UIManager::draw(sf::RenderWindow& window)
{
    for (auto& u : backgrounds) u.second->draw(window);
    for (auto& b : buttons) b.second->draw(window);
    for (auto& d : dials) d.second->draw(window);
    for (auto& s : sliders) s.second->draw(window);
}