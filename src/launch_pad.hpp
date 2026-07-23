#pragma once

#include <SFML/Graphics.hpp>
#include "particle.hpp"

class Random;

class LaunchPad
{
public:
    LaunchPad();

    void reset();

    void launch();

    void update(float dt);

    void draw(sf::RenderWindow& window);

    sf::Vector2u getBackgroundSize();

    void addParticle();

    Random* random;
private:
    sf::Texture bgTexture;
    sf::Sprite background;

    sf::Texture launchPadTexture;
    sf::Sprite launchPad;

    sf::Texture rocketTexture;
    sf::Sprite rocket;

    const sf::Vector2f rocketStartPosition;
    const float rocketStartSpeed;
    const float rocketSpeedMultiplier;
    
    bool launching;
    float rocketSpeed;



    std::vector<Particle> particles_behind;
    std::vector<Particle> particles_infront;
    sf::Texture particleTexture;
};