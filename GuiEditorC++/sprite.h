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
	virtual void update(float dt) override;	
	virtual float width() override;
	virtual float height() override;	
	virtual Object* hitTest(const sf::Vector2i mousePosition);
	sf::Vector2i getPosition();
	void moveObject(const sf::Vector2f amount);		
	void Setup();	
	const std::shared_ptr<sf::Sprite> getSprite() const;
	void loadSprite(std::string filename);
private:
	std::shared_ptr<sf::Sprite> mSprite;
	sf::Texture mTexture;

private:
	
	bool mActive;
	sf::Vector2i mPosition;
protected:
	bool contains(const sf::Vector2i& position);


};
#endif