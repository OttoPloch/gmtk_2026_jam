#include "game.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>

Game::Game() {}

void Game::start()
{
    window = Window(static_cast<sf::Vector2f>(launchPad.getBackgroundSize()));
    window.create(sf::VideoMode(window.windowedResolution), sf::Style::Close);

    launchPad.reset();

    run();
}

void Game::run()
{
	while (window.window.isOpen())
	{
		while (const std::optional event = window.window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				quit();
			}
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
			}
		}

        update();

        draw();
	}
}

void Game::update()
{
    launchPad.update();
}

void Game::draw()
{
    window.window.clear(sf::Color(10,10,10));
    
    launchPad.draw(window.window);
    
    window.window.display();
}

void Game::quit()
{
    window.window.close();
}