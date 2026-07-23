#include "game.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

Game::Game() {}

void Game::start()
{
    window = Window(static_cast<sf::Vector2f>(launchPad.getBackgroundSize()));
    window.create(sf::VideoMode(window.windowedResolution), sf::Style::Close);

    launchPad.reset();
    launchPad.random = &random;

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
        }
        if (event->is<sf::Event::FocusGained>())
        {
            gameClock.start();
        }

        if (!gameClock.isRunning()) continue;

        if (auto keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Escape)
            {
                quit();
            }
            else if (keyPressed->code == sf::Keyboard::Key::Enter)
            {
                launchPad.launch();
            }
            else if (keyPressed->code == sf::Keyboard::Key::R)
            {
                launchPad.reset();
            }
            else if (keyPressed->code == sf::Keyboard::Key::F11)
            {
                window.toggleFullscreen();
            }
            else if (keyPressed->code == sf::Keyboard::Key::P)
            {
                launchPad.addParticle(gameClock.getElapsedTime().asSeconds());
            }
            else if (keyPressed->code == sf::Keyboard::Key::U)
            {
                uiManager.clearUI();

                uiManager.addUIBackground({
                    {10, 10},
                    window.window.mapPixelToCoords(sf::Mouse::getPosition(window.window))
                });

                uiManager.addUIButton(&window.window, {{10, 10}, {36, 36}});
            }
            else if (keyPressed->code == sf::Keyboard::Key::X)
            {
                uiManager.clearUI();
            }
        }
    }
}

void Game::update()
{
    launchPad.update(dt, gameClock.getElapsedTime().asSeconds());

    uiManager.update(dt);
}

void Game::draw()
{
    window.window.clear(sf::Color(10,10,10));
    
    launchPad.draw(window.window);
    
    uiManager.draw(window.window);

    window.window.display();
}

void Game::quit()
{
    window.window.close();
}