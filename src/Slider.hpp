#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include "SliderBack.hpp"
#include "SliderFront.hpp"


class Slider : public sf::Drawable, public sf::Transformable
{
public:
    explicit Slider(const float&, const float&, const float&, const float&, const std::string & = "", const sf::Color & = SL_DEFCOLOR);

    void handleMouse(const sf::Vector2i&);
    float getValue() const;

    sf::FloatRect getBounds() const;

private:
    void backFrontConnexion();
    void draw(sf::RenderTarget&, sf::RenderStates) const;

    SliderBack  _backend;
    SliderFront _frontend;
};
