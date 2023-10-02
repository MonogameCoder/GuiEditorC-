#include <SFML/Graphics.hpp>
class Object
{
public:
	Object();
	virtual ~Object();
	virtual void draw(sf::RenderWindow& window ) = 0;
	virtual void update() = 0;
	virtual float width() = 0;
	virtual float height() = 0;
};