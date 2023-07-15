#include "SmoothMotionCalc.hpp"
#include <cmath>
#include <stdexcept>

SmoothMotionCalc::SmoothMotionCalc(
    const float& responseSpeed, // f
    const float& dampingCoef,   // zeta
    const float& initialResp,    // r
    const sf::Vector2f& initPos
)
: _f{responseSpeed}
, _zeta {dampingCoef}
, _r {initialResp}
, _k1 {}
, _k2 {}
, _k3 {}
, _outPosition {initPos}
, _outVelocity {0,0}
{
    setResponseSpeed(responseSpeed);
    setDampingCoef(dampingCoef);
    setInitialResponse(initialResp);
}

void SmoothMotionCalc::setResponseSpeed(const float& f)
{
    if(f < 0.00001f)
    {
        throw std::runtime_error("SmoothMotionCalc::setResponseSpeed : f can't be zero.");
    }
    _f = f;
    _k2 = 1/(4*M_PI*M_PI*_f*_f);
    
    recomputeCoefs();
}

void SmoothMotionCalc::setDampingCoef(const float& zeta)
{
    _zeta = zeta;
    recomputeCoefs();
}

void SmoothMotionCalc::setInitialResponse(const float& r)
{
    _r = r;
    recomputeCoefs();
}

sf::Vector2f SmoothMotionCalc::getNextPosition(sf::Time dt, const sf::Vector2f& inPrevPos, const sf::Vector2f& inCurrentPos)
{
    float T= dt.asSeconds();
    
    sf::Vector2f inVel = (inCurrentPos - inPrevPos) / T;
    int iterations = (int)std::ceil(T / _T_crit);
    T /= iterations;

    for (int i = 0; i < iterations; i++) {
        _outPosition = _outPosition + T * _outVelocity;
        _outVelocity = _outVelocity + T * (inCurrentPos + _k3 * inVel - _outPosition - _k1*_outVelocity) / _k2;
    }
    return _outPosition;
}


void SmoothMotionCalc::recomputeCoefs()
{
    _k1 = _zeta/(M_PI*_f);
    _k3 = _r * _zeta / (2 * M_PI * _f);
    _T_crit = 0.8f * (std::sqrt(4 * _k2 + _k1 * _k1) - _k1);
}