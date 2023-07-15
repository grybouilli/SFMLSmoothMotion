#include "SliderFront.hpp"
#include "FontLoader.hpp"

#include <sstream>
#include <iomanip>

SliderFront::SliderFront(const float& width, const float& height, const std::string& label, const sf::Color& fillColor)
    : _left{ sf::Vector2f(width / 2.f, height) }
    , _right{ sf::Vector2f(width, height) }
    , _cursor{ height / 2.f + .1f }
    , _label{ label }
    , _indicator{ label, FontLoader::font, 14 }
{
    _left.setFillColor(fillColor);
    _right.setFillColor(sf::Color(155, 155, 155));
    _cursor.setFillColor(fillColor);

    _cursor.setOrigin(height / 2.f, height / 2.f);
    _cursor.setPosition(width / 2.f, height / 2.f);
    _cursor.setOutlineColor(sf::Color::Black);
    _cursor.setOutlineThickness(2.f);

    _indicator.setPosition((width - _indicator.getCharacterSize()) / 2.f, height + 4.f);
    _indicator.setFillColor(sf::Color::Black);
}

void SliderFront::slide(const float& targetx, const sf::Transform& tr)
{
    auto transformedCursorPos = tr.transformPoint(_cursor.getPosition());
    auto diff = targetx - transformedCursorPos.x;

    _cursor.move(diff, 0);
    auto currentSize = _left.getSize();
    _left.setSize(sf::Vector2f(currentSize.x + diff, currentSize.y));
}

Range SliderFront::getRange() const
{
    return Range{ .min = 0, .max = _right.getLocalBounds().width, .value = _cursor.getPosition().x };
}

void SliderFront::setIndicator(const float& val)
{
    std::ostringstream str;
    str << _label << std::setprecision(4) << val;
    _indicator.setString(str.str());
}

sf::FloatRect SliderFront::getBounds() const
{
    return getTransform().transformRect(_right.getLocalBounds());
}

void SliderFront::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(_right, states);
    target.draw(_left, states);
    target.draw(_cursor, states);
    target.draw(_indicator, states);
}