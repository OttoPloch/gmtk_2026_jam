#include "ui_slider.hpp"
#include "utils.hpp"
#include <SFML/Window/Mouse.hpp>
#include "sound_player.hpp"

UISlider::UISlider(
    SoundPlayer* soundPlayer, 
    sf::RenderWindow* window,
    sf::Texture* texture,
    sf::FloatRect rect, bool sizeIsScale,
    SliderTemplate sliderTemplate
) : UIElement(soundPlayer, rect), window(window), handle(*texture), baseLeft(*texture), baseMiddle(*texture), baseRight(*texture), sliderTemplate(sliderTemplate)
{
    if (sizeIsScale) rect.size = {
        (sliderTemplate.baseTexCoords[0].size.x + sliderTemplate.baseTexCoords[1].size.x + sliderTemplate.baseTexCoords[2].size.x) * rect.size.x,
        (sliderTemplate.baseTexCoords[0].size.y + sliderTemplate.baseTexCoords[1].size.y + sliderTemplate.baseTexCoords[2].size.y) * rect.size.y
    };

    handle.setTextureRect(sliderTemplate.handleTexCoords);
    baseLeft.setTextureRect(sliderTemplate.baseTexCoords[0]);
    baseMiddle.setTextureRect(sliderTemplate.baseTexCoords[1]);
    baseRight.setTextureRect(sliderTemplate.baseTexCoords[2]);
    
    handle.setOrigin(sliderTemplate.handleOrigin);

    value = 0;
    lastValue = 0;

    setRect(rect);

    grabbed = false;
}

void UISlider::update()
{
    sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

    if (!grabbed)
    {
        if (mouseCollide(handle.getGlobalBounds(), *window))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                if (canGrab)
                {
                    grabbed = true;
            
                    grabOffset = mousePos - (handle.getGlobalBounds().position + sf::Vector2f(handle.getOrigin().x * scale.x, handle.getOrigin().y * scale.y));
                }

                canGrab = false;
            }
            else
            {
                canGrab = true;
            }
        }
        else
        {
            canGrab = false;
        }
    }
    else
    {
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            grabbed = false;
        }
        else
        {
            sf::Vector2f handlePos = handle.getPosition();

            if (sliderTemplate.vertical)
            {
                handle.setPosition({handlePos.x, std::round(mousePos.y - grabOffset.y)});

                if (handle.getPosition().y > empty.y) handle.setPosition({handlePos.x, empty.y});
                if (handle.getPosition().y < full.y) handle.setPosition({handlePos.x, full.y});

                value = (handle.getPosition().y - empty.y) / diff;
            }
            else
            {
                handle.setPosition({std::round(mousePos.x - grabOffset.x), handlePos.y});
                
                if (handle.getPosition().x < empty.x) handle.setPosition({empty.x, handlePos.y});
                if (handle.getPosition().x > full.x) handle.setPosition({full.x, handlePos.y});
                
                value = (handle.getPosition().x - empty.x) / diff;
            }

            if (std::abs(lastValue - value) >= .15f)
            {
                soundPlayer->play("slider");

                lastValue = value;
            }
        }
    }
}

void UISlider::draw(sf::RenderWindow& window)
{
    window.draw(baseLeft);
    window.draw(baseMiddle);
    window.draw(baseRight);
    window.draw(handle);
}

void UISlider::setRect(sf::FloatRect newRect)
{
    rect = newRect;

    scale = {
        1, 1
    };
    middleScale = {
        rect.size.x / (sliderTemplate.baseTexCoords[0].size.x + sliderTemplate.baseTexCoords[1].size.x + sliderTemplate.baseTexCoords[2].size.x),
        rect.size.y / (sliderTemplate.baseTexCoords[0].size.y + sliderTemplate.baseTexCoords[1].size.y + sliderTemplate.baseTexCoords[2].size.y)
    };
    handle.setScale(scale);
    baseLeft.setScale(scale);
    baseMiddle.setScale(middleScale);
    baseRight.setScale(scale);

    baseMiddlePositionOffset = static_cast<sf::Vector2f>(sliderTemplate.baseTexCoords[1].position - sliderTemplate.baseTexCoords[0].position);
    baseMiddlePositionOffset = {baseMiddlePositionOffset.x * scale.x, baseMiddlePositionOffset.y * scale.y};
    baseRightPositionOffset = static_cast<sf::Vector2f>(sliderTemplate.baseTexCoords[1].position - sliderTemplate.baseTexCoords[0].position);
    baseRightPositionOffset = {baseRightPositionOffset.x * middleScale.x, baseRightPositionOffset.y * middleScale.y};
    baseRightPositionOffset += baseMiddlePositionOffset;

    empty = {rect.position.x + sliderTemplate.baseTexCoords[0].size.x * sliderTemplate.emptyPoint.x * scale.x, rect.position.y + sliderTemplate.baseTexCoords[0].size.y * sliderTemplate.emptyPoint.y * scale.y};
    full = {rect.position.x + baseRightPositionOffset.x + sliderTemplate.baseTexCoords[2].size.x * sliderTemplate.fullPoint.x * scale.x, rect.position.y + baseRightPositionOffset.y + sliderTemplate.baseTexCoords[2].size.y * sliderTemplate.fullPoint.y * scale.y};
    
    if (sliderTemplate.vertical)
    {
        sf::Vector2f temp = empty;
        empty = full;
        full = temp;

        diff = full.y - empty.y;
    }
    else
    {
        diff = full.x - empty.x;
    }

    sf::Vector2f handlePos = handle.getPosition();
    if (sliderTemplate.vertical)
    {
        handle.setPosition({empty.x, std::round(empty.y + diff * value)});
    }
    else
    {
        handle.setPosition({std::round(empty.x + diff * value), empty.y});
    }
    
    baseLeft.setPosition(rect.position);
    baseMiddle.setPosition(rect.position + baseMiddlePositionOffset);
    baseRight.setPosition(rect.position + baseRightPositionOffset);
}

void UISlider::updateVisuals()
{
    setRect(rect);
}