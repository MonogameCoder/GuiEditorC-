#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "sprite.h"
#include "button.h"
#include "frame.h"



int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1366, 768), "My window");
    //window.setFramerateLimit(120);
    sf::Clock clock;
    
    Button bt1;
    Button bt2;
    Button bt3;
    Frame frame;
    frame.addItem(sf::Vector2i(32, 32), bt1);
    frame.addItem(sf::Vector2i(128, 128), bt2);
    sf::Vector2i lastMousePos = sf::Mouse::getPosition(window);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        auto pos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pos);
        auto selected = (Button*)bt3.hitTest(worldPos);

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
                    bt3.setClicked(true);
                }
            }
            break;
            case sf::Event::MouseButtonReleased:
            {
                bt3.setClicked(false);
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
      
        bt3.update(time.asMilliseconds());
        frame.update(time.asMilliseconds());
        clock.restart();
      
        window.clear(sf::Color::Black);
        bt3.draw(window);
        frame.draw(window);
        window.display();
    }

    return 0;
}