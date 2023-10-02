#include "sprite.h"
#include <stdlib.h>
using namespace std;
Sprite::Sprite(std::string filename) noexcept 
	: _position(sf::Vector2i::Vector2(0, 0)),
	  _active(true)
{
	_texture.loadFromFile(filename);
	_sprite = make_shared<sf::Sprite>(_texture);
	_rectangle = new sf::IntRect(_position.x, _position.y, _texture.getSize().x, _texture.getSize().y);
}

Sprite::Sprite(const Sprite& rhs) :
	_sprite(rhs._sprite),
	_rectangle(rhs._rectangle),
	_active(rhs._active)
{

}

Sprite::Sprite(Sprite&& rhs) noexcept
{
	if (rhs._sprite != nullptr)
	{
		_sprite = move(rhs._sprite);
		
		
	}
	_rectangle = move(rhs._rectangle);
	_active = move(rhs._active);
	rhs._sprite = nullptr;
}

Sprite::~Sprite()
{
}

Sprite& Sprite::operator=(const Sprite& rhs)
{
	_sprite = rhs._sprite;
	return *this;
}

Sprite& Sprite::operator=( Sprite&& rhs) noexcept
{
	if (rhs._sprite != nullptr)
	{
		_sprite = move(rhs._sprite);
	}

	rhs._sprite = nullptr;
	return *this;
}

void Sprite::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);	
	window.draw(*_sprite);	
	window.display();
}

void Sprite::update()
{
}

float Sprite::width()
{
	return _sprite->getLocalBounds().width;
}

float Sprite::height()
{
	return _sprite->getLocalBounds().height;
}
Object* Sprite::hitTest(sf::Vector2i mousePosition)
{
	if (_active)
	{
		if (contains(mousePosition))
		{
			return this;
		}
	}
	return NULL;
}
bool Sprite::contains(sf::Vector2i& position)
{	
	return (*_sprite).getTextureRect().contains(position);
}
shared_ptr<sf::Sprite> Sprite::getSprite()
{
	return _sprite;
}


