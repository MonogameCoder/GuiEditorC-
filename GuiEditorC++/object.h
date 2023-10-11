#ifndef OBJECT
#define OBJECT
#include <SFML/Graphics.hpp>
class Object
{
public:
	Object();
	virtual ~Object();
	bool operator==(const Object& rhs) const;
	virtual void draw(sf::RenderWindow& window ) = 0;
	virtual void update(sf::Int32 dt) = 0;
	virtual float width() = 0;
	virtual float height() = 0;
	virtual Object* hitTest(const sf::Vector2f mousePosition)  = 0;
	virtual bool contains(const sf::Vector2f& position) = 0;
	virtual void setPosition(sf::Vector2f position) = 0;
	void setIndex(int index)
	{
		mIndex = index;
	}
public:
	bool mActive;
private:
	int mIndex;
};
#endif