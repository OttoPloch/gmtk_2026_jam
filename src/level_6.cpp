#include "level_6.hpp"
#include "defaults.hpp"
#include "launch_pad.hpp"
#include "ui_manager.hpp"
#include "ui_button.hpp"
#include "ui_dial.hpp"
#include "ui_collider.hpp"
#include "random.hpp"
#include <chrono>
#include <iostream>

Level6::Level6() {}

Level6::Level6(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager, float timeToComplete) : Level(window, launchPad, uiManager, timeToComplete) {}

void Level6::createUI()
{
    powerLevel = 0;

    engine1Calibration = launchPad->random->getRandInt(-100, 100);
    engine2Calibration = launchPad->random->getRandInt(-100, 100);

    oxidizer = launchPad->random->getRandInt(0, 1);
    fuel = launchPad->random->getRandInt(0, 1);
    bomb = launchPad->random->getRandInt(0, 1);
    pumps = launchPad->random->getRandInt(0, 1);

    launchAngle = launchPad->random->getRandInt(-45, 45);

    Random randomActually(std::chrono::system_clock::now().time_since_epoch().count());

    goal_powerLevel = randomActually.getRandInt(60, 90);
    goal_engine1Calibration = randomActually.getRandInt(-100, 90);
    goal_engine2Calibration = randomActually.getRandInt(-100, 90);
    goal_oxidizer = randomActually.getRandInt(0, 1);
    goal_pumps = randomActually.getRandInt(0, 1);
    goal_launchAngle = randomActually.getRandInt(-45, 40);

    tolerance = 10;
    tolerance2 = 5;

    std::cout << goal_powerLevel << ", " << goal_engine1Calibration << ", " << goal_engine2Calibration << ", " << goal_oxidizer << ", " << goal_pumps << ", " << goal_launchAngle << '\n';

    uiManager->resetUI();



    sf::Vector2f panel1Pos(10, 20);
    uiManager->defaultGroup = "panel1";

    launchButton = uiManager->addUIButton("launch button", window, {{panel1Pos.x + 42, panel1Pos.y + 28}, {1, 1}}, true, defaultTexCoords.buttonTexCoords);
    UIText* text = uiManager->addUIText("text", {{panel1Pos.x + 10, panel1Pos.y + 10}, {100, 1}}, "LAUNCH BUTTON", 'h', sf::Color::White);
    
    uiManager->addToGroup("panel1",
    uiManager->addUIBackground("bg", {panel1Pos, {122, 60}}, defaultTexCoords.bgSmall, 'l'));

    uiManager->addToGroup("panel1",
    uiManager->addUIBackground("text bg", {text->getRect().position - sf::Vector2f(3, 3), text->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel1", text);    

    uiManager->addToGroup("panel1", launchButton);

    uiManager->defaultGroup = "LEVEL";
    panel1Collider = uiManager->addUICollider("panel1Collider", window, {{0, panel1Pos.y - 15}, {10, 90}}, true);
    
    panel1 = uiManager->getGroup("panel1");

    sf::Vector2f panel2Pos(160, 10);
    uiManager->defaultGroup = "panel2";
    
    powerDial = uiManager->addUIDial("power dial", window, {{panel2Pos.x + 10, panel2Pos.y + 21}, {50, 50}}, false, defaultTexCoords.dialTexCoords, -0, 100, 100./360/3);
    UIText* text3 = uiManager->addUIText("power text", {{panel2Pos.x + 27.5f, panel2Pos.y + 79}, {15, 100}}, "100%");
    UIText* text4 = uiManager->addUIText("power label", {{panel2Pos.x + 9, panel2Pos.y + 11}, {50, 100}}, "LAUNCH POWER", 'h', sf::Color::White);
    engine1Slider = uiManager->addUISlider("1slider", window, {{panel2Pos.x + 70, panel2Pos.y + 12}, {2, 1}}, true, defaultTexCoords.horizontalSlider);
    UIText* engine1Text = uiManager->addUIText("engine1 text", {{panel2Pos.x + 76, panel2Pos.y + 42}, {0, 3}}, "-100", 'l');
    UIText* engine1Label = uiManager->addUIText("engine1label text", {{panel2Pos.x + 76, panel2Pos.y + 32}, {0, 3}}, "ENG 1 CALIBRATION", 'l', sf::Color::White);
    engine2Slider = uiManager->addUISlider("2slider", window, {{panel2Pos.x + 70, panel2Pos.y + 52}, {2, 1}}, true, defaultTexCoords.horizontalSlider);
    UIText* engine2Text = uiManager->addUIText("engine2 text", {{panel2Pos.x + 76, panel2Pos.y + 82}, {0, 3}}, "-100", 'l');
    UIText* engine2Label = uiManager->addUIText("engine2label text", {{panel2Pos.x + 76, panel2Pos.y + 72}, {0, 3}}, "ENG 2 CALIBRATION", 'l', sf::Color::White);
    
    uiManager->addToGroup("panel2",
    uiManager->addUIBackground("bg2", {panel2Pos, {145, 100}}, defaultTexCoords.bgSmall, 't'));
    
    uiManager->addToGroup("panel2",
    uiManager->addUIBackground("text3 bg", {text3->getRect().position - sf::Vector2f(3, 3), text3->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel2", text3);
    uiManager->addToGroup("panel2",
    uiManager->addUIBackground("text4 bg", {text4->getRect().position - sf::Vector2f(3, 3), text4->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel2", text4);
    uiManager->addToGroup("panel2", powerDial);
    
    uiManager->addToGroup("panel2",
    uiManager->addUIBackground("engine1Text bg", {engine1Text->getRect().position - sf::Vector2f(3, 3), engine1Text->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel2", engine1Text);
    uiManager->addToGroup("panel2",
    uiManager->addUIBackground("engine1label bg", {engine1Label->getRect().position - sf::Vector2f(3, 3), engine1Label->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel2", engine1Label);
    uiManager->addToGroup("panel2", engine1Slider);
    
    uiManager->addToGroup("panel2",
    uiManager->addUIBackground("engine2Text bg", {engine2Text->getRect().position - sf::Vector2f(3, 3), engine2Text->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel2", engine2Text);
    uiManager->addToGroup("panel2",
    uiManager->addUIBackground("engine2label bg", {engine2Label->getRect().position - sf::Vector2f(3, 3), engine2Label->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel2", engine2Label);
    uiManager->addToGroup("panel2", engine2Slider);

    uiManager->defaultGroup = "LEVEL";
    panel2Collider = uiManager->addUICollider("panel2Collider", window, {{panel2Pos.x - 15, 0}, {175, 10}}, false);

    text3->valueRead = &powerLevel;
    text3->valueInPercent = true;

    engine1Text->valueRead = &engine1Calibration;
    engine1Text->valueDecimals = 0;
    engine2Text->valueRead = &engine2Calibration;
    engine2Text->valueDecimals = 0;
          
    engine1Slider->value = (engine1Calibration / 200.f) + .5f;
    engine2Slider->value = (engine2Calibration / 200.f) + .5f;

    panel2 = uiManager->getGroup("panel2");
    


    sf::Vector2f panel3Pos(launchPad->getBackgroundSize().x - 140, 40);
    uiManager->defaultGroup = "panel3";

    oxidizerButton = uiManager->addUIButton("oxidizer button", window, {{panel3Pos.x + 10, panel3Pos.y + 10}, {1, 1}}, true, defaultTexCoords.buttonSmallTexCoords);
    oxidizerText = uiManager->addUIText("oxidizer text", {{panel3Pos.x + 35, panel3Pos.y + 13}, {0, 4}}, "OFF", 'l');
    UIText* oxidizerLabel = uiManager->addUIText("oxidizer label", {{panel3Pos.x + 58, panel3Pos.y + 13}, {0, 4}}, "OXIDIZER", 'l', sf::Color::White);
    fuelButton = uiManager->addUIButton("fuel button", window, {{panel3Pos.x + 10, panel3Pos.y + 30}, {1, 1}}, true, defaultTexCoords.buttonSmallTexCoords);
    fuelText = uiManager->addUIText("fuel text", {{panel3Pos.x + 35, panel3Pos.y + 33}, {0, 4}}, "OFF", 'l');
    UIText* fuelLabel = uiManager->addUIText("fuel label", {{panel3Pos.x + 58, panel3Pos.y + 33}, {0, 4}}, "FUEL", 'l', sf::Color::White);
    bombButton = uiManager->addUIButton("bomb button", window, {{panel3Pos.x + 10, panel3Pos.y + 50}, {1, 1}}, true, defaultTexCoords.buttonSmallTexCoords);
    bombText = uiManager->addUIText("bomb text", {{panel3Pos.x + 35, panel3Pos.y + 53}, {0, 4}}, "OFF", 'l');
    UIText* bombLabel = uiManager->addUIText("bomb label", {{panel3Pos.x + 58, panel3Pos.y + 53}, {0, 4}}, "BOMB", 'l', sf::Color::White);
    pumpsButton = uiManager->addUIButton("pumps button", window, {{panel3Pos.x + 10, panel3Pos.y + 70}, {1, 1}}, true, defaultTexCoords.buttonSmallTexCoords);
    pumpsText = uiManager->addUIText("pumps text", {{panel3Pos.x + 35, panel3Pos.y + 73}, {0, 4}}, "OFF", 'l');
    UIText* pumpsLabel = uiManager->addUIText("pump label", {{panel3Pos.x + 58, panel3Pos.y + 73}, {0, 4}}, "PUMPS", 'l', sf::Color::White);
    
    uiManager->addToGroup("panel3",
    uiManager->addUIBackground("bg3", {panel3Pos, {120, 92}}, defaultTexCoords.bgSmall, 'r'));
    
    uiManager->addToGroup("panel3",
    uiManager->addUIBackground("oxidizer text bg", {oxidizerText->getRect().position - sf::Vector2f(3, 3), oxidizerText->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel3", oxidizerText);
    uiManager->addToGroup("panel3",
    uiManager->addUIBackground("oxidizer label bg", {oxidizerLabel->getRect().position - sf::Vector2f(3, 3), oxidizerLabel->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel3",
    oxidizerLabel);
    uiManager->addToGroup("panel3", oxidizerButton);
    
    uiManager->addToGroup("panel3",
    uiManager->addUIBackground("fuel text bg", {fuelText->getRect().position - sf::Vector2f(3, 3), fuelText->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel3", fuelText);
    uiManager->addToGroup("panel3",
    uiManager->addUIBackground("fuel label bg", {fuelLabel->getRect().position - sf::Vector2f(3, 3), fuelLabel->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel3",
    fuelLabel);
    uiManager->addToGroup("panel3", fuelButton);
    
    uiManager->addToGroup("panel3",
    uiManager->addUIBackground("bomb text bg", {bombText->getRect().position - sf::Vector2f(3, 3), bombText->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel3", bombText);
    uiManager->addToGroup("panel3",
    uiManager->addUIBackground("bomb label bg", {bombLabel->getRect().position - sf::Vector2f(3, 3), bombLabel->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel3",
    bombLabel);
    uiManager->addToGroup("panel3", bombButton);
    
    uiManager->addToGroup("panel3",
    uiManager->addUIBackground("pumps text bg", {pumpsText->getRect().position - sf::Vector2f(3, 3), pumpsText->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel3", pumpsText);
    uiManager->addToGroup("panel3",
    uiManager->addUIBackground("pumps label bg", {pumpsLabel->getRect().position - sf::Vector2f(3, 3), pumpsLabel->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel3",
    pumpsLabel);
    uiManager->addToGroup("panel3", pumpsButton);

    uiManager->defaultGroup = "LEVEL";
    panel3Collider = uiManager->addUICollider("panel3Collider", window, {{static_cast<float>(launchPad->getBackgroundSize().x) - 5, panel3Pos.y - 15}, {10, 130}}, true);

    panel3 = uiManager->getGroup("panel3");

    

    sf::Vector2f panel4Pos(350, 10);
    uiManager->defaultGroup = "panel4";

    angleDial = uiManager->addUIDial("angle dial", window, {{panel4Pos.x + 10, panel4Pos.y + 10}, {1, 1}}, true, defaultTexCoords.dialSmallTexCoords, -180, 0);
    UIText* angleText = uiManager->addUIText("angle text", {{panel4Pos.x + 11, panel4Pos.y + 34}, {0, 4}}, "-45°", 'l');
    UIText* angleLabel = uiManager->addUIText("angle label", {{panel4Pos.x + 34, panel4Pos.y + 15}, {0, 9}}, "LAUNCH\nANGLE", 'l', sf::Color::White);


    uiManager->addToGroup("panel4",
    uiManager->addUIBackground("panel3 bg", {panel4Pos, {73, 54}}, defaultTexCoords.bgSmall, 't'));

    uiManager->addToGroup("panel4", angleDial);
    uiManager->addToGroup("panel4",
    uiManager->addUIBackground("angle label bg", {angleLabel->getRect().position - sf::Vector2f(3, 3), angleLabel->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel4",
    angleLabel);
    uiManager->addToGroup("panel4",
    uiManager->addUIBackground("angle text bg", {angleText->getRect().position - sf::Vector2f(3, 3), angleText->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel4", angleText);

    uiManager->defaultGroup = "LEVEL";
    panel4Collider = uiManager->addUICollider("panel4Collider", window, {{panel4Pos.x - 15, 0}, {103, 10}}, false);

    angleText->valueRead = &launchAngle;
    angleText->valueDecimals = 0;
    angleText->valueInDegrees = true;
    
    angleDial->setValue((launchAngle - 45) * 2);

    panel4 = uiManager->getGroup("panel4");

    beginAnimation("hide all", 0);
}

void Level6::specificUpdate(float dt, float time)
{
    std::vector<std::pair<std::string, float>*> animsToUpdate;

    for (auto& l : animations)
    {
        if (l.second.size() > 0)
        {
            if (l.first == 0)
            {
                animsToUpdate.emplace_back(&l.second[0]);
                break;
            }
            else
            {
                animsToUpdate.emplace_back(&l.second[0]);
                continue;
            }
        }
    }

    if (animsToUpdate.size() > 0)
    {
        for (auto& currAnim : animsToUpdate)
        {
            if (currAnim->first == "hide all")
            {
                if (currAnim->second < 1)
                {
                    float offset = (.06f * std::sin(5 * currAnim->second)) * 500 * dt;
    
                    for (auto e : *panel1)
                    {
                        e->changeOffset({offset, 0});
                    }
    
                    for (auto e : *panel2)
                    {
                        e->changeOffset({0, offset});
                    }

                    for (auto e : *panel3)
                    {
                        e->changeOffset({-offset, 0});
                    }

                    for (auto e : *panel4)
                    {
                        e->changeOffset({0, offset});
                    }
                }
                else if (currAnim->second <= 2)
                {
                    float offset = -.15f * (static_cast<float>(pow(currAnim->second, 3))) * 500 * dt;
    
                    for (auto e : *panel1)
                    {
                        e->changeOffset({offset, 0});
                    }
    
                    for (auto e : *panel2)
                    {
                        e->changeOffset({0, offset});
                    }

                    for (auto e : *panel3)
                    {
                        e->changeOffset({-offset, 0});
                    }

                    for (auto e : *panel4)
                    {
                        e->changeOffset({0, offset});
                    }
                }
                else
                {
                    animations[0].erase(animations[0].begin());
                }
    
                currAnim->second += dt;
            }
            else if (currAnim->first == "show1")
            {
                if (currAnim->second <= .001f)
                {
                    float offset = -150;
    
                    for (auto e : *panel1)
                    {
                        e->setOffset({offset, 0});
                    }
                }
    
                if (currAnim->second <= .5f)
                {
                    float offset = 300 * dt;
    
                    for (auto e : *panel1)
                    {
                        e->changeOffset({offset, 0});
                    }
                }
                else
                {
                    for (auto e : *panel1)
                    {
                        e->setOffset({0, 0});
                    }
    
                    animations[1].erase(animations[1].begin());
                }
    
                currAnim->second += dt;
            }
            else if (currAnim->first == "show2")
            {
                if (currAnim->second <= .001f)
                {
                    float offset = -150;
    
                    for (auto e : *panel2)
                    {
                        e->setOffset({0, offset});
                    }
                }
    
                if (currAnim->second <= .5f)
                {
                    float offset = 300 * dt;
    
                    for (auto e : *panel2)
                    {
                        e->changeOffset({0, offset});
                    }
                }
                else
                {
                    for (auto e : *panel2)
                    {
                        e->setOffset({0, 0});
                    }
    
                    animations[2].erase(animations[2].begin());
                }
    
                currAnim->second += dt;
            }
            else if (currAnim->first == "show3")
            {
                if (currAnim->second <= .001f)
                {
                    float offset = 150;
    
                    for (auto e : *panel3)
                    {
                        e->setOffset({offset, 0});
                    }
                }
    
                if (currAnim->second <= .5f)
                {
                    float offset = -300 * dt;
    
                    for (auto e : *panel3)
                    {
                        e->changeOffset({offset, 0});
                    }
                }
                else
                {
                    for (auto e : *panel3)
                    {
                        e->setOffset({0, 0});
                    }
    
                    animations[3].erase(animations[3].begin());
                }
    
                currAnim->second += dt;
            }
            else if (currAnim->first == "show4")
            {
                if (currAnim->second <= .001f)
                {
                    float offset = -150;
    
                    for (auto e : *panel4)
                    {
                        e->setOffset({0, offset});
                    }
                }
    
                if (currAnim->second <= .5f)
                {
                    float offset = 300 * dt;
    
                    for (auto e : *panel4)
                    {
                        e->changeOffset({0, offset});
                    }
                }
                else
                {
                    for (auto e : *panel4)
                    {
                        e->setOffset({0, 0});
                    }
    
                    animations[4].erase(animations[4].begin());
                }
    
                currAnim->second += dt;
            }
            else if (currAnim->first == "hide1")
            {
                if (currAnim->second <= .001f)
                {
                    float offset = 0;
    
                    for (auto e : *panel1)
                    {
                        e->setOffset({offset, 0});
                    }
                }
    
                if (currAnim->second <= .5f)
                {
                    float offset = -300 * dt;
    
                    for (auto e : *panel1)
                    {
                        e->changeOffset({offset, 0});
                    }
                }
                else
                {
                    for (auto e : *panel1)
                    {
                        e->setOffset({-150, 0});
                    }
    
                    animations[1].erase(animations[1].begin());
                }
    
                currAnim->second += dt;
            }
            else if (currAnim->first == "hide2")
            {
                if (currAnim->second <= .001f)
                {
                    float offset = 0;
    
                    for (auto e : *panel2)
                    {
                        e->setOffset({0, offset});
                    }
                }
    
                if (currAnim->second <= .5f)
                {
                    float offset = -300 * dt;
    
                    for (auto e : *panel2)
                    {
                        e->changeOffset({0, offset});
                    }
                }
                else
                {
                    for (auto e : *panel2)
                    {
                        e->setOffset({0, -150});
                    }
    
                    animations[2].erase(animations[2].begin());
                }
    
                currAnim->second += dt;
            }
            else if (currAnim->first == "hide3")
            {
                if (currAnim->second <= .001f)
                {
                    float offset = 0;
    
                    for (auto e : *panel3)
                    {
                        e->setOffset({offset, 0});
                    }
                }
    
                if (currAnim->second <= .5f)
                {
                    float offset = 300 * dt;
    
                    for (auto e : *panel3)
                    {
                        e->changeOffset({offset, 0});
                    }
                }
                else
                {
                    for (auto e : *panel3)
                    {
                        e->setOffset({150, 0});
                    }
    
                    animations[3].erase(animations[3].begin());
                }
    
                currAnim->second += dt;
            }
            else if (currAnim->first == "hide4")
            {
                if (currAnim->second <= .001f)
                {
                    float offset = 0;
    
                    for (auto e : *panel4)
                    {
                        e->setOffset({0, offset});
                    }
                }
    
                if (currAnim->second <= .5f)
                {
                    float offset = -300 * dt;
    
                    for (auto e : *panel4)
                    {
                        e->changeOffset({0, offset});
                    }
                }
                else
                {
                    for (auto e : *panel4)
                    {
                        e->setOffset({0, -150});
                    }
    
                    animations[4].erase(animations[4].begin());
                }
    
                currAnim->second += dt;
            }
        }
    }

    if (animations[0].size() == 0)
    {
        if (panel1Collider && panel1Collider->onEnter())
        {
            if (animations[1].size() == 0)
            {
                if ((*panel1)[0]->getOffset() != sf::Vector2f(0, 0))
                {
                    beginAnimation("show1", 1);
                }
                else
                {
                    beginAnimation("hide1", 1);
                }
            }
        }

        if (panel2Collider && panel2Collider->onEnter())
        {
            if (animations[2].size() == 0)
            {
                if ((*panel2)[0]->getOffset() != sf::Vector2f(0, 0))
                {
                    beginAnimation("show2", 2);
                }
                else
                {
                    beginAnimation("hide2", 2);
                }
            }
        }

        if (panel3Collider && panel3Collider->onEnter())
        {
            if (animations[3].size() == 0)
            {
                if ((*panel3)[0]->getOffset() != sf::Vector2f(0, 0))
                {
                    beginAnimation("show3", 3);
                }
                else
                {
                    beginAnimation("hide3", 3);
                }
            }
        }

        if (panel4Collider && panel4Collider->onEnter())
        {
            if (animations[4].size() == 0)
            {
                if ((*panel4)[0]->getOffset() != sf::Vector2f(0, 0))
                {
                    beginAnimation("show4", 4);
                }
                else
                {
                    beginAnimation("hide4", 4);
                }
            }
        }
    }

    if (powerDial) powerLevel = powerDial->getValue();
    if (engine1Slider) engine1Calibration = (engine1Slider->value - .5f) * 200.f;
    if (engine2Slider) engine2Calibration = (engine2Slider->value - .5f) * 200.f;
    if (angleDial) launchAngle = (angleDial->getValue() / 2. + 45);

    if (oxidizerButton)
    {
        if (oxidizerButton->isDown()) oxidizer = !oxidizer;

        if (oxidizerText)
        {
            if (oxidizer) oxidizerText->setString("ON");
            else oxidizerText->setString("OFF");
        }
    }
    if (fuelButton)
    {
        if (fuelButton->isDown()) fuel = !fuel;

        if (fuelText)
        {
            if (fuel) fuelText->setString("ON");
            else fuelText->setString("OFF");
        }
    }
    if (bombButton)
    {
        if (bombButton->isDown()) bomb = !bomb;

        if (bombText)
        {
            if (bomb) bombText->setString("ON");
            else bombText->setString("OFF");
        }
    }
    if (pumpsButton)
    {
        if (pumpsButton->isDown()) pumps = !pumps;

        if (pumpsText)
        {
            if (pumps) pumpsText->setString("ON");
            else pumpsText->setString("OFF");
        }
    }

    if (launchButton && launchButton->isDown())
    {
        if (powerLevel >= goal_powerLevel && powerLevel <= goal_powerLevel + tolerance &&
            engine1Calibration >= goal_engine1Calibration && engine1Calibration <= goal_engine1Calibration + tolerance &&
            engine2Calibration >= goal_engine2Calibration && engine2Calibration <= goal_engine2Calibration + tolerance &&
            oxidizer == goal_oxidizer && fuel && !bomb && pumps == goal_pumps &&
            launchAngle >= goal_launchAngle && launchAngle <= goal_launchAngle + tolerance2
        )
        {
            launchPad->launch();
        }
        else
        {
            launchPad->fail();
        }

        beginAnimation("hide all", 0);

        panel1Collider = nullptr;
        panel2Collider = nullptr;
        panel3Collider = nullptr;
        panel4Collider = nullptr;
        uiManager->removeUICollider("panel1Collider");
        uiManager->removeUICollider("panel2Collider");
        uiManager->removeUICollider("panel3Collider");
    uiManager->removeUICollider("panel4Collider");
    }
}
