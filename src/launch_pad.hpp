#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "particle.hpp"

class Random;

class LaunchPad
{
public:
    LaunchPad();

    void reset();

    void launch();

    std::pair<bool, bool> update(float dt, float time);

    void draw(sf::RenderWindow& window);

    sf::Vector2u getBackgroundSize();

    void addParticle(float time, bool exploding = false);

    void fail();

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
    std::vector<Particle> particles_middle;
    std::vector<Particle> particles_infront;
    sf::Texture particleTexture;

    int particlesPerSecond;
    float particlesToMake;

    bool restart;
    bool failing;

    int fail_particlesPerSecond;
    float fail_particlesToMake;
    float timeFailing;
};