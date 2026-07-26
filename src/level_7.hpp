#pragma once

#include "level.hpp"

class UIButton;
class UIDial;
class UIElement;
class UICollider;

class Level7 : public Level
{
public:
    Level7();

    Level7(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager, float timeToComplete);

    void createUI() override;

    void specificUpdate(float dt, float time) override;

    void draw();
private:
    std::unique_ptr<sf::Sprite> endScreen;
    sf::Texture endScreenTexture;
};