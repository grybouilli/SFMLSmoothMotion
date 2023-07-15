#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

class SmoothMotionCalc
{
public:
    explicit SmoothMotionCalc(const float&, const float&, const float&, const sf::Vector2f&);

    void setResponseSpeed(const float&);
    void setDampingCoef(const float&);
    void setInitialResponse(const float&);

    sf::Vector2f getNextPosition(sf::Time, const sf::Vector2f&, const sf::Vector2f&);
private:
    void recomputeCoefs();

    float _T_crit;
    float _f, _zeta, _r;
    float _k1, _k2, _k3;

    sf::Vector2f _outPosition;
    sf::Vector2f _outVelocity;
};