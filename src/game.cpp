#include "game.hpp"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cmath>
#include <iostream>
#include "defaults.hpp"
#include "launch_pad.hpp"
#include "level_0.hpp"
#include "level_1.hpp"
#include "level_2.hpp"
#include "level_3.hpp"
#include "level_4.hpp"
#include "level_5.hpp"
#include "level_6.hpp"
#include "level_7.hpp"

Game::Game() {}

void Game::start()
{
    window = Window(static_cast<sf::Vector2f>(launchPad.getBackgroundSize()));
    window.create(sf::VideoMode(window.windowedResolution), sf::Style::Close, 60);

    launchPad.random = &random;
    launchPad.soundPlayer = &soundPlayer;

    uiManager = UIManager(&window.window, &soundPlayer);

    currLevel = 0;
    loadLevels();

    uiManager.timeIndicator = std::make_unique<UIBackground>("LEVEL", &uiManager, &soundPlayer, &uiManager.uiBackgroundTexture, sf::FloatRect({-1, static_cast<float>(launchPad.getBackgroundSize().y) - 6}, {static_cast<float>(launchPad.getBackgroundSize().x) + 1, 6}), defaultTexCoords.bgBar);

    uiManager.levelIndicator = std::make_unique<UIText>("LEVEL", &uiManager, &soundPlayer, sf::FloatRect({static_cast<sf::Vector2f>(launchPad.getBackgroundSize()) - sf::Vector2f(25, 25)}, {20, 1}), &uiManager.uiTextFont, "9", 'h', sf::Color::White);
    uiManager.levelIndicator->valueReadInt = &currLevel;

    run();
}

void Game::run()
{
    float secondCounter = 0;

	while (window.window.isOpen())
	{
        dt = dtClock.restart().asSeconds();
        
        if (secondCounter >= 1)
        {
            std::cout << "FPS: " << 1.f / dt << '\n';

            secondCounter = 0;
        }
        else
        {
            secondCounter += dt;
        }
        
        events();

        if (gameClock.isRunning())
        {
            update();
        }

        draw();
	}
}

void Game::events()
{
    while (const std::optional event = window.window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            quit();
        }
        if (event->is<sf::Event::FocusLost>())
        {
            gameClock.stop();

            soundPlayer.pauseAll();
        }
        if (event->is<sf::Event::FocusGained>())
        {
            gameClock.start();

            soundPlayer.playAll();
        }

        if (!gameClock.isRunning()) continue;

        if (auto mouseScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
        {
            if (mouseScrolled->delta > 0)
            {
                window.setViewRect({window.window.mapPixelToCoords(sf::Mouse::getPosition(window.window)), window.window.getView().getSize() * .8f});
            }
            else if (mouseScrolled->delta < 0)
            {
                window.setViewRect({{launchPad.getBackgroundSize().x / 2.f, launchPad.getBackgroundSize().y / 2.f}, static_cast<sf::Vector2f>(launchPad.getBackgroundSize())});
            }
        }

        if (auto keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Escape)
            {
                quit();
            }
            else if (keyPressed->code == sf::Keyboard::Key::R)
            {
                levels[currLevel]->setup();
            }
            else if (keyPressed->code == sf::Keyboard::Key::F11)
            {
                window.toggleFullscreen();
            }
            // else if (keyPressed->code == sf::Keyboard::Key::Right)
            // {
            //     if (currLevel < levels.size() - 1)
            //     {
            //         currLevel++;
            //         levels[currLevel]->setup();
            //     }
            // }
            // else if (keyPressed->code == sf::Keyboard::Key::Left)
            // {
            //     if (currLevel > 0)
            //     {
            //         currLevel--;
            //         levels[currLevel]->setup();
            //     }
            // }
        }
    }
}

void Game::update()
{
    soundPlayer.update();

    auto result = launchPad.update(dt, gameClock.getElapsedTime().asSeconds());

    if (result.first)
    {
        if (result.second)
        {
            if (currLevel > 0) soundPlayer.play("level finish");

            currLevel++;
            loadLevels();
        }
        else
        {
            loadLevels();
        }
    }

    uiManager.update(dt);

    if (uiManager.timeIndicator)
    {
        float rem = levels[currLevel]->timeRemainingPercent();
        
        if (rem == 1)
        {
            uiManager.timeIndicator->setOffset({0, 100});
        }
        else
        {
            uiManager.timeIndicator->setOffset({0, 0});
        }

        int red;
        int green;
        
        if (rem > .5f)
        {
            red = 255 * (1 - rem) * 2;
            green = 255;
        }
        else
        {
            red = 255;
            green = 255 * rem * 2;
        }

        uiManager.timeIndicator->resize({static_cast<float>(launchPad.getBackgroundSize().x) * rem + 1, 6});
        uiManager.timeIndicator->setColor(sf::Color(red, green, 0));
    }

    levels[currLevel]->update(dt, gameClock.getElapsedTime().asSeconds());
}

void Game::draw()
{
    window.window.clear(sf::Color(10,10,10));
    
    launchPad.draw(window.window);
    
    uiManager.draw(window.window);

    if (auto l = dynamic_cast<Level7*>(levels[currLevel].get()))
    {
        l->draw();
    }

    window.window.display();
}

void Game::quit()
{
    window.window.close();
}

void Game::loadLevels()
{
    levels.clear();

    levels.emplace_back(std::make_unique<Level0>(&window.window, &launchPad, &uiManager, -1));
    levels.emplace_back(std::make_unique<Level1>(&window.window, &launchPad, &uiManager, -1));
    levels.emplace_back(std::make_unique<Level2>(&window.window, &launchPad, &uiManager, 30));
    levels.emplace_back(std::make_unique<Level3>(&window.window, &launchPad, &uiManager, 25));
    levels.emplace_back(std::make_unique<Level4>(&window.window, &launchPad, &uiManager, 15));
    levels.emplace_back(std::make_unique<Level5>(&window.window, &launchPad, &uiManager, 20));
    levels.emplace_back(std::make_unique<Level6>(&window.window, &launchPad, &uiManager, 30));
    levels.emplace_back(std::make_unique<Level7>(&window.window, &launchPad, &uiManager, 30));

    levels[currLevel]->setup();
}