#include "FontLoader.hpp"

sf::Font FontLoader::font;


void FontLoader::loadFont()
{
    if (!font.loadFromFile("assets/roboto.ttf"))
    {
        throw std::runtime_error("FontLoader::loadFont : could not load assets/digitalo.ttf.");
    }
}