#include "ui_slider.hpp"
#include "utils.hpp"
#include <SFML/Window/Mouse.hpp>

UISlider::UISlider(
    sf::RenderWindow* window,
    sf::Texture* texture,
    sf::FloatRect rect, bool sizeIsScale,
    SliderTemplate sliderTemplate
) : window(window), handle(*texture), baseLeft(*texture), baseMiddle(*texture), baseRight(*texture), rect(rect), handleTexCoords(sliderTemplate.handleTexCoords), baseTexCoords(sliderTemplate.baseTexCoords), vertical(sliderTemplate.vertical)
{
    if (sizeIsScale) rect.size = {
        (baseTexCoords[0].size.x + baseTexCoords[1].size.x + baseTexCoords[2].size.x) * rect.size.x,
        (baseTexCoords[0].size.y + baseTexCoords[1].size.y + baseTexCoords[2].size.y) * rect.size.y
    };

    handle.setTextureRect(handleTexCoords);
    baseLeft.setTextureRect(baseTexCoords[0]);
    baseMiddle.setTextureRect(baseTexCoords[1]);
    baseRight.setTextureRect(baseTexCoords[2]);
    
    handle.setOrigin(sliderTemplate.handleOrigin);

    scale = {
        rect.size.x / (baseTexCoords[0].size.x + baseTexCoords[1].size.x + baseTexCoords[2].size.x),
        rect.size.y / (baseTexCoords[0].size.y + baseTexCoords[1].size.y + baseTexCoords[2].size.y)
    };
    handle.setScale(scale);
    baseLeft.setScale(scale);
    baseMiddle.setScale(scale);
    baseRight.setScale(scale);

    baseMiddlePositionOffset = static_cast<sf::Vector2f>(baseTexCoords[1].position - baseTexCoords[0].position);
    baseMiddlePositionOffset = {baseMiddlePositionOffset.x * scale.x, baseMiddlePositionOffset.y * scale.y};
    baseRightPositionOffset = static_cast<sf::Vector2f>(baseTexCoords[2].position - baseTexCoords[0].position);
    baseRightPositionOffset = {baseRightPositionOffset.x * scale.x, baseRightPositionOffset.y * scale.y};

    empty = {std::round(rect.position.x + baseTexCoords[0].size.x * sliderTemplate.emptyPoint.x * scale.x), std::round(rect.position.y + baseTexCoords[0].size.y * sliderTemplate.emptyPoint.y * scale.y)};
    full = {std::round(rect.position.x + baseRightPositionOffset.x + baseTexCoords[2].size.x * sliderTemplate.fullPoint.x * scale.x), std::round(rect.position.y + baseRightPositionOffset.y + baseTexCoords[2].size.y * sliderTemplate.fullPoint.y * scale.y)};
    
    if (vertical)
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

    handle.setPosition(empty);
    baseLeft.setPosition(rect.position);
    baseMiddle.setPosition(rect.position + baseMiddlePositionOffset);
    baseRight.setPosition(rect.position + baseRightPositionOffset);

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

            if (vertical)
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