#include "Slider.hpp"

Slider::Slider(const float& min, const float& max, const float& w, const float& h, const std::string& label, const sf::Color& fillColor)
    : _backend{ min, max }
    , _frontend{ w, h, label, fillColor }
{
    backFrontConnexion();
}


void Slider::handleMouse(const sf::Vector2i& mouse /* position relative to window*/)
{
    _frontend.slide((float)mouse.x, getTransform());

    backFrontConnexion();
}

float Slider::getValue() const
{
    return _backend.getValue();
}

sf::FloatRect Slider::getBounds() const
{
    return getTransform().transformRect((_frontend.getBounds()));
}

void Slider::backFrontConnexion()
{
    Range frontRange = _frontend.getRange();

    _backend.setTo(frontRange.value, frontRange.min, frontRange.max);

    _frontend.setIndicator(_backend.getValue());
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_frontend, states);
}