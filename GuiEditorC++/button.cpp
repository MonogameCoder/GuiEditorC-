#include "button.h"
#include <SFML/Graphics.hpp>

Button::Button::Button():
	Sprite("assets/button0.png" )	
{
	pButtonClicked = std::make_shared<Sprite>("assets/button0clicked.png");
	mCurrentSprite = *getSprite();	
	mCurrentSprite.setOrigin(0, 0);

	mLabel.setFillColor(sf::Color::Black);
	mLabel.setStyle(sf::Text::Style::Regular);
	mLabel.setFontSize(12);
	mLabel.setPosition(sf::Vector2i(width() / 2, height() / 2));
	

	if (mLabel.width() >= mDefaultSize.x || mLabel.height() >= mDefaultSize.y)
	{
		resize(sf::Vector2f(mLabel.width() / mDefaultSize.x, 1 + mLabel.height() / mDefaultSize.y));
	}
	mLabel.setOrigin(sf::Vector2f(mLabel.width() / 2, mLabel.height() / 2));

	mDefaultSize = sf::Vector2f(mCurrentSprite.getLocalBounds().width, mCurrentSprite.getLocalBounds().height);
	
	mActive = true;

}

Button::Button(std::string filename) noexcept:
	Sprite(filename+".png")
{
	pButtonClicked = std::make_shared<Sprite>(filename + "clicked.png");
	mCurrentSprite = *getSprite();
	mCurrentSprite.setOrigin(0, 0);

	mLabel.setFillColor(sf::Color::Black);
	mLabel.setStyle(sf::Text::Style::Regular);
	mLabel.setFontSize(12);
	mLabel.setPosition(sf::Vector2i(width() / 2, height() / 2));	

	if (mLabel.width() >= mDefaultSize.x || mLabel.height() >= mDefaultSize.y)
	{
		resize(sf::Vector2f(mLabel.width() / mDefaultSize.x, 1 + mLabel.height() / mDefaultSize.y));
	}

	mLabel.setOrigin(sf::Vector2f(mLabel.width() / 2, mLabel.height() / 2));
	mDefaultSize = sf::Vector2f(mCurrentSprite.getLocalBounds().width, mCurrentSprite.getLocalBounds().height);
	
	mActive = true;
}

Button::Button(const Button& rhs): 
	Sprite(rhs),
	pButtonClicked(rhs.pButtonClicked),
	mCurrentSprite(rhs.mCurrentSprite),
	mClicked(rhs.mClicked)
{
	mActive = true;
}

Button::Button(Button&& rhs) noexcept :	Sprite(rhs)
{
	if (rhs.pButtonClicked != nullptr)
	{
		pButtonClicked = std::move(rhs.pButtonClicked);

	}
	mCurrentSprite = std::move(rhs.mCurrentSprite);
	mActive = rhs.mActive;
	mClicked = rhs.mClicked;
	rhs.pButtonClicked = nullptr;
}

Button::~Button()
{
}

Button& Button::operator=(const Button& rhs)
{
	pButtonClicked = rhs.pButtonClicked;
	return *this;
}

Button& Button::operator=(Button&& rhs) noexcept 
{
	if (rhs.pButtonClicked != nullptr)
	{
		pButtonClicked = move(rhs.pButtonClicked);
	}
	
	rhs.pButtonClicked = nullptr;
	return *this;
}

void Button::draw(sf::RenderWindow& window)
{
	auto pos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pos);
	if (!contains(worldPos))
	{
		mClicked = false;
	}
	
	window.draw(mCurrentSprite);
	mLabel.draw(window);
	
}

void Button::update(sf::Int32 dt)
{	
	if (mClicked)
	{
		mCurrentSprite = *pButtonClicked->getSprite();
	}
	else
	{
		mCurrentSprite = *getSprite();
	}
	
}

float Button::width()
{
	return getButton().getSprite()->getGlobalBounds().width;
}

float Button::height()
{
	return getButton().getSprite()->getGlobalBounds().height;
}

float Button::defaultWidth()
{
	return mDefaultSize.x;
}

float Button::defaultHeight()
{
	return mDefaultSize.y;
}

Object* Button::hitTest(const sf::Vector2f mousePosition)
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

void Button::setPosition(sf::Vector2f position)
{
	sf::Vector2f center(mCurrentSprite.getPosition().x + width() / 2, mCurrentSprite.getPosition().y + height() / 2 - mLabel.height() / 2);

	mCurrentSprite.setPosition(position);
	pButtonClicked->setPosition(position);
	mLabel.setOrigin(sf::Vector2f(mLabel.width() / 2, mLabel.height() / 2));
	mLabel.setPosition(center);

	getSprite()->setPosition(mCurrentSprite.getPosition());

}

sf::Vector2i Button::getPosition() const
{
	return sf::Vector2i(getButton().getSprite()->getPosition());
}

void Button::resize(sf::Vector2f amount)
{
	pButtonClicked->getSprite()->setScale(amount);
	getSprite()->setScale(amount);

}

void Button::moveObject(const sf::Vector2f amount)
{
	pButtonClicked->moveObject(amount);
	Sprite::moveObject(amount);
	mLabel.moveObject(amount);
}

void Button::Setup()
{
}

const Sprite Button::getButton() const
{
	return *this;
}

void Button::setClicked(bool clicked)
{
	mClicked = clicked;
}
bool Button::contains(const sf::Vector2f& position)
{
	return mCurrentSprite.getGlobalBounds().contains(position);
}


