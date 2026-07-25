#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "ui_background.hpp"
#include "ui_button.hpp"
#include "ui_dial.hpp"
#include "ui_slider.hpp"
#include <map>
#include "ui_text.hpp"
#include "ui_collider.hpp"

class UIManager
{
public:
    UIManager();

    UIBackground* addUIBackground(std::string ID, sf::FloatRect rect, BackgroundTemplate backgroundTemplate, char barOrientation = 'n', int barOffset = 5, float scale = 1.f, sf::Texture* texture = nullptr);
    UIButton* addUIButton(std::string ID, sf::RenderWindow* window, sf::FloatRect rect, bool sizeIsScale, std::array<sf::IntRect, 3> texCoords, sf::Texture* texture = nullptr, float timeToRelease = 1.f);
    UIDial* addUIDial(std::string ID, sf::RenderWindow* window, sf::FloatRect rect, bool sizeIsScale, std::vector<sf::IntRect> texCoords, int minValue, int maxValue, float valueScale = 1, sf::Texture* texture = nullptr);
    UISlider* addUISlider(std::string ID, sf::RenderWindow* window, sf::FloatRect rect, bool sizeIsScale, SliderTemplate sliderTemplate, sf::Texture* texture = nullptr);
    UIText* addUIText(std::string ID, sf::FloatRect rect, std::string content, bool autoSetHeight = true, sf::Color color = sf::Color(60, 255, 60), sf::Font* font = nullptr);
    UICollider* addUICollider(std::string ID, sf::RenderWindow* window, sf::FloatRect rect, bool vertical);

    UIBackground* getUIBackground(std::string ID);
    UIButton* getUIButton(std::string ID);
    UIDial* getUIDial(std::string ID);
    UISlider* getUISlider(std::string ID);
    UIText* getUIText(std::string ID);
    UICollider* getUICollider(std::string ID);

    void addToGroup(std::string groupID, UIElement* element);
    std::vector<UIElement*>* getGroup(std::string groupID);

    void resetUI();

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

    std::map<std::string, std::unique_ptr<UIText>> text;
    sf::Font uiTextFont;

    std::map<std::string, std::unique_ptr<UICollider>> colliders;

    std::map<std::string, std::vector<UIElement*>> groups;
};