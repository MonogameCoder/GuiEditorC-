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

        Slot(vec2i position, Object* item) 
            :
            pItem(nullptr),
            mIndex(0)
        {
            mPosition = position;
           
            if (item != nullptr)
            {
                mIndex = mGlobalIndex++;
                item->setIndex(mIndex);
            }
            
            pItem = item;
           
        } 
        ~Slot()
        {
            delete pItem;
            pItem = nullptr;
        }
        bool operator==(const Object& rhs) const
        {
            return pItem == &rhs;
        }
    public:
        vec2i mPosition;
        Object* pItem;
    public:
        unsigned int mIndex;
        static unsigned int mGlobalIndex ;
   
    };
   

public:
    virtual void addItem(vec2i position, Object* item) = 0;
    virtual void removeItem(Object& item) = 0;
    virtual bool contains(Object& item) = 0;
 

    virtual void update(sf::Int32 dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual std::vector<Slot*> getSlots() = 0;

protected:
    std::vector<Slot*> mSlots;
    std::shared_ptr<Sprite> pFrameBG;

};

#endif // ! CONTAINER