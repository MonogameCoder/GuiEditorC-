#include "object.h"

Object::Object():mActive(true)
{
}

Object::~Object()
{
}

bool Object::operator==(const Object& rhs) const
{
	return hashObj(&rhs) == hashObj(this);
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

vec2i Object::getPosition() const
{
	return vec2i();
}

void Object::resize(vec2f size)
{
}

void Object::resetSize()
{
}
