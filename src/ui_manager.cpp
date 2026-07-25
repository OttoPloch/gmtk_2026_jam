#include "ui_manager.hpp"
#include "ui_collider.hpp"
#include "ui_dial.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <iostream>
#include <algorithm>

UIManager::UIManager() {}

UIManager::UIManager(SoundPlayer* soundPlayer) : soundPlayer(soundPlayer)
{
    if (!uiBackgroundTexture.loadFromFile("assets/ui.png"))
    {
        std::cout << "ERROR loading ui background texture.\n";
    }

    if (!uiButtonTexture.loadFromFile("assets/buttons.png"))
    {
        std::cout << "ERROR loading ui button texture.\n";
    }

    if (!uiDialTexture.loadFromFile("assets/dials.png"))
    {
        std::cout << "ERROR loading ui dial texture.\n";
    }

    if (!uiSliderTexture.loadFromFile("assets/sliders.png"))
    {
        std::cout << "ERROR loading ui slider texture.\n";
    }

    std::string fontFile = "assets/raster-forge-font/RasterForgeRegular-JpBgm.ttf";
    // std::string fontFile = "assets/pixelated-elegance-font/PixelatedEleganceRegular-ovawB.ttf";
    // std::string fontFile = "assets/ithaca-font/Ithaca-LVB75.ttf";

    if (!uiTextFont.openFromFile(fontFile))
    {
        std::cout << "ERROR loading ui text font.\n";
    }
}


UIBackground* UIManager::addUIBackground(std::string ID, sf::FloatRect rect, BackgroundTemplate backgroundTemplate, char barOrientation, int barOffset, float scale, sf::Texture* texture)
{
    if (!texture) texture = &uiBackgroundTexture;

    return (backgrounds[ID] = std::make_unique<UIBackground>(soundPlayer, texture, rect, backgroundTemplate, barOrientation, barOffset, scale)).get();
}

UIButton* UIManager::addUIButton(std::string ID, sf::RenderWindow* window, sf::FloatRect rect, bool sizeIsScale, std::array<sf::IntRect, 3> texCoords, sf::Texture* texture, float timeToRelease)
{
    if (!window) return nullptr;

    if (!texture) texture = &uiButtonTexture;

    return (buttons[ID] = std::make_unique<UIButton>(soundPlayer, window, texture, rect, sizeIsScale, texCoords, timeToRelease)).get();
}

UIDial* UIManager::addUIDial(std::string ID, sf::RenderWindow* window, sf::FloatRect rect, bool sizeIsScale, std::vector<sf::IntRect> texCoords, int minValue, int maxValue, float valueScale, sf::Texture* texture)
{
    if (!texture) texture = &uiDialTexture;

    return (dials[ID] = std::make_unique<UIDial>(soundPlayer, window, texture, rect, sizeIsScale, texCoords, minValue, maxValue, valueScale)).get();
}

UISlider* UIManager::addUISlider(std::string ID, sf::RenderWindow* window, sf::FloatRect rect, bool sizeIsScale, SliderTemplate sliderTemplate, sf::Texture* texture)
{
    if (!texture) texture = &uiSliderTexture;

    return (sliders[ID] = std::make_unique<UISlider>(soundPlayer, window, texture, rect, sizeIsScale, sliderTemplate)).get();
}

UIText* UIManager::addUIText(std::string ID, sf::FloatRect rect, std::string content, bool autoSetHeight, sf::Color color, sf::Font* font)
{
    if (!font) font = &uiTextFont;

    return (text[ID] = std::make_unique<UIText>(soundPlayer, rect, font, content, autoSetHeight, color)).get();
}

UICollider* UIManager::addUICollider(std::string ID, sf::RenderWindow* window, sf::FloatRect rect, bool vertical)
{
    return (colliders[ID] = std::make_unique<UICollider>(soundPlayer, window, rect, vertical)).get();
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

UIText* UIManager::getUIText(std::string ID)
{
    if (text.find(ID) != text.end()) return text[ID].get();
    std::cout << "ERROR getting UIText with ID '" << ID << "'\n";
    return nullptr;
}

UICollider* UIManager::getUICollider(std::string ID)
{
    if (colliders.find(ID) != colliders.end()) return colliders[ID].get();
    std::cout << "ERROR getting UICollider with ID '" << ID << "'\n";
    return nullptr;
}

void UIManager::removeUICollider(std::string ID)
{
    auto i = colliders.find(ID);
    if (i != colliders.end())
    {
        colliders.erase(i);
    }
}

void UIManager::addToGroup(std::string groupID, UIElement* element)
{
    if (element)
    {
        if (std::find(groups[groupID].begin(), groups[groupID].end(), element) == groups[groupID].end())
        {
            groups[groupID].emplace_back(element);
        }
        else
        {
            std::cout << "ERROR adding element to group with groupID '" << groupID << "'. Element pointer already in group.\n";
        }
    }
}

std::vector<UIElement*>* UIManager::getGroup(std::string groupID)
{
    if (groups.find(groupID) != groups.end())
    {
        return &groups[groupID];
    }

    std::cout << "ERROR getting group with groupID '" << groupID << "'. Group not found.\n";
    return nullptr;
}

void UIManager::resetUI()
{
    groups.clear();
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
    for (auto& t : text) t.second->update();
    for (auto& c : colliders) c.second->update();

    if (levelIndicator) levelIndicator->update();
}

void UIManager::draw(sf::RenderWindow& window)
{
    for (auto& u : backgrounds) u.second->draw(window);
    for (auto& t : text) t.second->draw(window);
    for (auto& b : buttons) b.second->draw(window);
    for (auto& d : dials) d.second->draw(window);
    for (auto& s : sliders) s.second->draw(window);
    for (auto& c : colliders) c.second->draw(window);

    if (*levelIndicator->valueReadInt != 0) levelIndicator->draw(window);
    if (timeIndicator) timeIndicator->draw(window);
}