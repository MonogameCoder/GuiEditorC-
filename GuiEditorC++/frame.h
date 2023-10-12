#pragma once
#ifndef FRAME
#define FRAME
#include "container.h"
#include<vector>

class Frame : public Container
{
	enum Mode
	{
		STATIC,
		DYNAMIC
	};
public:
	Frame();
	~Frame();

	Slot operator[](int index)
	{
		if (index >= 0)
			return mSlots.at(index);
		return  mSlots[0];
	}

	Slot operator[](Object& item)
	{
		for (unsigned int i = 0; i < mSlots.size(); i++)
		{
			if (mSlots[i] == item)
			{
				return mSlots[i];
			}
		}
		return mSlots[0];
	}

	virtual void addItem(sf::Vector2i position, Object& item) override;
	virtual void removeItem(Object& item) override;
	virtual bool contains(Object& item)  override;
	Object* hitTest(const sf::Vector2f mousePosition);
	virtual bool contains(const sf::Vector2f& position) override;
	virtual void update(sf::Int32 dt)  override;
	virtual void draw(sf::RenderWindow& window) override;
	virtual std::vector<Slot> getSlots() override;

	virtual float width() override;
	virtual float height() override;
	virtual void setPosition(sf::Vector2f position) override;

	void moveObject(sf::Vector2f amount);

private:
	Mode mMode;

};
#endif