#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window( sf::VideoMode( { 1440, 810 } ), "SFML works!" );
	window.setFramerateLimit(60);

	sf::Texture bg("../../assets/launch site.png");
	sf::Sprite bgSprite(bg);
	sf::Vector2f SCALE(static_cast<float>(window.getSize().x) / static_cast<float>(bg.getSize().x), static_cast<float>(window.getSize().y) / static_cast<float>(bg.getSize().y));
	bgSprite.setScale(SCALE);

	sf::Texture launchPad("../../assets/launch pad.png");
	sf::Sprite launchPadSprite(launchPad);
	launchPadSprite.setScale(SCALE);

	sf::Texture rocket("../../assets/rocket.png");
	sf::Sprite rocketSprite(rocket);
	rocketSprite.setScale(SCALE);
	rocketSprite.setOrigin({rocket.getSize().x / 2.f, static_cast<float>(rocket.getSize().y)});

	sf::Vector2f ROCKET_START(242, 216);

	rocketSprite.setPosition({ROCKET_START.x * SCALE.x, ROCKET_START.y * SCALE.y});

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		rocketSprite.move({0, -2});

		window.clear(sf::Color(10,10,10));
		window.draw( bgSprite );
		window.draw(rocketSprite);
		window.draw(launchPadSprite);
		window.display();
	}
}
