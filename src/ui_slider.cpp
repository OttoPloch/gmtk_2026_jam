#include "ui_slider.hpp"
#include "utils.hpp"
#include <SFML/Window/Mouse.hpp>

UISlider::UISlider(
    sf::RenderWindow* window,
    sf::Texture* texture,
    sf::FloatRect rect, bool sizeIsScale,
    SliderTemplate sliderTemplate
) : UIElement(rect), window(window), handle(*texture), baseLeft(*texture), baseMiddle(*texture), baseRight(*texture), sliderTemplate(sliderTemplate)
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

    scale = {
        rect.size.x / (sliderTemplate.baseTexCoords[0].size.x + sliderTemplate.baseTexCoords[1].size.x + sliderTemplate.baseTexCoords[2].size.x),
        rect.size.y / (sliderTemplate.baseTexCoords[0].size.y + sliderTemplate.baseTexCoords[1].size.y + sliderTemplate.baseTexCoords[2].size.y)
    };
    handle.setScale(scale);
    baseLeft.setScale(scale);
    baseMiddle.setScale(scale);
    baseRight.setScale(scale);

    setRect(rect);

    grabbed = false;

    value = 0;
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
                handle.setPosition({handlePos.x, mousePos.y - grabOffset.y});

                if (handle.getPosition().y > empty.y) handle.setPosition({handlePos.x, empty.y});
                if (handle.getPosition().y < full.y) handle.setPosition({handlePos.x, full.y});

                value = (handle.getPosition().y - empty.y) / diff;
            }
            else
            {
                handle.setPosition({mousePos.x - grabOffset.x, handlePos.y});
                
                if (handle.getPosition().x < empty.x) handle.setPosition({empty.x, handlePos.y});
                if (handle.getPosition().x > full.x) handle.setPosition({full.x, handlePos.y});
                
                value = (handle.getPosition().x - empty.x) / diff;
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

    baseMiddlePositionOffset = static_cast<sf::Vector2f>(sliderTemplate.baseTexCoords[1].position - sliderTemplate.baseTexCoords[0].position);
    baseMiddlePositionOffset = {baseMiddlePositionOffset.x * scale.x, baseMiddlePositionOffset.y * scale.y};
    baseRightPositionOffset = static_cast<sf::Vector2f>(sliderTemplate.baseTexCoords[2].position - sliderTemplate.baseTexCoords[0].position);
    baseRightPositionOffset = {baseRightPositionOffset.x * scale.x, baseRightPositionOffset.y * scale.y};

    empty = {rect.position.x + sliderTemplate.baseTexCoords[0].size.x * sliderTemplate.emptyPoint.x * scale.x, std::round(rect.position.y + sliderTemplate.baseTexCoords[0].size.y * sliderTemplate.emptyPoint.y * scale.y)};
    full = {rect.position.x + baseRightPositionOffset.x + sliderTemplate.baseTexCoords[2].size.x * sliderTemplate.fullPoint.x * scale.x, std::round(rect.position.y + baseRightPositionOffset.y + sliderTemplate.baseTexCoords[2].size.y * sliderTemplate.fullPoint.y * scale.y)};
    
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
        handle.setPosition({empty.x, empty.y + diff * value});
    }
    else
    {
        handle.setPosition({empty.x + diff * value, empty.y});
    }
    
    baseLeft.setPosition(rect.position);
    baseMiddle.setPosition(rect.position + baseMiddlePositionOffset);
    baseRight.setPosition(rect.position + baseRightPositionOffset);
}

void UISlider::updateVisuals()
{
    setRect(rect);
}