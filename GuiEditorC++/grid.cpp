#include "grid.h"
#include <string>

Grid::Grid()
{
	pFrameBG = std::make_shared<Sprite>("assets/FrameEditorTX.png");
	mItems.setRectangle(pFrameBG->getPosition().x, pFrameBG->getPosition().y, pFrameBG->width(), pFrameBG->height());
}

Grid::~Grid()
{
}

void Grid::insert(Container::Slot* item)
{
	mItems.Insert(item);
}

void Grid::addItem(sf::Vector2i position, Object* item)
{
	auto slot = new Slot(position, item);
	mSlots.emplace_back(slot);
	insert(slot);

}

void Grid::removeItem(Object& item)
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

bool Grid::contains(Object& item)
{
	return false;
}



Object* Grid::hitTest(const sf::Vector2f mousePosition)
{
	for (unsigned int i = 0; i < mSlots.size(); i++)
	{
		Container::Slot* slot = mSlots[i];


		if (slot->pItem != nullptr && slot->pItem->mActive)
		{
			if (slot->pItem->contains(mousePosition))
			{
				return slot->pItem;
			}
		}
	}

	return NULL;
}

bool Grid::contains(const sf::Vector2f& position)
{
	return false;
}

void Grid::update(sf::Int32 dt)
{
	mItems.UpdateLayout();
	for (int i = 0; i < mSlots.size(); i++)
	{
		Container::Slot* slot = mSlots[i];

		if (slot->pItem != nullptr)
		{

			sf::Vector2i pos = pFrameBG->getPosition();
			slot->pItem->setPosition(sf::Vector2f(pos + slot->mPosition));
			slot->pItem->update(dt);
		}
	}
}

void Grid::draw(sf::RenderWindow& window)
{
	pFrameBG->draw(window);
	for (int i = 0; i < mSlots.size(); i++)
	{
		Container::Slot* slot = mSlots[i];

		if (slot->pItem != nullptr)
		{

			slot->pItem->draw(window);

		}
	}
}

std::vector<Container::Slot*> Grid::getSlots()
{
	return mSlots;
}

float Grid::width()
{
	return pFrameBG->getSprite()->getGlobalBounds().width;
}

float Grid::height()
{
	return pFrameBG->getSprite()->getGlobalBounds().height;
}

void Grid::setPosition(sf::Vector2f position)
{
	pFrameBG->setPosition(position);
}

void Grid::moveObject(sf::Vector2f amount)
{
	for (int i = 0; i < mSlots.size(); i++)
	{
		Container::Slot* slot = mSlots[i];

		if (slot->pItem != nullptr)
		{
			sf::Vector2i pos = pFrameBG->getPosition();
			slot->pItem->setPosition(sf::Vector2f(amount));


		}
	}
}