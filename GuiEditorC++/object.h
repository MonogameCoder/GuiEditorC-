#ifndef OBJECT
#define OBJECT
#include <SFML/Graphics.hpp>
typedef sf::Vector2f vec2f;
typedef sf::Vector2i vec2i;

class Object
{
public:
	Object();
	virtual ~Object();
	bool operator==(const Object& rhs) const;
	bool operator!=(const Object& rhs) const;
	virtual void draw(sf::RenderWindow& window ) = 0;
	virtual void update(sf::Int32 dt) = 0;
	virtual float defaultWidth();
	virtual float defaultHeight();
	virtual float width() = 0;
	virtual float height() = 0;
	virtual Object* hitTest(const vec2f mousePosition)  = 0;
	virtual bool contains(const vec2f& position) = 0;
	virtual void setPosition(vec2f position) = 0;
	virtual vec2i getPosition() const;
	virtual void resize(vec2f amount);
	virtual void resetSize();
	//virtual void moveObject(const sf::Vector2f amount)  = 0;
	void setIndex(unsigned int index)
	{
		mIndex = index;
	}
public:
	bool mActive;
	vec2f mDefaultSize;
private:
	unsigned int mIndex = 0;
	std::hash<const Object*> hashObj;
};
#endif