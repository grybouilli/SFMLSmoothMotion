#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow mainWindow(sf::VideoMode(1000,1000), "Smooth Motion Project");

    while(mainWindow.isOpen())
    {
        sf::Event event;
        while(mainWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                mainWindow.close();
        }

        mainWindow.clear(sf::Color::White);
        // draw some stuff
        mainWindow.display();
    }

    return 0;
}