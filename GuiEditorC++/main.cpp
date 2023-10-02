#include <SFML/Graphics.hpp>
#include <iostream>
#include "sprite.h"


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1366, 768), "My window");
    
    Sprite sprite ("assets/ninja.jpg");
    //Sprite sprite2 = std::move(sprite);
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }              
       
        // draw everything here...

        sprite.draw(window);       

    }

    return 0;
}