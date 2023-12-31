#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>

class Tracker : public sf::Transformable
{
public:
    virtual ~Tracker()
    {}

    virtual sf::Vector2f getPosition() const
    {
        return sf::Transformable::getPosition();
    }

    void update(sf::Time dt)
    {
        updateCurrent(dt);
        _previousPosition = getPosition();
    }

    sf::Vector2f getPreviousPosition() const { return _previousPosition; }
protected:
    virtual void updateCurrent(sf::Time dt)
    {

    }

private:
    sf::Vector2f _previousPosition;
};

class MouseTracker : public Tracker
{
public:
    explicit MouseTracker(const sf::RenderWindow& win)
        : _window{ &win }
    {

    }

    virtual ~MouseTracker()
    {
        _window = nullptr;
    }

    sf::Vector2f getPosition() const
    {
        auto position = sf::Mouse::getPosition(*_window);
        return sf::Vector2f(position.x, position.y);
    }

private:
    sf::RenderWindow const* _window;
};