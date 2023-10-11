#include "frame.h"

Frame::Frame()
{
	pFrameBG = std::make_shared<Sprite>("assets/UItoolboxTX.png");
}

Frame::~Frame()
{
}

void Frame::addItem(sf::Vector2i position, Object& item)
{
	mSlots.emplace_back(Slot(position, item));
}

void Frame::removeItem(Object& item)
{
	for (unsigned int i = 0; i < mSlots.size(); i++)
	{
		if (mSlots[i] == item)
		{
			mSlots.erase(mSlots.begin() + i);
			break;
		}

	}	
}

bool Frame::contains(Object& item)
{
	return false;
}



Object* Frame::hitTest(const sf::Vector2f mousePosition)
{
	for (unsigned int i = mSlots.size() -1; i > 0; i--)
	{
		Container::Slot slot = mSlots[i];

		
		return slot.pItem->hitTest(mousePosition);
	}
	
	return NULL;
}

bool Frame::contains(const sf::Vector2f& position)
{
	return false;
}

void Frame::update(sf::Int32 dt)
{
	for (int i = 0; i < mSlots.size(); i++)
	{
		Container::Slot slot = mSlots[i];

		if (slot.pItem.get() != nullptr)
		{
			
			slot.pItem->setPosition(sf::Vector2f(pFrameBG->getPosition() + slot.mPosition));			

		}
	}
}

void Frame::draw(sf::RenderWindow& window)
{
	pFrameBG->draw(window);
	for (int i = 0; i < mSlots.size(); i++)
	{
		Container::Slot slot = mSlots[i];

		if (slot.pItem.get() != nullptr)
		{
			
			slot.pItem->draw(window);

		}
	}
}

std::vector<Container::Slot> Frame::getSlots()
{
	return mSlots;
}

float Frame::width()
{
	return pFrameBG->getSprite()->getGlobalBounds().width;
}

float Frame::height()
{
	return pFrameBG->getSprite()->getGlobalBounds().height;
}

void Frame::setPosition(sf::Vector2f position)
{
	pFrameBG->setPosition(position);
}