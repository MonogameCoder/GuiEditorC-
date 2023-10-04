#pragma once
#ifndef LABEL
#define LABEL
#include "object.h"
#include <string.h>

class Label : public Object
{
public:
	Label();
	Label(std::string text, std::string fontname);
	virtual ~Label();

	Label(const Label& rhs) = delete;
	Label(Label&& rhs) noexcept = delete;
	Label& operator =(const Label& rhs) = delete;
	Label& operator=(Label&& rhs) noexcept = delete;

public:
	virtual void draw(sf::RenderWindow& window) override;
	virtual void update(float dt) override;
	virtual float width() override;
	virtual float height()  override;
	sf::Text getText() const;
	sf::Vector2i getPosition() const;
	void setFontSize(int size);
	void setFillColor(sf::Color color);
	void setStyle(sf::Text::Style style);
	void setText(std::string text);
	void setPosition(sf::Vector2i position);
	void moveObject(sf::Vector2f amount);
	void loadFont(std::string fontname);
private:
	sf::Text mText;
	sf::Font mFont;
};
#endif