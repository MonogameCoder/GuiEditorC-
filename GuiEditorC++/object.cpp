#include "object.h"

Object::Object()
{
}

Object::~Object()
{
}

bool Object::operator==(const Object& rhs) const
{
	return rhs.mIndex  == mIndex;
}

void Object::draw(sf::RenderWindow& window)
{
}

void Object::update(sf::Int32 dt)
{
}

float Object::width()
{
	return 0;
}

float Object::height()
{
	return 0;
}
