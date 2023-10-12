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
		Button();
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
		virtual Object* hitTest(const sf::Vector2f mousePosition) override;
		virtual bool contains(const sf::Vector2f& position) override;

		virtual void setPosition(sf::Vector2f position) override;
		virtual sf::Vector2i getPosition() const override;
		void moveObject(const sf::Vector2f amount) ;
		void Setup();
		const Sprite getButton() const;
		void setClicked(bool clicked);
	private:
		std::shared_ptr<Sprite> pButtonClicked;
		sf::Sprite mCurrentSprite;
		sf::Texture mTexture;
		sf::Texture mTextureClicked;
		bool mClicked;
		sf::Vector2i mPosition;
		Label mLabel;
		
	};

#endif