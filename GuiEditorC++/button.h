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
		virtual void update(float dt) override;
		virtual float width() override;
		virtual float height() override;
		virtual Object* hitTest(const sf::Vector2f mousePosition) override;
		sf::Vector2i getPosition();
		void moveObject(const sf::Vector2f amount);
		void Setup();
		const Sprite getButton() const;
		void setClicked(bool clicked);
	private:
		std::shared_ptr<Sprite> mButtonClicked;
		sf::Sprite mCurrentSprite;
		sf::Texture mTexture;
		sf::Texture mTextureClicked;
		bool mActive;
		bool mClicked;
		sf::Vector2i mPosition;
		Label mLabel;

	private:		
		bool contains(const sf::Vector2f& position);
		
	};

#endif