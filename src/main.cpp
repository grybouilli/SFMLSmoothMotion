#include <SFML/Graphics.hpp>
#include "Dummy.hpp"
#include "Tracker.hpp"

int main()
{
    sf::RenderWindow mainWindow(sf::VideoMode(1000,1000), "Smooth Motion Project");

    Dummy dum { 400, 400 };
    MouseTracker mouse {mainWindow};
    dum.follow(mouse);
    while(mainWindow.isOpen())
    {
        sf::Event event;
        while(mainWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                mainWindow.close();
        }

        dum.update(sf::Time::Zero);
        mainWindow.clear(sf::Color::White);
        mainWindow.draw(dum);
        mainWindow.display();
    }

    return 0;
}