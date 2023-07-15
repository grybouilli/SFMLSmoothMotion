#include <SFML/Graphics.hpp>
#include "Dummy.hpp"
#include "Tracker.hpp"
#include "SmoothMotionCalc.hpp"
#include "Slider.hpp"

#define TIME_PER_FRAME 1/60.f
#define SF_TIME_PER_FRAME sf::seconds(TIME_PER_FRAME)
int main()
{
    sf::RenderWindow mainWindow(sf::VideoMode(1000, 1000), "Smooth Motion Project");

    Dummy dum{};
    MouseTracker mouse{ mainWindow };
    SmoothMotionCalc calculator{ 6.f, .5f, 2.f, mouse.getPosition() };

    Slider slider1 { 0.f, 1.f, 300.f, 20.f };
    slider1.setPosition(10.f, 10.f);

    dum.follow(mouse, calculator);

    sf::Clock clock;
    sf::Time elapsed { sf::Time::Zero };

    bool mousePressed = false;
    while (mainWindow.isOpen())
    {
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mainWindow.close();

            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                mainWindow.setView(sf::View(visibleArea));
            }

            if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
            {
                mousePressed = !mousePressed;
            }
        }

        if(mousePressed)
        {
            auto mousePos = sf::Mouse::getPosition(mainWindow);
            if(slider1.getBounds().contains(mousePos.x, mousePos.y))
                slider1.handleMouse(mousePos);
        }
        elapsed += clock.restart();
        if(elapsed.asSeconds() > TIME_PER_FRAME)
        {
            dum.update(SF_TIME_PER_FRAME);
            mouse.update(SF_TIME_PER_FRAME);
            elapsed = sf::Time::Zero;
        }
        mainWindow.clear(sf::Color::White);
        mainWindow.draw(dum);
        mainWindow.draw(slider1);
        mainWindow.display();
    }

    return 0;
}