#include "level_0.hpp"
#include "ui_manager.hpp"
#include "launch_pad.hpp"

Level0::Level0() {}

Level0::Level0(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager, float timeToComplete) : Level(window, launchPad, uiManager, timeToComplete)
{
    started = false;
}

void Level0::createUI()
{
    sf::Vector2f panelPos(40, 60);

    uiManager->resetUI();
    uiManager->addToGroup("panel1", uiManager->addUIBackground("BG", {panelPos, {145, 70}}, defaultTexCoords.bg, 'l'));
    startButton = uiManager->addUIButton("Button", window, {{panelPos.x + 15, panelPos.y + 20}, {1, 1}}, true, defaultTexCoords.buttonTexCoords);
    uiManager->addToGroup("panel1", startButton);

    UIText* text = uiManager->addUIText("text", {{panelPos.x + 63, panelPos.y + 25}, {60, 1}}, "PLAY", true, sf::Color::White);
    uiManager->addToGroup("panel1", text);

    uiManager->addToGroup("panel1", uiManager->addUIBackground("text bg", {text->getRect().position - sf::Vector2f(3, 3), text->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));

    panel1 = uiManager->getGroup("panel1");
}

void Level0::specificUpdate(float dt, float time)
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

    if (startButton && startButton->isDown())
    {
        beginAnimation("hide all", 0);

        started = true;
    }

    if (animations[0].size() == 0 && started)
    {
        launchPad->nextLevel();
    }
}