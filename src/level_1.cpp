#include "level_1.hpp"
#include "defaults.hpp"
#include "launch_pad.hpp"
#include "ui_manager.hpp"
#include "ui_button.hpp"

Level1::Level1() {}

Level1::Level1(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager, float timeToComplete) : Level(window, launchPad, uiManager, timeToComplete)
{}

void Level1::createUI()
{
    uiManager->resetUI();



    sf::Vector2f panel1Pos(10, 20);

    launchButton = uiManager->addUIButton("launch button", window, {{panel1Pos.x + 42, panel1Pos.y + 28}, {1, 1}}, true, defaultTexCoords.buttonTexCoords);
    UIText* text = uiManager->addUIText("text", {{panel1Pos.x + 10, panel1Pos.y + 10}, {100, 1}}, "LAUNCH BUTTON", 'h', sf::Color::White);
    
    uiManager->addToGroup("panel1",
    uiManager->addUIBackground("bg", {panel1Pos, {122, 60}}, defaultTexCoords.bgSmall, 'l'));

    uiManager->addToGroup("panel1",
    uiManager->addUIBackground("text bg", {text->getRect().position - sf::Vector2f(3, 3), text->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel1", text);

    uiManager->addToGroup("panel1", launchButton);

    panel1 = uiManager->getGroup("panel1");
}

void Level1::specificUpdate(float dt, float time)
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
                }
                else if (currAnim->second <= 2)
                {
                    float offset = -.15f * (static_cast<float>(pow(currAnim->second, 3))) * 500 * dt;
    
                    for (auto e : *panel1)
                    {
                        e->changeOffset({offset, 0});
                    }
                }
                else
                {
                    animations[0].erase(animations[0].begin());
                }
    
                currAnim->second += dt;
            }
        }
    }

    if (launchButton && launchButton->isDown())
    {
        launchPad->launch();

        beginAnimation("hide all", 0);
    }
}

