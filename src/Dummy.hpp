#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Time.hpp>

#include "Tracker.hpp"

#define DEFSIZE 100.f
#define DEFCOLOR sf::Color::Cyan

class Dummy : public sf::Drawable, public Tracker
{
public:
    Dummy();
    Dummy(float,float, float=DEFSIZE, sf::Color = DEFCOLOR);
    virtual ~Dummy()
    {
        _target = nullptr;
    }

    void update(sf::Time);
    void follow(const Tracker&);


private:
    void draw(sf::RenderTarget&, sf::RenderStates) const;

    void centerOrigin(float radius);

    sf::CircleShape _shape;
    Tracker const * _target;

    // trajectory engine
};