#pragma once

#include "level.hpp"

class UIButton;
class UIDial;
class UIElement;
class UICollider;
class UISlider;
class UIText;

class Level6 : public Level
{
public:
    Level6();

    Level6(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager, float timeToComplete);

    void createUI() override;

    void specificUpdate(float dt, float time) override;
private:
    UIButton* launchButton;

    float powerLevel;
    UIDial* powerDial;

    std::vector<UIElement*>* panel1;
    UICollider* panel1Collider;
    
    float engine1Calibration;
    UISlider* engine1Slider;
    
    float engine2Calibration;
    UISlider* engine2Slider;

    std::vector<UIElement*>* panel2;
    UICollider* panel2Collider;
    
    bool oxidizer;
    UIButton* oxidizerButton;
    UIText* oxidizerText;
    bool fuel;
    UIButton* fuelButton;
    UIText* fuelText;
    bool bomb;
    UIButton* bombButton;
    UIText* bombText;
    bool pumps;
    UIButton* pumpsButton;
    UIText* pumpsText;
    
    std::vector<UIElement*>* panel3;
    UICollider* panel3Collider;

    float launchAngle;
    UIDial* angleDial;

    std::vector<UIElement*>* panel4;
    UICollider* panel4Collider;

    std::vector<UIElement*>* notes;
    UICollider* notesCollider;

    float goal_powerLevel;
    float goal_engine1Calibration;
    float goal_engine2Calibration;
    float goal_oxidizer;
    float goal_pumps;
    float goal_launchAngle;
    float tolerance;
    float tolerance2;
};