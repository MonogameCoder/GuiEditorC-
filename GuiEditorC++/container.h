#pragma once
#ifndef  CONTAINER
#define CONTAINER
#include <vector>
#include <list>
#include "object.h"
#include "sprite.h"

class Container : public Object
{
public:
    
    class Slot
    {
    public:

        Slot(sf::Vector2i position, Object& item) 
        {
            pItem.reset(dynamic_cast<Sprite*>(&item));
            mPosition = position;
            mIndex = mGlobalIndex++;
            pItem->setIndex(mIndex);
        }       
        bool operator==(const Object& rhs) const
        {
            return *pItem == rhs;
        }
    public:
        sf::Vector2i mPosition;
        std::shared_ptr<Object> pItem;
    public:
        long long mIndex;
        static long long mGlobalIndex ;
   
    };
   

public:
    virtual void addItem(sf::Vector2i position, Object& item) = 0;
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