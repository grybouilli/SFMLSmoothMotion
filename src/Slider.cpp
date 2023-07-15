#include "Slider.hpp"

Slider::Slider(const float& min, const float& max, const float& w, const float& h, const sf::Color& fillColor)
    : _backend{ min, max }
    , _frontend{ w, h, fillColor }
{
}


void Slider::handleMouse(const sf::Vector2i& mouse /* position relative to window*/)
{
    _frontend.slide((float)mouse.x, getTransform());
    Range frontRange = _frontend.getRange();

    _backend.setTo(frontRange.value, frontRange.min, frontRange.max);
}

float Slider::getValue() const
{
    return _backend.getValue();
}


sf::FloatRect Slider::getBounds() const
{
    return getTransform().transformRect((_frontend.getBounds()));
}
void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_frontend, states);
}