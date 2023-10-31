#pragma once
#ifndef GRID
#define GRID
#include "container.h"
#include "gridLL.h"

class Grid : public Container
{
public:
	Grid();
	~Grid();

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
	void insert(Container::Slot* item);
	virtual void addItem(vec2i position, Object* item) override;
	void removeSlot(Object* item);
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
	GridLL mItems;
};
#endif // !GRID
