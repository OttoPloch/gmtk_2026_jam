#include "particle.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>
#include "random.hpp"

Particle::Particle(Random* random, float time, sf::FloatRect rect, sf::IntRect texCoords, sf::Texture* texture, float lifetime, sf::Vector2f velocity, bool fades, sf::Vector2f minBounds, sf::Vector2f maxBounds) : particle(*texture), lifetime(lifetime), velocity(velocity), fades(fades), minBounds(minBounds), maxBounds(maxBounds)
{
    particleSize = rect.size;

    particle.setTexture(*texture);
    particle.setTextureRect(texCoords);
    particle.setOrigin({particle.getLocalBounds().size.x / 2.f, static_cast<float>(particle.getLocalBounds().size.y)});
    particle.setPosition(rect.position);
    particle.setScale({rect.size.x / particle.getGlobalBounds().size.x, rect.size.y / particle.getGlobalBounds().size.y});

    particleAlpha = 255;
    particleBrightness = random->getRandInt(230, 255);
    startTime = time;
    finished = false;
}

bool Particle::update(float dt, float time)
{
    if (!finished)
    {
        float elapsedTime = time - startTime;

        particle.move(velocity * dt);

        if (particle.getPosition().x - particleSize.x / 2.f < minBounds.x) particle.setPosition({minBounds.x + particleSize.x / 2.f, particle.getPosition().y});
        else if (particle.getPosition().x + particleSize.x / 2.f > maxBounds.x) particle.setPosition({maxBounds.x - particleSize.x / 2.f, particle.getPosition().y});

        if (particle.getPosition().y - particleSize.y < minBounds.y) particle.setPosition({particle.getPosition().x, minBounds.y + particleSize.y});
        else if (particle.getPosition().y > maxBounds.y) particle.setPosition({particle.getPosition().x, maxBounds.y});
        
        if (fades)
        {
            particleAlpha = std::min((255 - 255 * (elapsedTime / lifetime)), 255.f);
            particle.setColor(sf::Color(particleBrightness, particleBrightness, particleBrightness, particleAlpha));
        }

        if (elapsedTime >= lifetime)
        {
            particle.setColor(sf::Color::Red);

            finished = true;

            return true;
        }
    }

    return false;
}

void Particle::draw(sf::RenderWindow& window)
{
    window.draw(particle);
}
