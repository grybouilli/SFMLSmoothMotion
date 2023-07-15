#pragma once

struct Range
{
    const float min;
    const float max;
    float value;
};

class SliderBack
{
public:
    explicit SliderBack(const float&, const float&);

    float getValue() const;
    void setTo(const float&, const float&, const float&);

private:
    Range _range;
};