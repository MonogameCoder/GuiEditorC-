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
	virtual float defaultWidth() override;
	virtual float defaultHeight() override;
	virtual float width() override;
	virtual float height()  override;
	sf::Text getText() const;
	virtual vec2i getPosition() const override;
	virtual void setPosition(vec2f position) override;
	virtual Object* hitTest(const vec2f mousePosition) override;
	virtual bool contains(const vec2f& position) override;
	void moveObject(const vec2f amount);
	void setFontSize(int size);
	void setFillColor(sf::Color color);
	void setStyle(sf::Text::Style style);
	void setText(std::string text);
	void setPosition(vec2i position);
	void setOrigin(vec2f origin);
	vec2f getOrigin() const;
	void loadFont(std::string fontname);
private:
	sf::Text mText;
	sf::Font mFont;

};
#endif