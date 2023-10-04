#include <SFML/Graphics.hpp>
#include <iostream>
#include "sprite.h"
#include "button.h"
#include <SFML/System/Clock.hpp>


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1366, 768), "My window");
    //window.setFramerateLimit(120);
    sf::Clock clock;
    
    Button sprite;
    sf::Vector2i lastMousePos = sf::Mouse::getPosition(window);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        auto pos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pos);
        auto selected = (Button*)sprite.hitTest(worldPos);

        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
            {
                if (event.key.code == sf::Mouse::Left && selected != NULL)
                {
                    sprite.setClicked(true);
                }
            }
            break;
            case sf::Event::MouseButtonReleased:
            {
                sprite.setClicked(false);
            }
            break;
            }
        }
    
      
      
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
          
            if (selected != NULL)
            {
                sf::Vector2i currMousePos = sf::Mouse::getPosition(window);

                selected->moveObject(sf::Vector2f(currMousePos - lastMousePos));

            }
        }
       
       
        lastMousePos = sf::Mouse::getPosition(window);

        sf::Time time = clock.getElapsedTime();
        //std::cout << time.asMilliseconds() << std::endl;
        sprite.update(time.asMilliseconds());
        clock.restart();
      

     
        sprite.draw(window);
    }

    return 0;
}