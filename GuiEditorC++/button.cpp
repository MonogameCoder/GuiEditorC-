#include "button.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Button::Button::Button():
	Sprite("assets/button0.png" ),
	mActive(true)
{
	mButtonClicked = std::make_shared<Sprite>("assets/button0clicked.png");
	mCurrentSprite = *getSprite();
	
	mLabel.setFillColor(sf::Color::Black);
	mLabel.setStyle(sf::Text::Style::Regular);
	mLabel.setFontSize(16);
	int x = mLabel.getText().getLocalBounds().width /2;
	int y = mLabel.getText().getLocalBounds().height;
	mLabel.setPosition(sf::Vector2i(getSprite()->getLocalBounds().width / 2.f - x, getSprite()->getLocalBounds().height / 2.f - y));
	
}

Button::Button(std::string filename) noexcept:
	Sprite(filename),
	mActive(true)
{
	mButtonClicked = std::make_shared<Sprite>(filename + "clicked");
}

Button::Button(const Button& rhs): 
	Sprite(rhs),
	mButtonClicked(rhs.mButtonClicked),
	mCurrentSprite(rhs.mCurrentSprite),
	mActive(rhs.mActive),
	mClicked(rhs.mClicked)
{
	
}

Button::Button(Button&& rhs) noexcept :	Sprite(rhs)
{
	if (rhs.mButtonClicked != nullptr)
	{
		mButtonClicked = move(rhs.mButtonClicked);

	}
	mCurrentSprite = rhs.mCurrentSprite;
	mActive = rhs.mActive;
	mClicked = rhs.mClicked;
	rhs.mButtonClicked = nullptr;
}

Button::~Button()
{
}

Button& Button::operator=(const Button& rhs)
{
	mButtonClicked = rhs.mButtonClicked;
	return *this;
}

Button& Button::operator=(Button&& rhs) noexcept 
{
	if (rhs.mButtonClicked != nullptr)
	{
		mButtonClicked = move(rhs.mButtonClicked);
	}
	
	rhs.mButtonClicked = nullptr;
	return *this;
}

void Button::draw(sf::RenderWindow& window)
{

	window.clear(sf::Color::Black);
	// draw everything here...	
	window.draw(mCurrentSprite);
	mLabel.draw(window);
	window.display();
}

void Button::update(float dt)
{	
	if (mClicked)
	{
		mCurrentSprite = *mButtonClicked->getSprite();
	}
	else
	{
		mCurrentSprite = *getSprite();
	}
}

float Button::width()
{
	return getButton().getSprite().get()->getLocalBounds().width;
}

float Button::height()
{
	return getButton().getSprite().get()->getLocalBounds().height;
}

Object* Button::hitTest(const sf::Vector2i mousePosition)
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

sf::Vector2i Button::getPosition()
{
	return sf::Vector2i(getButton().getSprite().get()->getPosition());
}

void Button::moveObject(const sf::Vector2f amount)
{
	mButtonClicked->moveObject(amount);
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
bool Button::contains(const sf::Vector2i& position)
{
	return Sprite::contains(position);
}


