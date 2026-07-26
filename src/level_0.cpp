#include "level_0.hpp"
#include "defaults.hpp"
#include "ui_manager.hpp"
#include "launch_pad.hpp"

Level0::Level0() {}

Level0::Level0(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager, float timeToComplete) : Level(window, launchPad, uiManager, timeToComplete)
{
    started = false;
}

void Level0::createUI()
{
    uiManager->resetUI();
    


    sf::Vector2f panelPos(40, 60);
    uiManager->defaultGroup = "panel1";

    startButton = uiManager->addUIButton("Button", window, {{panelPos.x + 15, panelPos.y + 20}, {1, 1}}, true, defaultTexCoords.buttonTexCoords);
    UIText* text = uiManager->addUIText("text", {{panelPos.x + 63, panelPos.y + 25}, {60, 1}}, "PLAY", 'h', sf::Color::White);

    uiManager->addToGroup("panel1",
    uiManager->addUIBackground("BG", {panelPos, {145, 70}}, defaultTexCoords.bg, 'l'));

    uiManager->addToGroup("panel1",
    uiManager->addUIBackground("text bg", {text->getRect().position - sf::Vector2f(3, 3), text->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel1", text);

    uiManager->addToGroup("panel1", startButton);

    panel1 = uiManager->getGroup("panel1");



    std::string infoTextContent = "Controls:\n - Click and Drag for most\n   things\n - R to reset\n - F11 to toggle fullscreen\n - Escape to quit\n\nMade with SFML for the\n2026 GMTK Game Jam.\nAttributions are below.\n\n\n";
    infoTextContent += "Electronics-Flashlight-Plastic-Button-03.wav by DWOBoyle -- https://freesound.org/s/152535/ -- License: Attribution 4.0\n\nbubble pop 6 by nomentero -- https://freesound.org/s/744144/ -- License: Creative Commons 0\n\nTicking Timer 20 Sec.wav by LilMati -- https://freesound.org/s/487722/ -- License: Creative Commons 0\n\nButton Click 1.wav by Mellau -- https://freesound.org/s/506054/ -- License: Attribution NonCommercial 4.0";

    int newLineCounter = 0;
    std::vector<int> newLineIndices;
    for (int i = 0; i < infoTextContent.size(); i++)
    {
        if (infoTextContent[i] == '\n') newLineCounter = 0;

        if (newLineCounter >= 30)
        {
            newLineIndices.emplace_back(i);

            newLineCounter = 0;
        }
        else
        {
            newLineCounter++;
        }
    }

    if (newLineIndices.size() > 0)
    {
        for (int i = newLineIndices.size() - 1; i >= 0; i--)
        {
            infoTextContent.insert(newLineIndices[i], "\n");
        }
    }

    sf::Vector2f infoPos(static_cast<float>(launchPad->getBackgroundSize().x) - 150, 30);

    uiManager->defaultGroup = "info";

    infoButton = uiManager->addUIButton("info button", window, {{static_cast<float>(launchPad->getBackgroundSize().x) - 22, 10}, {1, 1}}, true, defaultTexCoords.buttonInfoTexCoords);
    
    uiManager->addToGroup("info", infoButton);
    uiManager->defaultGroup = "info display";
    uiManager->addToGroup("info display",
    uiManager->addUIBackground("info bg", {infoPos, {130, 170}}, defaultTexCoords.bg, 'r'));
    uiManager->addToGroup("info display",
    uiManager->addUIText("info text", {infoPos + sf::Vector2f(15, 15), {98, 0}}, infoTextContent, 'h', sf::Color::White));

    infoGroup = uiManager->getGroup("info display");

    showInfo = false;
    for (auto& e : *infoGroup)
    {
        e->setOffset({150, 0});
    }
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
            else if (currAnim->first == "show info")
            {
                if (currAnim->second <= .001f)
                {
                    float offset = 150;
    
                    for (auto e : *infoGroup)
                    {
                        e->setOffset({offset, 0});
                    }
                }
    
                if (currAnim->second <= .5f)
                {
                    float offset = -300 * dt;
    
                    for (auto e : *infoGroup)
                    {
                        e->changeOffset({offset, 0});
                    }
                }
                else
                {
                    for (auto e : *infoGroup)
                    {
                        e->setOffset({0, 0});
                    }
    
                    animations[1].erase(animations[1].begin());
                }
    
                currAnim->second += dt;
            }
            else if (currAnim->first == "hide info")
            {
                if (currAnim->second <= .001f)
                {
                    float offset = 0;
    
                    for (auto e : *infoGroup)
                    {
                        e->setOffset({offset, 0});
                    }
                }
    
                if (currAnim->second <= .5f)
                {
                    float offset = 300 * dt;
    
                    for (auto e : *infoGroup)
                    {
                        e->changeOffset({offset, 0});
                    }
                }
                else
                {
                    for (auto e : *infoGroup)
                    {
                        e->setOffset({150, 0});
                    }
    
                    animations[1].erase(animations[1].begin());
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

    if (infoButton && infoButton->isDown())
    {
        showInfo = !showInfo;

        if (showInfo)
        {
            beginAnimation("show info", 1);
        }
        else
        {
            beginAnimation("hide info", 1);
        }
    }

    if (animations[0].size() == 0 && started)
    {
        launchPad->nextLevel();
    }
}