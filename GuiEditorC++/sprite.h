#include "object.h"
#include <string.h>

#include <iostream>
#include <optional>

class Sprite: public Object
{
public:
	Sprite(std::string filename) noexcept;  
	Sprite(const Sprite& rhs);
	Sprite(Sprite&& rhs) noexcept;
	
	virtual ~Sprite();
	Sprite& operator =(const Sprite& rhs);
	Sprite& operator=(Sprite&& rhs) noexcept ;

	virtual void draw(sf::RenderWindow& window) override;
	virtual void update() override;
	virtual float width() override;
	virtual float height() override;	
	virtual Object* hitTest(sf::Vector2i mousePosition);
	bool contains(sf::Vector2i& position);
	void Setup();
private:
	std::shared_ptr<sf::Sprite> _sprite;
	sf::Texture _texture;
	sf::IntRect* _rectangle;
public:
	std::shared_ptr<sf::Sprite> getSprite();
	bool _active;
	sf::Vector2i _position;


};