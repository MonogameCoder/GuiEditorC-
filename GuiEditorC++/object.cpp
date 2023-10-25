#include "object.h"

Object::Object():mActive(true)
{
}

Object::~Object()
{
}

bool Object::operator==(const Object& rhs) const
{
	return rhs.mIndex  == mIndex;
}

bool Object::operator!=(const Object& rhs) const
{
	return !(*this == rhs);
}

void Object::draw(sf::RenderWindow& window)
{
}

void Object::update(sf::Int32 dt)
{
}

float Object::defaultWidth()
{
	return 0.0f;
}

float Object::defaultHeight()
{
	return 0.0f;
}

float Object::width()
{
	return 0;
}

float Object::height()
{
	return 0;
}

sf::Vector2i Object::getPosition() const
{
	return sf::Vector2i();
}

void Object::resize(sf::Vector2f size)
{
}

void Object::resetSize()
{
}
