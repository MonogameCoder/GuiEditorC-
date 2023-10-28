#pragma once
#ifndef LABEL
#define LABEL
#include "object.h"
#include <string.h>

class Label : public Object
{
public:
	Label() noexcept;
	explicit Label(std::string text, std::string fontname) noexcept;
	virtual ~Label();

	//Label(const Label& rhs) = delete;
	//Label(Label&& rhs) noexcept = delete;
	//Label& operator =(const Label& rhs) = delete;
	//Label& operator=(Label&& rhs) noexcept = delete;

public:
	virtual void draw(sf::RenderWindow& window) override;
	virtual void update(sf::Int32 dt) override;
	virtual float width() override;
	virtual float height()  override;
	sf::Text getText() const;
	virtual sf::Vector2i getPosition() const override;
	virtual void setPosition(sf::Vector2f position) override;
	virtual Object* hitTest(const sf::Vector2f mousePosition) override;
	virtual bool contains(const sf::Vector2f& position) override;
	void moveObject(const sf::Vector2f amount);
	void setFontSize(int size);
	void setFillColor(sf::Color color);
	void setStyle(sf::Text::Style style);
	void setText(std::string text);
	void setPosition(sf::Vector2i position);
	void setOrigin(sf::Vector2f origin);
	sf::Vector2f getOrigin() const;
	void loadFont(std::string fontname);
private:
	sf::Text mText;
	sf::Font mFont;

};
#endif