#include "label.h"

Label::Label() noexcept
{
	loadFont("assets/Arial.ttf");
	mText.setFont(mFont);
	mText.setString("Button");
	mText.setCharacterSize(12);

	mText.setFillColor(sf::Color::White);
	mText.setStyle(sf::Text::Bold);
	mText.setOrigin(0, 0);

	mDefaultSize = vec2f(mText.getLocalBounds().width, mText.getLocalBounds().height);

	mActive = true;
}

Label::Label(std::string text, std::string fontname) noexcept
{
	loadFont(fontname);
	mText.setFont(mFont);
	mText.setString(text);
	mText.setCharacterSize(12);

	mText.setFillColor(sf::Color::White);
	mText.setStyle(sf::Text::Bold);
	mText.setOrigin(0, 0);

	mDefaultSize = vec2f(mText.getLocalBounds().width, mText.getLocalBounds().height);
	mActive = true;

}

Label::~Label()
{
}

void Label::draw(sf::RenderWindow& window)
{
	window.draw(mText);

}

void Label::update(sf::Int32 dt)
{

}

float Label::defaultWidth()
{
	return mDefaultSize.x;
}

float Label::defaultHeight()
{
	return mDefaultSize.y;
}

float Label::width()
{
	return mText.getGlobalBounds().width;
}

float Label::height()
{
	return mText.getGlobalBounds().height;
}

sf::Text Label::getText() const
{
	return mText;
}

vec2i Label::getPosition() const
{
	return (vec2i)mText.getPosition();
}

void Label::setPosition(vec2f position)
{
	mText.setPosition(position);
}

Object* Label::hitTest(const vec2f mousePosition)
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

bool Label::contains(const vec2f& position)
{
	return mText.getGlobalBounds().contains(position);
}


void Label::setFontSize(int size)
{
	mText.setCharacterSize(size);
}

void Label::setFillColor(sf::Color color)
{
	mText.setFillColor(color);
}

void Label::setStyle(sf::Text::Style style)
{
	mText.setStyle(style);
}

void Label::setText(std::string text)
{
	mText.setString(text);
}

void Label::setPosition(vec2i position)
{
	mText.setPosition((vec2f)position);
}

void Label::setOrigin(vec2f origin)
{
	mText.setOrigin(origin);
}

vec2f Label::getOrigin() const
{
	return mText.getOrigin();
}

void Label::moveObject(vec2f amount)
{
	mText.move(amount);
}

void Label::loadFont(std::string fontname)
{

	if (!mFont.loadFromFile(fontname))
	{
		exit(0);
	}
}