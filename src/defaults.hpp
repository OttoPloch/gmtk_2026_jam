#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

struct SliderTemplate
{
    sf::IntRect handleTexCoords;
    std::array<sf::IntRect, 3> baseTexCoords;
    sf::Vector2f handleOrigin;
    sf::Vector2f emptyPoint;
    sf::Vector2f fullPoint;
    bool vertical; // false = horizontal
};

struct DefaultTexCoords
{
    int bgTexCoordSize = 32;
    int bgSmallTexCoordSize = 16;
    int bgTextTexCoordSize = 5;
    sf::Vector2i bgTexCoordOffset = {0, 0};
    sf::Vector2i bgSmallTexCoordOffset = {0, 96};
    sf::Vector2i bgTextTexCoordOffet = {48, 96};

    std::array<sf::IntRect, 3> buttonTexCoords = {
        sf::IntRect({0, 0}, {36, 36}),
        sf::IntRect({36, 0}, {36, 36}),
        sf::IntRect({72, 0}, {36, 36})
    };
    std::array<sf::IntRect, 3> buttonSmallTexCoords = {
        sf::IntRect({0, 36}, {18, 19}),
        sf::IntRect({18, 36}, {18, 19}),
        sf::IntRect({36, 36}, {18, 19})
    };

    ////////////////// SLIDERS //////////////////
    // empty and full points for sliders are in percents

    sf::IntRect sliderHandleTexCoordsHorizontal = {{0, 0}, {14, 27}};
    std::array<sf::IntRect, 3> sliderBaseTexCoordsHorizontal = {
        sf::IntRect({16, 0}, {16, 16}),
        sf::IntRect({32, 0}, {16, 16}),
        sf::IntRect({48, 0}, {16, 16})
    };
    sf::Vector2f sliderHandleOriginHorizontal = {6, 13};
    sf::Vector2f sliderEmptyPointHorizontal = {6./16., 6./16.};
    sf::Vector2f sliderFullPointHorizontal = {8./16., 6./16.};
    
    SliderTemplate horizontalSlider = {
        sliderHandleTexCoordsHorizontal,
        sliderBaseTexCoordsHorizontal,
        sliderHandleOriginHorizontal,
        sliderEmptyPointHorizontal,
        sliderFullPointHorizontal,
        false
    };

    sf::IntRect sliderHandleTexCoordsVertical = {{64, 0}, {27, 20}};
    std::array<sf::IntRect, 3> sliderBaseTexCoordsVertical = {
        sf::IntRect({96, 0}, {16, 16}),
        sf::IntRect({96, 16}, {16, 16}),
        sf::IntRect({96, 32}, {16, 16})
    };
    sf::Vector2f sliderHandleOriginVertical = {13, 17};
    sf::Vector2f sliderEmptyPointVertical = {7./16., 6./16.};
    sf::Vector2f sliderFullPointVertical = {7./16., 6./16.};

    SliderTemplate verticalSlider = {
        sliderHandleTexCoordsVertical,
        sliderBaseTexCoordsVertical,
        sliderHandleOriginVertical,
        sliderEmptyPointVertical,
        sliderFullPointVertical,
        true
    };

    sf::IntRect sliderSmallHandleTexCoordsHorizontal = {{0, 48}, {8, 13}};
    std::array<sf::IntRect, 3> sliderSmallBaseTexCoordsHorizontal = {
        sf::IntRect({9, 48}, {8, 8}),
        sf::IntRect({17, 48}, {8, 8}),
        sf::IntRect({25, 48}, {8, 8})
    };
    sf::Vector2f sliderSmallHandleOriginHorizontal = {3, 6};
    sf::Vector2f sliderSmallEmptyPointHorizontal = {5./16., 3./16.};
    sf::Vector2f sliderSmallFullPointHorizontal = {3./16., 3./16.};
    
    SliderTemplate smallHorizontalSlider = {
        sliderSmallHandleTexCoordsHorizontal,
        sliderSmallBaseTexCoordsHorizontal,
        sliderSmallHandleOriginHorizontal,
        sliderSmallEmptyPointHorizontal,
        sliderSmallFullPointHorizontal,
        false
    };

    sf::IntRect sliderSmallHandleTexCoordsVertical = {{33, 48}, {15, 10}};
    std::array<sf::IntRect, 3> sliderSmallBaseTexCoordsVertical = {
        sf::IntRect({49, 48}, {7, 8}),
        sf::IntRect({49, 56}, {7, 8}),
        sf::IntRect({49, 64}, {7, 8})
    };
    sf::Vector2f sliderSmallHandleOriginVertical = {6, 7};
    sf::Vector2f sliderSmallEmptyPointVertical = {4./16., 7./16.};
    sf::Vector2f sliderSmallFullPointVertical = {4./16., 0./16.};

    SliderTemplate smallVerticalSlider = {
        sliderSmallHandleTexCoordsVertical,
        sliderSmallBaseTexCoordsVertical,
        sliderSmallHandleOriginVertical,
        sliderSmallEmptyPointVertical,
        sliderSmallFullPointVertical,
        true
    };

    /////////////////////////////////////////////

    std::vector<sf::IntRect> dialTexCoords = {
        sf::IntRect({0, 0}, {32, 37}),
        sf::IntRect({32, 0}, {32, 37}),
        sf::IntRect({64, 0}, {32, 37}),
        sf::IntRect({96, 0}, {32, 37}),
        sf::IntRect({0, 37}, {32, 37}),
        sf::IntRect({32, 37}, {32, 37}),
        sf::IntRect({64, 37}, {32, 37}),
        sf::IntRect({96, 37}, {32, 37}),
        sf::IntRect({0, 74}, {32, 37}),
        sf::IntRect({32, 74}, {32, 37}),
        sf::IntRect({64, 74}, {32, 37}),
        sf::IntRect({96, 74}, {32, 37}),
        sf::IntRect({0, 111}, {32, 37}),
        sf::IntRect({32, 111}, {32, 37}),
        sf::IntRect({64, 111}, {32, 37}),
        sf::IntRect({96, 111}, {32, 37})
    };
    std::vector<sf::IntRect> dialSmallTexCoords = {
        sf::IntRect({0, 148}, {16, 18}),
        sf::IntRect({16, 148}, {16, 18}),
        sf::IntRect({32, 148}, {16, 18}),
        sf::IntRect({48, 148}, {16, 18}),
        sf::IntRect({0, 166}, {16, 18}),
        sf::IntRect({16, 166}, {16, 18}),
        sf::IntRect({32, 166}, {16, 18}),
        sf::IntRect({48, 166}, {16, 18}),
        sf::IntRect({0, 184}, {16, 18}),
        sf::IntRect({16, 184}, {16, 18}),
        sf::IntRect({32, 184}, {16, 18}),
        sf::IntRect({48, 184}, {16, 18}),
        sf::IntRect({0, 202}, {16, 18}),
        sf::IntRect({16, 202}, {16, 18}),
        sf::IntRect({32, 202}, {16, 18}),
        sf::IntRect({48, 202}, {16, 18})
    };
};

static DefaultTexCoords defaultTexCoords;