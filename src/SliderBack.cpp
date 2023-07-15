#include "SliderBack.hpp"

SliderBack::SliderBack(const float& min, const float& max)
    : _range{ .min = min, .max = max, .value = min }
{

}

float SliderBack::getValue() const
{
    return _range.value;
}

void SliderBack::setTo(const float& v, const float& m, const float& M)
{
    _range.value =(v-m) * (_range.max - _range.min) / (M-m) + _range.min;
}