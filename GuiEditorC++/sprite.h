#ifndef SPRITE
#define SPRITE

#include "object.h"
#include <string.h>


class Sprite: public Object
{
public:
	Sprite();
	explicit Sprite(std::string filename) noexcept;
	Sprite(const Sprite& rhs);
	Sprite(Sprite&& rhs) noexcept;

	virtual ~Sprite();
	Sprite& operator =(const Sprite& rhs);
	Sprite& operator=(Sprite&& rhs) noexcept;


public:
	virtual void draw(sf::RenderWindow& window) override;
	virtual void update(sf::Int32 dt) override;
	void setWidth(float width);
	void setHeight(float height);
	virtual float defaultWidth() override;
	virtual float defaultHeight() override;
	virtual float width() override;
	virtual float height() override;	
	virtual Object* hitTest(const sf::Vector2f mousePosition) override;
	virtual bool contains(const sf::Vector2f& position) override;
	virtual void setPosition(sf::Vector2f position) override;
	virtual vec2i getPosition() const override;
	virtual void moveObject(const sf::Vector2f amount) override;		
	const std::shared_ptr<sf::Sprite> getSprite() const;
	void loadSprite(std::string filename);

protected:
	std::shared_ptr<sf::Sprite> pSprite;
	sf::Texture mTexture;

private:
	vec2i mPosition;
	float mWidth;
	float mHeight;



};
#endif