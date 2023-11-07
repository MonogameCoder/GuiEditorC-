#include "button.h"
#include <SFML/Graphics.hpp>

Button::Button::Button() noexcept:
	Sprite("assets/button0.png" )	
{
	pButtonClicked = new Sprite("assets/button0clicked.png");
	mCurrentSprite = *getSprite();	
	

	mLabel.setFillColor(sf::Color::Black);
	mLabel.setStyle(sf::Text::Style::Regular);
	mLabel.setFontSize(12);
	mLabel.setPosition(vec2i(width() / 2, height() / 2));
	mDefaultSize = vec2f(mCurrentSprite.getLocalBounds().width, mCurrentSprite.getLocalBounds().height);


	if (mLabel.width() >= mDefaultSize.x || mLabel.height() >= mDefaultSize.y)
	{
		resize(vec2f(0.5 + mLabel.width() / mDefaultSize.x, 1 + mLabel.height() / mDefaultSize.y));
	}

	mLabel.setOrigin(vec2f(mLabel.width() / 2, mLabel.height() / 2));
	mCurrentSprite.setOrigin(0,0);
	
	mActive = true;

}

Button::Button(std::string filename) noexcept:
	Sprite(filename+".png")
{
	pButtonClicked = new Sprite(filename + "clicked.png");
	mCurrentSprite = *getSprite();
	

	mLabel.setFillColor(sf::Color::Black);
	mLabel.setStyle(sf::Text::Style::Regular);
	mLabel.setFontSize(12);
	mLabel.setPosition(vec2i(width() / 2, height() / 2));	
	mDefaultSize = vec2f(mCurrentSprite.getLocalBounds().width, mCurrentSprite.getLocalBounds().height);


	if (mLabel.width() >= mDefaultSize.x || mLabel.height() >= mDefaultSize.y)
	{
		resize(vec2f(0.5 + mLabel.width() / mDefaultSize.x, 1 + mLabel.height() / mDefaultSize.y));
	}

	mLabel.setOrigin(vec2f(mLabel.width() / 2, mLabel.height() / 2));
	mCurrentSprite.setOrigin(0, 0);
	
	mActive = true;
}

Button::Button(const Button& rhs)
{
	*this = rhs;
}

Button::Button(Button&& rhs) noexcept :	Sprite(rhs)
{
	if (rhs.pButtonClicked != nullptr)
	{
		pButtonClicked = std::move(rhs.pButtonClicked);

	}
	mLabel = std::move(rhs.mLabel);
	rhs.pButtonClicked = nullptr;
}

Button::~Button()
{
	delete pButtonClicked;
	pButtonClicked = nullptr;
}

Button& Button::operator=(const Button& rhs)
{
	pSprite = std::make_shared<sf::Sprite>(*rhs.pSprite);
	pButtonClicked = new Sprite(*rhs.pButtonClicked);
	mDefaultSize = rhs.mDefaultSize;
	mLabel = rhs.mLabel;

	return *this;
}

Button& Button::operator=(Button&& rhs) noexcept 
{
	if (rhs.pButtonClicked != nullptr)
	{
		pButtonClicked = std::move(rhs.pButtonClicked);
	}
	mLabel = std::move(mLabel);
	rhs.pButtonClicked = nullptr;
	return *this;
}

void Button::draw(sf::RenderWindow& window)
{
	auto pos = sf::Mouse::getPosition(window);
	vec2f worldPos = window.mapPixelToCoords(pos);
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

Object* Button::hitTest(const vec2f mousePosition)
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

void Button::setPosition(vec2f position)
{
	vec2f center(mCurrentSprite.getPosition().x + width() / 2, mCurrentSprite.getPosition().y + height() / 2 - mLabel.height() / 2);

	mCurrentSprite.setPosition(position);
	pButtonClicked->setPosition(position);
	mLabel.setOrigin(vec2f(mLabel.width() / 2, mLabel.height() / 2));
	mLabel.setPosition(center);

	getSprite()->setPosition(mCurrentSprite.getPosition());

}

vec2i Button::getPosition() const
{
	return vec2i(getButton().getSprite()->getPosition());
}

void Button::resize(vec2f amount)
{
	pButtonClicked->getSprite()->setScale(amount);
	getSprite()->setScale(amount );

}

void Button::resetSize()
{
	/*vec2f size = vec2f(defaultWidth() /getSprite()->getGlobalBounds().width, defaultHeight() / getSprite()->getGlobalBounds().height);
	getSprite()->setScale(size);*/
}

void Button::setText(std::string text)
{
	mLabel.setText(text);
}

const std::string Button::getText() const
{
	return mLabel.getText().getString();
}
void Button::moveObject(const vec2f amount)
{
	pButtonClicked->moveObject(amount);
	Sprite::moveObject(amount);
	mLabel.moveObject(amount);
}


const Sprite Button::getButton() const
{
	return *this;
}

void Button::setClicked(bool clicked)
{
	mClicked = clicked;
}
bool Button::contains(const vec2f& position)
{
	return mCurrentSprite.getGlobalBounds().contains(position);
}


