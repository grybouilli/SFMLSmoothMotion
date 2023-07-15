#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "SliderBack.hpp"

#define SL_DEFCOLOR sf::Color::Blue

class SliderFront : public sf::Drawable, public sf::Transformable
{
public: 
    explicit SliderFront(const float&,const float&, const sf::Color& = SL_DEFCOLOR);

    void slide(const float&, const sf::Transform&);
    Range getRange() const;

    sf::FloatRect getBounds() const;


private:
    void draw(sf::RenderTarget&, sf::RenderStates) const;

    sf::RectangleShape  _left;
    sf::RectangleShape  _right;
    sf::CircleShape     _cursor;

};