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

struct BackgroundTemplate
{
    int texCoordSize;
    sf::Vector2i texCoordOffset;

    sf::IntRect horizontalBarTexCoords;
    sf::IntRect VerticalBarTexCoords;
    sf::Vector2i horizontalBarLOrigin;
    sf::Vector2i horizontalBarROrigin;
    sf::Vector2i verticalBarTOrigin;
    sf::Vector2i verticalBarBOrigin;
    sf::Vector2i horizontalBar1LMargin;
    sf::Vector2i horizontalBar2LMargin;
    sf::Vector2i horizontalBar1RMargin;
    sf::Vector2i horizontalBar2RMargin;
    sf::Vector2i verticalBar1TMargin;
    sf::Vector2i verticalBar2TMargin;
    sf::Vector2i verticalBar1BMargin;
    sf::Vector2i verticalBar2BMargin;
};

struct DefaultTexCoords
{
    //////////////// BACKGROUNDS ////////////////

    int bgTexCoordSize = 32;
    sf::Vector2i bgTexCoordOffset = {0, 0};
    sf::IntRect bgHorizontalBarTexCoords = sf::IntRect({0, 144}, {66, 13});
    sf::IntRect bgVerticalBarTexCoords = sf::IntRect({80, 144}, {13, 66});
    
    BackgroundTemplate bg = {
        bgTexCoordSize,
        bgTexCoordOffset,
        bgHorizontalBarTexCoords,
        bgVerticalBarTexCoords,
        {62, 0},
        {1, 0},
        {0, 62},
        {0, 1},
        {0, 10},
        {0, 24},
        {-4, 10},
        {-4, 24},
        {9, 0},
        {24, 0},
        {10, -4},
        {24, -4}
    };

    int bgSmallTexCoordSize = 16;
    sf::Vector2i bgSmallTexCoordOffset = {0, 96};
    sf::IntRect bgSmallHorizontalBarTexCoords = sf::IntRect({0, 160}, {39, 8});
    sf::IntRect bgSmallVerticalBarTexCoords = sf::IntRect({64, 160}, {8, 39});

    BackgroundTemplate bgSmall = {
        bgSmallTexCoordSize,
        bgSmallTexCoordOffset,
        bgSmallHorizontalBarTexCoords,
        bgSmallVerticalBarTexCoords,
        {36, 0},
        {1, 0},
        {0, 36},
        {0, 1},
        {0, 5},
        {0, 13},
        {-2, 7},
        {-2, 13},
        {5, 0},
        {13, 0},
        {5, -2},
        {13, -2}
    };

    int bgTextTexCoordSize = 5;
    sf::Vector2i bgTextTexCoordOffset = {48, 96};

    BackgroundTemplate bgText = {
        bgTextTexCoordSize,
        bgTextTexCoordOffset,
        {{0, 0}, {0, 0}},
        {{0, 0}, {0, 0}},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0}
    };

    /////////////////////////////////////////////

    ////////////////// BUTTONS //////////////////

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

    /////////////////////////////////////////////

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
    
    /////////////////// DIALS ///////////////////

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

    /////////////////////////////////////////////
};

static DefaultTexCoords defaultTexCoords;