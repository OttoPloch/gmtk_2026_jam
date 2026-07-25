#pragma once

#include "level.hpp"

class UIButton;
class UIDial;
class UIElement;
class UICollider;

class Level0 : public Level
{
public:
    Level0();

    Level0(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager, float timeToComplete);

    void createUI() override;

    void specificUpdate(float dt, float time) override;
private:
    std::vector<UIElement*>* panel1;
    UIButton* startButton;
    bool started;
};