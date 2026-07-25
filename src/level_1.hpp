#pragma once

#include "level.hpp"

class UIButton;
class UIDial;
class UIElement;
class UICollider;

class Level1 : public Level
{
public:
    Level1();

    Level1(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager, float timeToComplete);

    void createUI() override;

    void specificUpdate(float dt, float time) override;
private:
    UIButton* launchButton;

    std::vector<UIElement*>* panel1;
};