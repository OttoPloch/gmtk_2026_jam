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

    Level1(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager);

    void createUI() override;

    void update(float dt, float time) override;
private:
    UIButton* launchButton;

    float powerLevel;
    UIDial* powerDial;

    std::vector<UIElement*>* panel1;
    UICollider* panel1Collider;

    float launchAngle;
    UIDial* angleDial;
    
    
    std::vector<UIElement*>* panel2;
    UICollider* panel2Collider;
};