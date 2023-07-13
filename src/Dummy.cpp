#include "Dummy.hpp"

Dummy::Dummy()
: _shape {DEFSIZE}
, _target { nullptr}
{
    _shape.setFillColor(DEFCOLOR);
    centerOrigin(DEFSIZE);
}

Dummy::Dummy(float x, float y, float radius, sf::Color fillColor)
: _shape {radius}
, _target { nullptr }
{
    _shape.setFillColor(fillColor);
    centerOrigin(radius);
    // _shape.setPosition(x,y);
}

void Dummy::update(sf::Time dt)
{
    if(_target)
    {
        setPosition(_target->getPosition());
        //trajectory engine computes position
    }
}

void Dummy::follow(const Tracker& tr)
{
    _target = &tr;
}

void Dummy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_shape, states);
}

void Dummy::centerOrigin(float radius)
{
    _shape.setOrigin(radius, radius);
}