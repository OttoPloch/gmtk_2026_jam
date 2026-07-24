#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "ui_background.hpp"
#include "ui_button.hpp"
#include "ui_dial.hpp"
#include "ui_slider.hpp"
#include <map>

class UIManager
{
public:
    UIManager();

    UIBackground* addUIBackground(std::string ID, sf::FloatRect rect, int texCoordSize, sf::Vector2i texCoordOffset, sf::Texture* texture = nullptr);
    UIButton* addUIButton(std::string ID, sf::RenderWindow* window, sf::FloatRect rect, bool sizeIsScale, std::array<sf::IntRect, 3> texCoords, sf::Texture* texture = nullptr, float timeToRelease = 1.f);
    UIDial* addUIDial(std::string ID, sf::RenderWindow* window, sf::FloatRect rect, bool sizeIsScale, std::vector<sf::IntRect> texCoords, sf::Texture* texture = nullptr);
    UISlider* addUISlider(std::string ID, sf::RenderWindow* window, sf::FloatRect rect, bool sizeIsScale, SliderTemplate sliderTemplate, sf::Texture* texture = nullptr);

    UIBackground* getUIBackground(std::string ID);
    UIButton* getUIButton(std::string ID);
    UIDial* getUIDial(std::string ID);
    UISlider* getUISlider(std::string ID);

    void clearUI();

    void update(float dt);

    void draw(sf::RenderWindow& window);
private:
    std::map<std::string, std::unique_ptr<UIBackground>> backgrounds;
    sf::Texture uiBackgroundTexture;

    std::map<std::string, std::unique_ptr<UIButton>> buttons;
    sf::Texture uiButtonTexture;

    std::map<std::string, std::unique_ptr<UIDial>> dials;
    sf::Texture uiDialTexture;

    std::map<std::string, std::unique_ptr<UISlider>> sliders;
    sf::Texture uiSliderTexture;
};