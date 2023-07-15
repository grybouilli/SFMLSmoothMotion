#pragma once

#include <SFML/Graphics/Font.hpp>

struct FontLoader
{
    static sf::Font font;
    static void loadFont();
};
