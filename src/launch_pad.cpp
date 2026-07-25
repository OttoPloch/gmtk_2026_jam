#include "launch_pad.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <iostream>
#include "random.hpp"
#include "sound_player.hpp"

LaunchPad::LaunchPad() :
bgTexture("assets/launch site.png"),
background(bgTexture),
launchPadTexture("assets/launch pad.png"),
launchPad(launchPadTexture),
rocketTexture("assets/rocket.png"),
rocket(rocketTexture),
rocketStartPosition(242, 216),
rocketStartSpeed(.6f),
rocketSpeedMultiplier(1.6f),
launching(false),
rocketSpeed(rocketStartSpeed)
{
    rocket.setOrigin({rocket.getLocalBounds().size.x / 2.f, static_cast<float>(rocket.getLocalBounds().size.y)});

    if (!particleTexture.loadFromFile("assets/particles.png"))
    {
        std::cout << "ERROR loading particle texture.\n";
    }
    
    reset();
}

void LaunchPad::reset()
{
    rocket.setPosition(rocketStartPosition);
    
    launching = false;
    rocketSpeed = rocketStartSpeed;

    particlesPerSecond = 60;
    particlesToMake = 0;

    fail_particlesPerSecond = 30;
    fail_particlesToMake = 0;
    timeFailing = 0;

    particles_behind.clear();
    particles_middle.clear();
    particles_infront.clear();

    restart = false;
    failing = false;

    goToNextLevel = false;

    popped = false;
}

void LaunchPad::launch()
{
    if (failing) return;

    soundPlayer->play("launch");

    launching = true;
}

void LaunchPad::nextLevel()
{
    goToNextLevel = true;
}

std::pair<bool, bool> LaunchPad::update(float dt, float time)
{
    if (goToNextLevel)
    {
        return {true, true};
    }

    if (launching)
    {
        particlesToMake += dt * particlesPerSecond;

        while (particlesToMake >= 1)
        {
            addParticle(time);

            particlesToMake -= 1;
        }

        rocketSpeed *= std::pow(rocketSpeedMultiplier, dt);

        rocket.move({0, -rocketSpeed * dt});

        if (rocket.getPosition().y < -static_cast<int>(getBackgroundSize().y) * 3)
        {
            return {true, true};
        }
    }
    else if (failing)
    {
        if (timeFailing < 6) fail_particlesPerSecond += timeFailing * 20 * dt;
        else fail_particlesPerSecond += timeFailing * 100 * dt;

        if (timeFailing < 6) fail_particlesToMake += dt * fail_particlesPerSecond;
        else if (!popped)
        {
            soundPlayer->play("pop");
            popped = true;
        }

        while (fail_particlesToMake >= 1)
        {
            addParticle(time, (timeFailing >= 5));

            fail_particlesToMake -= 1;
        }

        if (timeFailing >= 7)
        {
            restart = true;
        }

        timeFailing += dt;
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

    if (restart) return {true, false};

    return {false, false};
}

void LaunchPad::draw(sf::RenderWindow& window)
{
    window.draw(background);
    for (auto& p : particles_behind) p.draw(window);
    if (timeFailing < 5.5) window.draw(rocket);
    for (auto& p : particles_middle) p.draw(window);
    window.draw(launchPad);
    for (auto& p : particles_infront) p.draw(window);
}

sf::Vector2u LaunchPad::getBackgroundSize()
{
    return bgTexture.getSize();
}

void LaunchPad::addParticle(float time, bool exploding)
{
    if (!failing)
    {
        sf::Vector2f position({rocket.getPosition().x, rocket.getPosition().y + 2});
        sf::IntRect texCoords({0, 0}, {16, 16});
        bool fades = true;
        bool shrinks = false;
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
    
            if (layer == 1) particles_behind.emplace_back(random, time, sf::FloatRect(position, {size, size}), texCoords, &particleTexture, particleColor, lifetime, velocity, fades, shrinks, minBounds, maxBounds);
            else particles_infront.emplace_back(random, time, sf::FloatRect(position, {size, size}), texCoords, &particleTexture, particleColor, lifetime, velocity, fades, shrinks, minBounds, maxBounds);
        }
        else if (layer == 2)
        {
            // fire
            size = random->getRandInt(1, 6);
            particleColor = sf::Color(random->getRandInt(200, 255), random->getRandInt(30, 100), 0);
            lifetime = random->getRandInt(1, 2) / 3.f;
            velocity = sf::Vector2f(random->getRandInt(-5, 5), random->getRandInt(5, 10));
    
            particles_middle.emplace_back(random, time, sf::FloatRect(position, {size, size}), texCoords, &particleTexture, particleColor, lifetime, velocity, fades, shrinks, minBounds, maxBounds);
        }
    }
    else
    {
        if (!exploding)
        {
            sf::Vector2f position({rocket.getPosition().x, rocket.getPosition().y - random->getRandInt(0, 40)});
            sf::IntRect texCoords({0, 0}, {16, 16});
            bool fades = true;
            bool shrinks = true;
            sf::Vector2f minBounds(0, -static_cast<int>(getBackgroundSize().y));
            sf::Vector2f maxBounds(getBackgroundSize().x, rocketStartPosition.y + 10 + random->getRandInt(-3, 3));
        
            float size;
            sf::Color particleColor;
            float lifetime;
            sf::Vector2f velocity;
        
            // smoke
            size = random->getRandInt(2, 20);
            int brightness = random->getRandInt(140, 200);
            particleColor = sf::Color(brightness + 20, brightness + 10, brightness);
            lifetime = random->getRandInt(1, 8);
            velocity = sf::Vector2f(random->getRandInt(-30, 30), random->getRandInt(-30, 30));

            if (random->getRandInt(0, 1) == 1) particles_behind.emplace_back(random, time, sf::FloatRect(position, {size, size}), texCoords, &particleTexture, particleColor, lifetime, velocity, fades, shrinks, minBounds, maxBounds);
            else particles_infront.emplace_back(random, time, sf::FloatRect(position, {size, size}), texCoords, &particleTexture, particleColor, lifetime, velocity, fades, shrinks, minBounds, maxBounds);
        }
        else
        {
            sf::Vector2f position({rocket.getPosition().x + random->getRandInt(-10, 10), rocket.getPosition().y - random->getRandInt(0, 40)});
            sf::IntRect texCoords({0, 0}, {16, 16});
            bool fades = true;
            bool shrinks = true;
            sf::Vector2f minBounds(0, -static_cast<int>(getBackgroundSize().y));
            sf::Vector2f maxBounds(getBackgroundSize().x, rocketStartPosition.y + 10 + random->getRandInt(-3, 6));
    
            float size;
            sf::Color particleColor;
            float lifetime;
            sf::Vector2f velocity;
        
            int type = random->getRandInt(1, 4);
        
            if (type == 1)
            {
                // smoke
                size = random->getRandInt(5, 20);
                int brightness = random->getRandInt(140, 200);
                particleColor = sf::Color(brightness + 20, brightness + 10, brightness);
                lifetime = random->getRandInt(1, 20);
                velocity = sf::Vector2f(random->getRandInt(-50, 50), random->getRandInt(-50, 50));
            }
            else
            {
                // fire
                size = random->getRandInt(3, 30);
                particleColor = sf::Color(random->getRandInt(200, 255), random->getRandInt(30, 100), 0);
                lifetime = random->getRandInt(1, 20) / 3.f;
                velocity = sf::Vector2f(random->getRandInt(-100, 100), random->getRandInt(-100, 100));
            }

            if (random->getRandInt(0, 1) == 1) particles_behind.emplace_back(random, time, sf::FloatRect(position, {size, size}), texCoords, &particleTexture, particleColor, lifetime, velocity, fades, shrinks, minBounds, maxBounds);
            else particles_infront.emplace_back(random, time, sf::FloatRect(position, {size, size}), texCoords, &particleTexture, particleColor, lifetime, velocity, fades, shrinks, minBounds, maxBounds);   
        }
    }
}

void LaunchPad::fail()
{
    if (!launching)
    {
        failing = true;
    }
}