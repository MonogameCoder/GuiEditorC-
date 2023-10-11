#ifndef SPRITE
#define SPRITE

#include "object.h"
#include <string.h>


class Sprite: public Object
{
public:
	explicit Sprite(std::string filename) noexcept;
	Sprite(const Sprite& rhs);
	Sprite(Sprite&& rhs) noexcept;

	virtual ~Sprite();
	Sprite& operator =(const Sprite& rhs);
	Sprite& operator=(Sprite&& rhs) noexcept;


public:
	virtual void draw(sf::RenderWindow& window) override;
	virtual void update(sf::Int32 dt) override;
	virtual float width() override;
	virtual float height() override;	
	virtual Object* hitTest(const sf::Vector2f mousePosition) override;
	virtual bool contains(const sf::Vector2f& position) override;
	virtual void setPosition(sf::Vector2f position) override;
	sf::Vector2i getPosition();
	void moveObject(const sf::Vector2f amount);		
	void Setup();	
	const std::shared_ptr<sf::Sprite> getSprite() const;
	void loadSprite(std::string filename);
private:
	std::shared_ptr<sf::Sprite> pSprite;
	sf::Texture mTexture;

private:
	sf::Vector2i mPosition;



};
#endif