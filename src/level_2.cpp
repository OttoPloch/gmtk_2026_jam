#include "level_2.hpp"
#include "defaults.hpp"
#include "launch_pad.hpp"
#include "ui_manager.hpp"
#include "ui_button.hpp"
#include "ui_dial.hpp"
#include "ui_collider.hpp"

Level2::Level2() {}

Level2::Level2(sf::RenderWindow* window, LaunchPad* launchPad, UIManager* uiManager, float timeToComplete) : Level(window, launchPad, uiManager, timeToComplete),
powerLevel(0)
{}

void Level2::createUI()
{
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
    UIText* text3 = uiManager->addUIText("z power text", {{panel2Pos.x + 27.5f, panel2Pos.y + 79}, {15, 100}}, "100%");
    UIText* text4 = uiManager->addUIText("power text", {{panel2Pos.x + 9, panel2Pos.y + 11}, {50, 100}}, "LAUNCH POWER", 'h', sf::Color::White);
    
    uiManager->addToGroup("panel2",
    uiManager->addUIBackground("bg2", {panel2Pos, {70, 95}}, defaultTexCoords.bgSmall, 't'));

    uiManager->addToGroup("panel2",
    uiManager->addUIBackground("text4 bg", {text4->getRect().position - sf::Vector2f(3, 3), text4->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel2", text4);

    uiManager->addToGroup("panel2",
    uiManager->addUIBackground("text3 bg", {text3->getRect().position - sf::Vector2f(3, 3), text3->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));
    uiManager->addToGroup("panel2", text3);

    uiManager->addToGroup("panel2", powerDial);

    uiManager->defaultGroup = "LEVEL";
    panel2Collider = uiManager->addUICollider("panel2Collider", window, {{panel2Pos.x - 15, 0}, {100, 10}}, false);

    text3->valueRead = &powerLevel;
    text3->valueInPercent = true;
            
    panel2 = uiManager->getGroup("panel2");

    


    sf::Vector2f notesPos(50, static_cast<float>(launchPad->getBackgroundSize().y - 106));
    uiManager->defaultGroup = "notes";

    UIText* notesText = uiManager->addUIText("notes text", {notesPos + sf::Vector2f(15, 15), {0, 10}}, "Todo:\n     - set power to 100%", 'l', sf::Color::White);

    uiManager->addToGroup("notes",
    uiManager->addUIBackground("notes bg", {notesPos, {200, 80}}, defaultTexCoords.bg, 'b'));

    uiManager->addToGroup("notes",
    uiManager->addUIBackground("notes text bg", {notesText->getRect().position - sf::Vector2f(3, 3), notesText->getRect().size + sf::Vector2f(6, 6)}, defaultTexCoords.bgText));

    uiManager->addToGroup("notes", notesText);

    notesCollider = uiManager->addUICollider("notes collider", window, {{notesPos.x - 15, static_cast<float>(launchPad->getBackgroundSize().y - 11)}, {230, 40}}, false, true);

    notes = uiManager->getGroup("notes");


    beginAnimation("hide all", 0);
}

void Level2::specificUpdate(float dt, float time)
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

                    for (auto e : *notes)
                    {
                        e->changeOffset({0, -offset});
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

                    for (auto e : *notes)
                    {
                        e->changeOffset({0, -offset});
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
            else if (currAnim->first == "show notes")
            {
                if (currAnim->second <= .001f)
                {
                    float offset = 150;
    
                    for (auto e : *notes)
                    {
                        e->setOffset({0, offset});
                    }
                }
    
                if (currAnim->second <= .5f)
                {
                    float offset = -300 * dt;
    
                    for (auto e : *notes)
                    {
                        e->changeOffset({0, offset});
                    }
                }
                else
                {
                    for (auto e : *notes)
                    {
                        e->setOffset({0, 0});
                    }
    
                    animations[10].erase(animations[10].begin());
                }
    
                currAnim->second += dt;
            }
            else if (currAnim->first == "hide notes")
            {
                if (currAnim->second <= .001f)
                {
                    float offset = 0;
    
                    for (auto e : *notes)
                    {
                        e->setOffset({0, offset});
                    }
                }
    
                if (currAnim->second <= .5f)
                {
                    float offset = 300 * dt;
    
                    for (auto e : *notes)
                    {
                        e->changeOffset({0, offset});
                    }
                }
                else
                {
                    for (auto e : *notes)
                    {
                        e->setOffset({0, 150});
                    }
    
                    animations[10].erase(animations[10].begin());
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

        if (notesCollider && notesCollider->onEnter())
        {
            if (animations[10].size() == 0)
            {
                if ((*notes)[0]->getOffset() != sf::Vector2f(0, 0))
                {
                    beginAnimation("show notes", 10);
                }
                else
                {
                    beginAnimation("hide notes", 10);
                }
            }
        }
    }

    if (powerDial) powerLevel = powerDial->getValue();

    if (launchButton && launchButton->isDown())
    {
        if (powerLevel >= 100)
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
        notesCollider = nullptr;
        uiManager->removeUICollider("panel1Collider");
        uiManager->removeUICollider("panel2Collider");
        uiManager->removeUICollider("notes collider");
    }
}
