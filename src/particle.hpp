#pragma once

#include <SFML/Graphics.hpp>

class Random;

class Particle
{
public:
    Particle();
    
    Particle(Random* random, float time, sf::FloatRect rect, sf::IntRect texCoords, sf::Texture* texture, sf::Color color, float lifetime, sf::Vector2f velocity, bool fades, sf::Vector2f minBounds, sf::Vector2f maxBounds);

    bool update(float dt, float time);

    void draw(sf::RenderWindow& window);
private:
    sf::Vector2f particleSize;

    sf::Sprite particle;
    float particleAlpha;
    sf::Color color;
    
    float lifetime;
    sf::Vector2f velocity;
    bool fades;
    sf::Vector2f minBounds;
    sf::Vector2f maxBounds;
    
    float startTime;
    bool finished;
};