#include "sprite.h"
#include <stdlib.h>
using namespace std;
Sprite::Sprite(std::string filename) noexcept
	: mPosition(sf::Vector2i::Vector2(0, 0)),
	  mActive(true)
{
	loadSprite(filename);
	mSprite = make_shared<sf::Sprite>(mTexture);
	
}

Sprite::Sprite(const Sprite& rhs) :
	mSprite(rhs.mSprite),
	mActive(rhs.mActive)
{

}

Sprite::Sprite(Sprite&& rhs) noexcept
{
	if (rhs.mSprite != nullptr)
	{
		mSprite = move(rhs.mSprite);
		
		
	}
	mActive = move(rhs.mActive);
	rhs.mSprite = nullptr;
}

Sprite::~Sprite()
{
}

Sprite& Sprite::operator=(const Sprite& rhs)
{
	mSprite = rhs.mSprite;
	return *this;
}

Sprite& Sprite::operator=( Sprite&& rhs) noexcept
{
	if (rhs.mSprite != nullptr)
	{
		mSprite = move(rhs.mSprite);
	}

	rhs.mSprite = nullptr;
	return *this;
}

void Sprite::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);	
	window.draw(*mSprite);	
	window.display();
}

void Sprite::update(float dt)
{
	
	
}

float Sprite::width()
{
	return mSprite->getLocalBounds().width;
}

float Sprite::height()
{
	return mSprite->getLocalBounds().height;
}
sf::Vector2i Sprite::getPosition()
{
	return sf::Vector2i(mSprite->getPosition());
}
void Sprite::moveObject(const sf::Vector2f amount)
{
	mSprite->move(amount);
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
bool Sprite::contains(const sf::Vector2f& position)
{	
	return mSprite->getGlobalBounds().contains(position);
}
void Sprite::Setup()
{
}
const shared_ptr<sf::Sprite> Sprite::getSprite() const
{
	return mSprite;
}

void Sprite::loadSprite(std::string filename)
{
	if (!mTexture.loadFromFile(filename))
	{
		exit(0);
	}
}


