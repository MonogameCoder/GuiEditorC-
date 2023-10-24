#pragma once
#ifndef  CONTAINER
#define CONTAINER
#include <vector>
#include <list>
#include "object.h"
#include "sprite.h"
#include "button.h"
#include "label.h"

class Container : public Object
{
public:
    
    class Slot
    {
    public:

        Slot(sf::Vector2i position, Object* item) 
        {
         

            mPosition = position;
            mIndex = mGlobalIndex++;
            item->setIndex(mIndex);
            if (typeid(*item) == typeid(Button))
            {
                pItem = new Button(*static_cast<Button*>(item));
                //pItem = reinterpret_cast<Button*>(item);
            }
            else if (typeid(*item) == typeid(Sprite))
            {
                pItem = new Sprite(*static_cast<Sprite*>(item));
               // pItem = static_cast<Sprite*>(item);
            }
            else if (typeid(*item) == typeid(Label))
            {
                pItem = new Label;
                //pItem = static_cast<Label*>(item);
            }        
           
        } 
        ~Slot()
        {
            if (pItem != nullptr)
            {
                delete pItem;
            }
           
            pItem = nullptr;
        }
        bool operator==(const Object& rhs) const
        {
            return pItem == &rhs;
        }
    public:
        sf::Vector2i mPosition;
        Object* pItem;
    public:
        unsigned int mIndex;
        static unsigned int mGlobalIndex ;
   
    };
   

public:
    virtual void addItem(sf::Vector2i position, Object* item) = 0;
    virtual void removeItem(Object& item) = 0;
    virtual bool contains(Object& item) = 0;
 

    virtual void update(sf::Int32 dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual std::vector<Slot> getSlots() = 0;

protected:
    std::vector<Slot> mSlots;
    std::list<Slot> mChildren;
    std::shared_ptr<Sprite> pFrameBG;

};

#endif // ! CONTAINER