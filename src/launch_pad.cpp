#include "launch_pad.hpp"
#include <iostream>

LaunchPad::LaunchPad() :
bgTexture("../../assets/launch site.png"),
background(bgTexture),
launchPadTexture("../../assets/launch pad.png"),
launchPad(launchPadTexture),
rocketTexture("../../assets/rocket.png"),
rocket(rocketTexture),
rocketStartPosition(242, 216),
rocketStartSpeed(.01f),
rocketSpeedMultiplier(1.01f),
launching(false),
rocketSpeed(rocketStartSpeed)
{
    rocket.setOrigin({rocket.getLocalBounds().size.x / 2.f, static_cast<float>(rocket.getLocalBounds().size.y)});
}

void LaunchPad::reset()
{
    rocket.setPosition(rocketStartPosition);
    
    launching = false;
    rocketSpeed = rocketStartSpeed;
}

void LaunchPad::launch()
{
    launching = true;
}

void LaunchPad::update()
{
    if (launching)
    {
        rocketSpeed *= rocketSpeedMultiplier;

        rocket.move({0, -rocketSpeed});

        if (rocket.getPosition().y < 0)
        {
            launching = false;
        }
    }

    std::cout << launching << '\n';
}

void LaunchPad::draw(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(rocket);
    window.draw(launchPad);
}

sf::Vector2u LaunchPad::getBackgroundSize()
{
    return bgTexture.getSize();
}