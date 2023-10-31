#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <list>

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

    std::list<Object*> uiList;
    Object* selected = {};

    Button bt1;
    Button bt2;
    Label lb1("Hello World!", "assets/Arial.ttf");
    lb1.setFontSize(22);
    lb1.setFillColor(sf::Color::Yellow);
    lb1.setStyle(sf::Text::Italic);

    Frame frame;
    frame.addItem(sf::Vector2i(32, 32), &bt1);
    frame.addItem(sf::Vector2i(128, 128), &bt2);
    frame.addItem(sf::Vector2i(256, 256), &lb1);

    Button bt3;
    Button bt4;
    Button bt5;
    Button bt6;
    Button bt7;
    bt7 = bt6;
    Label lb2{ "Hello World!", "assets/Arial.ttf" };

    Grid grid;
    sf::Vector2f gridPos = sf::Vector2f(frame.getPosition().x + frame.width(), frame.getPosition().y);
    grid.setPosition(gridPos);
    //grid.addItem(sf::Vector2i(0,0), &bt3);
    //grid.addItem(sf::Vector2i(128,0), &bt4);
    //grid.addItem(sf::Vector2i(0,128), &bt5);
    //grid.addItem(sf::Vector2i(128,128), &bt6);
    //grid.addItem(sf::Vector2i(128, 256), &bt7);
    //grid.addItem(sf::Vector2i(256, 256), &lb2);
    Button testBtn;
    uiList.push_back(&frame);
    uiList.push_back(&grid);

    sf::Vector2i lastMousePos = sf::Mouse::getPosition(window);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        auto pos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pos);
    
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            for (auto& item : uiList)
            {
                selected = item->hitTest(worldPos);
                if (selected != nullptr)
                {
                    break;
                }
            }
        }
      
       
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
                        //frame.removeItem(lb1);
                    }                    
                }
                if (selected != nullptr && grid.contains(*selected))
                {
                    grid.removeItem(*selected);                 
                   
                }
            }
            break;
            case sf::Event::MouseButtonReleased:
            {
                pos = sf::Mouse::getPosition(window);
                worldPos = window.mapPixelToCoords(pos);
                auto position = sf::Vector2i(worldPos) - grid.getPosition();
                static int index = 0;
                if (selected != nullptr)
                {
                    if (typeid(*selected) == typeid(Button))
                    {
                        Button* btn = static_cast<Button*>(selected);
                        btn->setClicked(false);
                    }
                    if (selected != nullptr && grid.contains(*selected))
                    {
                       
                        grid.removeSlot(selected);      
                        grid.addItem(position, selected);                     
                    }
                    else if (selected != nullptr && frame.contains(*selected) && grid.contains((sf::Vector2f)selected->getPosition()))
                    {
                        if (typeid(*selected) == typeid(Button))
                        {
                            
                            selected = new Button(*static_cast<Button*>(selected));
                            Button* btn = (Button*)selected;
                            btn->setText("Button" + std::to_string(index++));
                           
                        }
                        else if (typeid(*selected) == typeid(Sprite))
                        {
                            selected = new Sprite(*static_cast<Sprite*>(selected));
                        }
                        else if (typeid(*selected) == typeid(Label))
                        {                           
                            selected = new Label(*static_cast<Label*>(selected));
                        }
                        grid.addItem(position, selected);
                    }
                }
              
            }
            break;
            }
        }
       
        sf::Time time = clock.getElapsedTime();
      
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            pos = sf::Mouse::getPosition(window);
           
            if (selected != nullptr)
            {

                if (typeid(*selected) == typeid(Button))
                {
                    static_cast<Button*>(selected)->moveObject(sf::Vector2f(pos - lastMousePos));
                }
                else if (typeid(*selected) == typeid(Sprite))
                {
                    static_cast<Sprite*>(selected)->moveObject(sf::Vector2f(pos - lastMousePos));
                }
                else if (typeid(*selected) == typeid(Label))
                {
                    static_cast<Label*>(selected)->moveObject(sf::Vector2f(pos - lastMousePos));
                }

            }
        }
       
       
      

        lastMousePos = sf::Mouse::getPosition(window);
      
        frame.update(time.asMilliseconds());
        grid.update(time.asMilliseconds());
        clock.restart();
      
        window.clear(sf::Color::Black);
        grid.draw(window);
        frame.draw(window);
      
        window.display();
      
    }
   
    return 0;
}