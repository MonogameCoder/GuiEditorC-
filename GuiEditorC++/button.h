#pragma once
#ifndef BUTTON
#define BUTTON

#include "sprite.h"
#include "object.h"
#include <string.h>
#include "label.h"

	class Button : public Sprite
	{
	public:
		Button() noexcept;
		explicit Button(std::string filename) noexcept;
		Button(const Button& rhs);
		Button(Button&& rhs) noexcept;
		virtual ~Button();

		Button& operator=(const Button& rhs);
		Button& operator=(Button&& rhs) noexcept;

	public:
		virtual void draw(sf::RenderWindow& window) override;
		virtual void update(sf::Int32 dt) override;
		virtual float width() override;
		virtual float height() override;
		virtual float defaultWidth() override;
		virtual float defaultHeight() override;
		virtual Object* hitTest(const vec2f mousePosition) override;
		virtual bool contains(const vec2f& position) override;
		virtual void setPosition(vec2f position) override;
		virtual vec2i getPosition() const override;
		virtual void resize(vec2f amount) override;
		virtual void resetSize() override;
		void setText(std::string text);
		const std::string getText() const;
		void moveObject(const vec2f amount) ;
		void Setup();
		const Sprite getButton() const;
		void setClicked(bool clicked);
	private:
		Sprite* pButtonClicked;
		sf::Sprite mCurrentSprite;
		sf::Texture mTexture;
		sf::Texture mTextureClicked;
		bool mClicked;
		vec2i mPosition;
		Label mLabel;
		
	};

#endif