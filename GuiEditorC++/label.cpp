#include "label.h"

Label::Label()
{
	loadFont("assets/Arial.ttf");
	mText.setFont(mFont);
	mText.setString("Button");
	mText.setCharacterSize(12);

	mText.setFillColor(sf::Color::White);
	mText.setStyle(sf::Text::Bold);
}

Label::Label(std::string text, std::string fontname)
{
	loadFont(fontname);	
	mText.setFont(mFont); 	
	mText.setString(text);		
	mText.setCharacterSize(12);

	mText.setFillColor(sf::Color::White);
	mText.setStyle(sf::Text::Bold);
	

}

Label::~Label()
{
}

void Label::draw(sf::RenderWindow& window)
{
	window.draw(mText);
	
}

void Label::update(float dt)
{
}

float Label::width()
{
	return 0.0;
}

float Label::height()
{
	return 0.0f;
}

sf::Text Label::getText() const
{
	return mText;
}

sf::Vector2i Label::getPosition() const
{
	return (sf::Vector2i)mText.getPosition();
}

void Label::setFontSize(int size)
{
	mText.setCharacterSize(12);
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

void Label::setPosition(sf::Vector2i position)
{
	mText.setPosition((sf::Vector2f)position);
}

void Label::moveObject(sf::Vector2f amount)
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
