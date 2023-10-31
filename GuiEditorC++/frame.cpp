#include "frame.h"

Frame::Frame()
	:mMode(Mode::STATIC)
{
	pFrameBG = std::make_shared<Sprite>("assets/UItoolboxTX.png");
}

Frame::~Frame()
{
}

void Frame::addItem(vec2i position, Object* item)
{
	mSlots.emplace_back(new Slot(position, item));
}

void Frame::removeItem(Object& item)
{
	for (unsigned int i = 0; i < mSlots.size(); i++)
	{
		if (*mSlots[i] == item)
		{
			mSlots.erase(mSlots.begin() + i);
			break;
		}

	}
}

bool Frame::contains(Object& item)
{
	for (const auto& obj : mSlots)
	{
		if (*obj->pItem == item)
		{
			return true;
		}
	}
	return false;
}



 Object* Frame::hitTest(const vec2f mousePosition)
{
	for (unsigned int i = 0; i < mSlots.size(); i++)
	{
		const Container::Slot* slot = mSlots[i];
		
		if (slot->pItem  != nullptr && slot->pItem->mActive)
		{
			
			if (slot->pItem->contains(mousePosition))
			{
				return slot->pItem;				
			}
		}
	}

	return NULL;
}

bool Frame::contains(const vec2f& position)
{
	return false;
}

void Frame::update(sf::Int32 dt)
{
	for (int i = 0; i < mSlots.size(); i++)
	{
		Container::Slot* slot = mSlots[i];

		if (slot->pItem != nullptr)
		{
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				vec2i pos = pFrameBG->getPosition();
				slot->pItem->setPosition(vec2f(pos + slot->mPosition));

				if (mMode == Mode::DYNAMIC)
				{
					slot->mPosition = slot->pItem->getPosition();
				}
			}
			slot->pItem->update(dt);
		}
	}
}

void Frame::draw(sf::RenderWindow& window)
{
	pFrameBG->draw(window);
	for (int i = 0; i < mSlots.size(); i++)
	{
		const Container::Slot* slot = mSlots[i];

		if (slot->pItem != nullptr)
		{

			slot->pItem->draw(window);

		}
	}
}

std::vector<Container::Slot*> Frame::getSlots()
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

void Frame::setPosition(vec2f position)
{
	pFrameBG->setPosition(position);
}

void Frame::moveObject(vec2f amount)
{
	for (int i = 0; i < mSlots.size(); i++)
	{
		const Container::Slot* slot = mSlots[i];

		if (slot->pItem != nullptr)
		{
			vec2i pos = pFrameBG->getPosition();
			slot->pItem->setPosition(vec2f(amount));


		}
	}
}
