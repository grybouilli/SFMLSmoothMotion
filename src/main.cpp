#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Dummy.hpp"
#include "Tracker.hpp"
#include "SmoothMotionCalc.hpp"
#include "Slider.hpp"
#include "FontLoader.hpp"

#define TIME_PER_FRAME 1/60.f
#define SF_TIME_PER_FRAME sf::seconds(TIME_PER_FRAME)

enum Params
{
    F = 0,
    ZETA,
    R,
    TOTAL
};

int main()
{
    FontLoader::loadFont();

    sf::RenderWindow mainWindow(sf::VideoMode(1000, 1000), "Smooth Motion Project");

    Dummy dum{};
    MouseTracker mouse{ mainWindow };
    SmoothMotionCalc calculator{ 6.f, .5f, 2.f, mouse.getPosition() };

    std::vector<Slider> sliders{
        Slider  { 0.001f, 10.f, 300.f, 20.f, "f : " },
        Slider  { 0.f, 5.f, 300.f, 20.f, " zeta : " },
        Slider  { -5.f, 5.f, 300.f, 20.f, " r : " }
    };

    sliders[Params::F].setPosition(10.f, 10.f);
    sliders[Params::ZETA].setPosition(320.f, 10.f);
    sliders[Params::R].setPosition(630.f, 10.f);

    dum.follow(mouse, calculator);

    sf::Clock clock;
    sf::Time elapsed{ sf::Time::Zero };

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

        if (mousePressed)
        {
            auto mousePos = sf::Mouse::getPosition(mainWindow);
            for (auto slider = 0; slider < sliders.size(); slider++)
            {
                if (sliders[slider].getBounds().contains(mousePos.x, mousePos.y))
                {
                    std::function<void(SmoothMotionCalc*, const float&)> setter;
                    switch (slider)
                    {
                    case Params::F:
                        setter = std::mem_fn(&SmoothMotionCalc::setResponseSpeed);
                        break;
                    case Params::ZETA:
                        setter = std::mem_fn(&SmoothMotionCalc::setDampingCoef);
                        // calculator.setDampingCoef(sliders[slider].getValue());
                        break;
                    case Params::R:
                        setter = std::mem_fn(&SmoothMotionCalc::setInitialResponse);
                        // calculator.setInitialResponse(sliders[slider].getValue());
                        break;
                    default:
                        break;
                    }
                    sliders[slider].handleMouse(mousePos);
                    setter(&calculator, sliders[slider].getValue());
                }
            }
        }
        elapsed += clock.restart();
        if (elapsed.asSeconds() > TIME_PER_FRAME)
        {
            dum.update(SF_TIME_PER_FRAME);
            mouse.update(SF_TIME_PER_FRAME);
            elapsed = sf::Time::Zero;
        }
        mainWindow.clear(sf::Color::White);
        mainWindow.draw(dum);
        for (auto& slider : sliders)
        {
            mainWindow.draw(slider);
        }
        mainWindow.display();
    }

    return 0;
}