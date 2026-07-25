#pragma once

#include "level.hpp"

class UIButton;
class UIDial;
class UIElement;
class UICollider;
class UISlider;

class Level3 : public Level
{
public:
    Level3();

    Level3(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager, float timeToComplete);

    void createUI() override;

    void specificUpdate(float dt, float time) override;
private:
    UIButton* launchButton;

    float powerLevel;
    UIDial* powerDial;

    std::vector<UIElement*>* panel1;
    UICollider* panel1Collider;

    float launchAngle;
    UIDial* angleDial;
    
    float engine1Calibration;
    UISlider* engine1Slider;
    
    float engine2Calibration;
    UISlider* engine2Slider;

    std::vector<UIElement*>* panel2;
    UICollider* panel2Collider;
};