#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "sprite.h"
#include "button.h"
#include "label.h"
#include "frame.h"
#include "grid.h"


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1366, 768), "My window");
    //window.setFramerateLimit(120);
    sf::Clock clock;
    
    Button bt1;
    Button bt2;
    Label lb1("Hello World!", "assets/Arial.ttf");
    lb1.setFontSize(22);
    lb1.setFillColor(sf::Color::Yellow);
    lb1.setStyle(sf::Text::Italic);
  
    Frame frame;
    frame.addItem(sf::Vector2i(32, 32),&bt1);
    frame.addItem(sf::Vector2i(128, 128), &bt2);
    frame.addItem(sf::Vector2i(256, 256), &lb1);

    Button bt3;
    Button bt4;
    Button bt5;
    Button bt6;

    Grid grid;
    sf::Vector2f gridPos = sf::Vector2f(frame.getPosition().x + frame.width(), frame.getPosition().y);
    grid.setPosition(gridPos);
    grid.addItem(sf::Vector2i(0,0), &bt3);
    grid.addItem(sf::Vector2i(128,0), &bt4);
    grid.addItem(sf::Vector2i(0,128), &bt5);
    grid.addItem(sf::Vector2i(128,128), &bt6);


    sf::Vector2i lastMousePos = sf::Mouse::getPosition(window);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        auto pos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pos);
        auto selected = frame.hitTest(worldPos);

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
                    if (typeid(*selected) == typeid(Button))
                    {
                        Button* btn = static_cast<Button*>(selected);
                        btn->setClicked(true);
                        frame.removeItem(lb1);
                    }                    
                }
            }
            break;
            case sf::Event::MouseButtonReleased:
            {
                if (selected != NULL)
                {
                    if (typeid(*selected) == typeid(Button))
                    {
                        Button* btn = static_cast<Button*>(selected);
                        btn->setClicked(false);
                    }
                }
              
            }
            break;
            }
        }
       
        sf::Time time = clock.getElapsedTime();
      
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i currMousePos = sf::Mouse::getPosition(window);
            if (selected != NULL)
            {

                if (typeid(*selected) == typeid(Button))
                {
                    static_cast<Button*>(selected)->moveObject(sf::Vector2f(currMousePos - lastMousePos));
                }
                else if (typeid(*selected) == typeid(Sprite))
                {
                    static_cast<Sprite*>(selected)->moveObject(sf::Vector2f(currMousePos - lastMousePos));
                }
                else if (typeid(*selected) == typeid(Label))
                {
                    static_cast<Label*>(selected)->moveObject(sf::Vector2f(currMousePos - lastMousePos));
                }

            }
        }
       
       
      

        lastMousePos = sf::Mouse::getPosition(window);
      
        frame.update(time.asMilliseconds());
        grid.update(time.asMilliseconds());
        clock.restart();
      
        window.clear(sf::Color::Black);
       
        frame.draw(window);
        grid.draw(window);
        //bt3.draw(window);
        window.display();
      
    }

    return 0;
}