#include "Dummy.hpp"

Dummy::Dummy(float radius, sf::Color fillColor)
: _shape {radius}
, _target { nullptr }
, _motionComputer {nullptr}
{
    _shape.setFillColor(fillColor);
    centerOrigin(radius);
}

void Dummy::updateCurrent(sf::Time dt)
{
    if(_target && _motionComputer)
    {
        //trajectory engine computes position
        auto nextPosition = _motionComputer->getNextPosition(dt,_target->getPreviousPosition(), _target->getPosition());
        setPosition(nextPosition);
    }
}

void Dummy::follow(const Tracker& tr, SmoothMotionCalc& motCal)
{
    _target = &tr;
    _motionComputer = &motCal;
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