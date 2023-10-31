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

	const Slot& operator[](int index)
	{
		if (index >= 0)
			return *mSlots[index];
		return  *mSlots[0];
	}

	const Slot& operator[](Object& item)
	{
		for (unsigned int i = 0; i < mSlots.size(); i++)
		{
			if (*mSlots[i] == item)
			{
				return *mSlots[i];
			}
		}
		return *mSlots[0];
	}

	virtual void addItem(vec2i position, Object* item) override;
	virtual void removeItem(Object& item) override;
	virtual bool contains(Object& item)  override;
	Object* hitTest(const vec2f mousePosition);
	virtual bool contains(const vec2f& position) override;
	virtual void update(sf::Int32 dt)  override;
	virtual void draw(sf::RenderWindow& window) override;
	virtual std::vector<Slot*> getSlots() override;

	virtual float width() override;
	virtual float height() override;
	virtual void setPosition(vec2f position) override;

	void moveObject(vec2f amount);

private:
	Mode mMode;

};
#endif