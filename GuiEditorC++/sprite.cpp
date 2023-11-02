#include "sprite.h"
#include <stdlib.h>


Sprite::Sprite()
{
}
Sprite::Sprite(std::string filename) noexcept
	:
	mPosition(vec2i(0, 0)),
	mHeight(0),
	mWidth(0)
	 
{
	mActive = true;
	loadSprite(filename);
	pSprite = std::make_shared<sf::Sprite>(mTexture);
	pSprite->setOrigin(0, 0);
	mDefaultSize = sf::Vector2f(pSprite->getGlobalBounds().width, pSprite->getGlobalBounds().height);
	
}

Sprite::Sprite(const Sprite& rhs) 
	:
	mHeight(rhs.mHeight),
	mWidth(rhs.mWidth)
{
	*this = rhs;
}

Sprite::Sprite(Sprite&& rhs) noexcept
	:
	mHeight(rhs.mHeight), 
	mWidth(rhs.mWidth)
{
	if (rhs.pSprite != nullptr)
	{
		pSprite = std::move(rhs.pSprite);		
	}
	
	rhs.pSprite = nullptr;
}

Sprite::~Sprite()
{
}

Sprite& Sprite::operator=(const Sprite& rhs)
{	
	pSprite = std::make_shared<sf::Sprite>(*rhs.pSprite);
	return *this;
}

Sprite& Sprite::operator=( Sprite&& rhs) noexcept
{
	if (rhs.pSprite != nullptr)
	{
		pSprite = std::move(rhs.pSprite);
	}

	rhs.pSprite = nullptr;
	return *this;
}

void Sprite::draw(sf::RenderWindow& window)
{
	
	window.draw(*pSprite);	
	
}

void Sprite::update(sf::Int32 dt)
{
	
	
}

void Sprite::setWidth(float width)
{
	mWidth = width;
}

void Sprite::setHeight(float height)
{
	mHeight = height;
}

float Sprite::defaultWidth()
{
	return mDefaultSize.x;
}

float Sprite::defaultHeight()
{
	return mDefaultSize.y;
}

float Sprite::width()
{
	return pSprite == nullptr ? mWidth : pSprite->getGlobalBounds().width;
}

float Sprite::height()
{
	return pSprite == nullptr ? mHeight :pSprite->getGlobalBounds().height;
}
vec2i Sprite::getPosition() const
{
	return vec2i(pSprite->getPosition());
}
void Sprite::moveObject(const sf::Vector2f amount)
{
	pSprite->move(amount);
}
Object* Sprite::hitTest(const sf::Vector2f mousePosition)
{
	if (mActive)
	{
		if (contains(mousePosition))
		{
			return this;
		}
	}
	return NULL;
}
void Sprite::setPosition(sf::Vector2f position)
{
	pSprite->setPosition(position);
}
bool Sprite::contains(const sf::Vector2f& position)
{	
	return pSprite->getGlobalBounds().contains(position);
}

const std::shared_ptr<sf::Sprite> Sprite::getSprite() const
{
	return pSprite;
}

void Sprite::loadSprite(std::string filename)
{
	if (!mTexture.loadFromFile(filename))
	{
		exit(0);
	}
}


