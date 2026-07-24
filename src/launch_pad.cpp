#include "launch_pad.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <iostream>
#include "random.hpp"

LaunchPad::LaunchPad() :
bgTexture("../../assets/launch site.png"),
background(bgTexture),
launchPadTexture("../../assets/launch pad.png"),
launchPad(launchPadTexture),
rocketTexture("../../assets/rocket.png"),
rocket(rocketTexture),
rocketStartPosition(242, 216),
rocketStartSpeed(.6f),
rocketSpeedMultiplier(1.6f),
launching(false),
rocketSpeed(rocketStartSpeed)
{
    rocket.setOrigin({rocket.getLocalBounds().size.x / 2.f, static_cast<float>(rocket.getLocalBounds().size.y)});

    if (!particleTexture.loadFromFile("../../assets/particles.png"))
    {
        std::cout << "ERROR loading particle texture.\n";
    }
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

void LaunchPad::update(float dt, float time)
{
    if (launching)
    {
        addParticle(time);

        rocketSpeed *= std::pow(rocketSpeedMultiplier, dt);

        rocket.move({0, -rocketSpeed * dt});

        if (rocket.getPosition().y < -static_cast<int>(getBackgroundSize().y))
        {
            reset();
        }
    }

    for (int i = 0; i < particles_behind.size(); i++)
    {
        if (particles_behind[i].update(dt, time)) particles_behind.erase(particles_behind.begin() + i);
    }

    for (int i = 0; i < particles_middle.size(); i++)
    {
        if (particles_middle[i].update(dt, time)) particles_middle.erase(particles_middle.begin() + i);
    }

    for (int i = 0; i < particles_infront.size(); i++)
    {
        if (particles_infront[i].update(dt, time)) particles_infront.erase(particles_infront.begin() + i);
    }
}

void LaunchPad::draw(sf::RenderWindow& window)
{
    window.draw(background);
    for (auto& p : particles_behind) p.draw(window);
    window.draw(rocket);
    for (auto& p : particles_middle) p.draw(window);
    window.draw(launchPad);
    for (auto& p : particles_infront) p.draw(window);
}

sf::Vector2u LaunchPad::getBackgroundSize()
{
    return bgTexture.getSize();
}

void LaunchPad::addParticle(float time)
{
    sf::Vector2f position({rocket.getPosition().x, rocket.getPosition().y + 2});
    sf::IntRect texCoords({0, 0}, {16, 16});
    bool fades = true;
    sf::Vector2f minBounds(0, -static_cast<int>(getBackgroundSize().y));
    sf::Vector2f maxBounds(getBackgroundSize().x, rocketStartPosition.y + 10 + random->getRandInt(-3, 3));

    float size;
    sf::Color particleColor;
    float lifetime;
    sf::Vector2f velocity;

    int layer = random->getRandInt(1, 3);

    if (layer == 1 || layer == 3)
    {
        // vapor
        size = random->getRandInt(4, 10);
        int brightness = random->getRandInt(230, 255);
        particleColor = sf::Color(brightness, brightness, brightness);
        lifetime = random->getRandInt(1, 2);
        velocity = sf::Vector2f(random->getRandInt(-20, 20), random->getRandInt(10, 30));

        if (layer == 1) particles_behind.emplace_back(random, time, sf::FloatRect(position, {size, size}), texCoords, &particleTexture, particleColor, lifetime, velocity, fades, minBounds, maxBounds);
        else particles_infront.emplace_back(random, time, sf::FloatRect(position, {size, size}), texCoords, &particleTexture, particleColor, lifetime, velocity, fades, minBounds, maxBounds);
    }
    else if (layer == 2)
    {
        // fire
        size = random->getRandInt(1, 6);
        particleColor = sf::Color(random->getRandInt(200, 255), random->getRandInt(30, 100), 0);
        lifetime = random->getRandInt(1, 2) / 3.f;
        velocity = sf::Vector2f(random->getRandInt(-5, 5), random->getRandInt(5, 10));

        particles_middle.emplace_back(random, time, sf::FloatRect(position, {size, size}), texCoords, &particleTexture, particleColor, lifetime, velocity, fades, minBounds, maxBounds);
    }
}